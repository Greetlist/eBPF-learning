#include <string.h>
#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

char LICENSE[] SEC("license") = "Dual BSD/GPL";

SEC("kprobe/sys_clone")
int handle_clone(void* ctx) {
  const char s[] = "Hello, World!\n";
  bpf_trace_printk(s, strlen(s));
  return 0;
}
