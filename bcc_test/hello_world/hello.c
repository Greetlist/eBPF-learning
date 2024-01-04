//int kprobe___do_fork(struct pt_regs* ctx, struct sock* sk) {
//int kprobe___do_fork(void* ctx) {
//  bpf_trace_printk("University\n");
//  return 0;
//}

int hello_world(void* ctx) {
  bpf_trace_printk("In Self defined Function\n");
  return 0;
}
