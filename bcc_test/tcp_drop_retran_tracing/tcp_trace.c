#include <uapi/linux/ptrace.h>
#include <net/sock.h>
#include <net/tcp_states.h>
#include <bcc/proto.h>
#include <linux/taskstats.h>
#include <linux/bpf.h>

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

struct retransmit_info {
  u64 count;
  u32 pid;
  char task_command[TS_COMM_LEN];
  u32 saddr;
  u32 daddr;
  u16 sport;
  u16 dport;
};
BPF_HASH(retransmit_socket_map, struct sock*, struct retransmit_info);

BPF_PERF_OUTPUT(export_events);

int deal_tcp_drop(struct pt_regs* ctx, struct sock* sk) {
  // just care about ipv4 family
  if (sk->__sk_common.skc_family != AF_INET) {
    return 0;
  }
  struct drop_info* di = drop_socket_map.lookup(&sk);
  if (di == NULL) {
    struct drop_info new_drop_info = {0};
    new_drop_info.count = 1;
    new_drop_info.pid = bpf_get_current_pid_tgid() >> 32;
    bpf_get_current_comm(&new_drop_info.task_command, TS_COMM_LEN);
    new_drop_info.saddr = sk->__sk_common.skc_rcv_saddr;
    new_drop_info.daddr = sk->__sk_common.skc_daddr;
    new_drop_info.sport = sk->__sk_common.skc_num;
    u16 dport = sk->__sk_common.skc_dport;
    new_drop_info.dport = ntohs(dport);
    drop_socket_map.update(&sk, &new_drop_info);
    return 0;
  }

  di->count++;
  drop_socket_map.update(&sk, di);

  struct drop_info submit = {0};
  __builtin_memcpy(&submit, di, sizeof(struct drop_info));
  export_events.perf_submit(ctx, &submit, sizeof(struct drop_info));
  return 0;
}

int deal_tcp_retransmit(struct pt_regs* ctx, struct sock* sk) {
  // just care about ipv4 family
  if (sk->__sk_common.skc_family != AF_INET) {
    return 0;
  }
  struct retransmit_info* ri = retransmit_socket_map.lookup(&sk);
  if (ri == NULL) {
    struct retransmit_info new_info = {0};
    new_info.count = 1;
    new_info.pid = bpf_get_current_pid_tgid() >> 32;
    bpf_get_current_comm(&new_info.task_command, TS_COMM_LEN);
    new_info.saddr = sk->__sk_common.skc_rcv_saddr;
    new_info.daddr = sk->__sk_common.skc_daddr;
    new_info.sport = sk->__sk_common.skc_num;
    u16 dport = sk->__sk_common.skc_dport;
    new_info.dport = ntohs(dport);
    retransmit_socket_map.update(&sk, &new_info);
    return 0;
  }

  ri->count++;
  retransmit_socket_map.update(&sk, ri);

  struct retransmit_info submit = {0};
  __builtin_memcpy(&submit, ri, sizeof(struct retransmit_info));
  export_events.perf_submit(ctx, &submit, sizeof(struct retransmit_info));
  return 0;
}
