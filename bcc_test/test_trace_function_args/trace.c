#include <uapi/linux/ptrace.h>
#include <net/sock.h>
#include <net/ip_fib.h>
#include <net/tcp_states.h>
#include <bcc/proto.h>
#include <linux/taskstats.h>
#include <linux/bpf.h>
#include <linux/byteorder/generic.h>

#define buf_len 32
struct drop_info {
  u64 count;
  u32 pid;
  char task_command[TS_COMM_LEN];
  u32 drop_reason;
  u32 saddr;
  u32 daddr;
  u16 sport;
  u16 dport;
};
BPF_HASH(drop_socket_map, struct sock*, struct drop_info);

BPF_PERF_OUTPUT(export_events);

static void local_inet_ntop(__u32 src, unsigned char* dst) {
  u32 index = 0;
  unsigned char bytes[4];
  bytes[0] = src & 0XFF;
  bytes[1] = (src >> 8) & 0XFF;
  bytes[2] = (src >> 16) & 0XFF;
  bytes[3] = (src >> 24) & 0XFF;
  bpf_trace_printk("bytes: %d %d %d\n", bytes[0], bytes[1], bytes[2]);
  for (int i = 0; i < 4; ++i) {
    if (bytes[i] == 0) {
      dst[index++] = '0';
      continue;
    }
    unsigned int section_len = 0;
    while (bytes[i] != 0) {
      unsigned char c = bytes[i] % 10 + 48;
      unsigned char left = (bytes[i] >> 3) - bytes[i] - bytes[i];
      bytes[i] = left;
      //bytes[i] /= 10;
      dst[index++] = c;
      section_len++;
    }
    if (section_len == 2 || section_len == 3) {
      u32 start_index = index - section_len;
      u32 end_index = index - 1;
      unsigned char cur = dst[start_index];
      //dst[start_index] = dst[end_index];
      dst[end_index] = cur;
    }
    if (i != 3) {
      dst[index++] = '.';
    }
  }
  dst[index++] = '\0';
  //bpf_trace_printk("dst: %s.\n", dst);
}

int deal_fib_table_lookup(struct pt_regs* ctx,
      struct fib_table *tb, const struct flowi4 *flp,
      struct fib_result *res, int fib_flags) {
  unsigned char src[buf_len], dst[buf_len];
  __builtin_memset(src, 0, buf_len);
  __builtin_memset(dst, 0, buf_len);
  __be32 network_byte_src, network_byte_dst;
  bpf_probe_read_kernel((void*)&network_byte_src, sizeof(__be32), (const void*)&flp->saddr);
  bpf_probe_read_kernel((void*)&network_byte_dst, sizeof(__be32), (const void*)&flp->daddr);
  u64 addr_arr[2] = {network_byte_src, network_byte_dst};
  //char str[256];
  //bpf_snprintf(str, 256, "src: %pI4, dst: %pI4\n", addr_arr, 128);
  //bpf_trace_vprintk("src: %pI4, dst: %pI4\n", 256, addr_arr, 128);
  //bpf_trace_printk("src: %u, dst: %u.\n", network_byte_src, network_byte_dst);
  //local_inet_ntop(network_byte_src, src);
  //local_inet_ntop(network_byte_dst, dst);
  //bpf_trace_printk("src: %s.\n", src);
  //bpf_trace_printk("dst: %s.\n", dst);
  return 0;
}
