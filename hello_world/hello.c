#include <bpf/libbpf.h>
#include <unistd.h>
#include "hello.skel.h"

static int libbpf_print_fn(enum libbpf_print_level level, const char *format, va_list args) {
  return vfprintf(stderr, format, args);
}

int main(int argc, char** argv) {
  struct hello_bpf* skel;
  libbpf_set_print(libbpf_print_fn);
  skel = hello_bpf__open_and_load();
  if (!skel) {
    fprintf(stderr, "failed to open BPF\n");
    return 1;
  }

  int err = hello_bpf__attach(skel);
  if (err) {
    fprintf(stderr, "failed to Attach\n");
    return 1;
  }
  while (true) {
    fprintf(stderr, ".");
    sleep(1);
  }
  hello_bpf__destroy(skel);
  return 0;
}
