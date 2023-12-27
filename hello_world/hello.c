#include <linux/bpf.h>
#include <bpf/bpf.h>

void kprobe__sys_clone(void* ctx) {
  bpf_trace_printk("Hello World! %p\n", 32, ctx);
}