#define MAX_SYMBOL_LEN 64

static u64 hash_str(const char* str) {
  u64 res = 5381;
  for (int i = 0; i < MAX_SYMBOL_LEN; ++i) {
    int c = *(str+i);
    res = ((res << 5) + res) + c;
  }
  return res;
}

struct invoke_info {
  u64 invoke_start_us;
  u64 symbol_index;
};
BPF_PERCPU_HASH(symbol_map, u64, struct invoke_info);

BPF_ARRAY(invoke_counts, u64, 1);
BPF_ARRAY(invoke_time, u64, 1);

struct display_info {
  u64 invoke_total_count;
  u64 invoke_total_time;
  u64 symbol_index;
};
BPF_PERF_OUTPUT(invoke_events);


int trace_symbol_0_start(struct pt_regs* ctx) {
  u64 hash_value = 0;
  struct invoke_info* i = symbol_map.lookup(&hash_value);
  if (i == NULL) {
    struct invoke_info ii = {0};
    ii.invoke_start_us = bpf_ktime_get_ns() / 1000ul;
    ii.symbol_index = hash_value;
    symbol_map.update(&hash_value, &ii);
  } else {
    i->invoke_start_us = bpf_ktime_get_ns() / 1000ul;
    symbol_map.update(&hash_value, i);
  }
  return 0;
}

int trace_symbol_0_end(struct pt_regs* ctx) {
  u64 hash_value = 0;
  struct invoke_info* i = symbol_map.lookup(&hash_value);
  if (i == NULL) {
    return 0;
  }

  invoke_counts.atomic_increment(i->symbol_index, 1);
  invoke_time.atomic_increment(i->symbol_index, bpf_ktime_get_ns() / 1000ul - i->invoke_start_us);
  return 0;
}
