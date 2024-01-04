#include <uapi/linux/ptrace.h>
#include <net/sock.h>
#include <net/tcp_states.h>
#include <bcc/proto.h>
#include <linux/taskstats.h>
#include <linux/bpf.h>

struct record_info {
  uint64_t connect_start_us;
  uint64_t connect_end_us;
  uint32_t pid;
  char task_command[TS_COMM_LEN];
  uint32_t saddr;
  uint32_t daddr;
  uint16_t sport;
  uint16_t dport;
};
BPF_HASH(socket_map, struct sock*, struct record_info);
BPF_PERF_OUTPUT(connect_events);

int deal_with_active_connect(struct pt_regs* ctx, struct sock* sk) {
  uint32_t pid = bpf_get_current_pid_tgid() >> 32;
  struct record_info si;
  memset(&si, 0, sizeof(struct record_info));
  si.pid = pid;
  si.connect_start_us = bpf_ktime_get_ns() / 1000ul;
  bpf_get_current_comm(&si.task_command, TS_COMM_LEN);
  bpf_trace_printk("command: %s\n", si.task_command);
  socket_map.update(&sk, &si);
  bpf_trace_printk("end of tcp_v4_connect\n");
  return 0;
}

int deal_with_established(struct pt_regs* ctx, struct sock* sk) {
  // socket tcp state must be SYN_SENT, because of 
  if (sk->__sk_common.skc_state != BPF_TCP_SYN_SENT) {
    return 0;
  }
  struct record_info* si = socket_map.lookup(&sk);
  if (si == NULL) {
    return 0;
  }

  // just care about ipv4 family
  if (sk->__sk_common.skc_family != AF_INET) {
    return 0;
  }

  struct record_info submit;
  __builtin_memset(&submit, 0, sizeof(struct record_info));
  submit.connect_start_us = si->connect_start_us;
  submit.connect_end_us = bpf_ktime_get_ns() / 1000ul;
  submit.pid = si->pid;
  __builtin_memcpy(submit.task_command, si->task_command, TS_COMM_LEN);
  submit.saddr = sk->__sk_common.skc_rcv_saddr;
  submit.daddr = sk->__sk_common.skc_daddr;
  submit.sport = sk->__sk_common.skc_num;
  submit.dport = sk->__sk_common.skc_dport;

  connect_events.perf_submit(ctx, &submit, sizeof(struct record_info));
  socket_map.delete(&sk);
  return 0;
}
