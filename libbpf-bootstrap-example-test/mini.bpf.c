#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

char LICENSE[] SEC("license") = "Dual BSD/GPL";

//SEC("tp/syscalls/sys_enter_fork")
SEC("kprobe/_do_fork")
int handle_tp(void *ctx)
{
  int pid = bpf_get_current_pid_tgid();
  bpf_printk("BPF triggered from PID %d.\n", pid);
  return 0;
}
