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
  char symbol[MAX_SYMBOL_LEN];
};
BPF_PERCPU_HASH(symbol_map, u64, struct invoke_info);

struct agg_info {
  u64 invoke_total_count;
  u64 invoke_total_time;
  char symbol[MAX_SYMBOL_LEN];
  struct bpf_spin_lock lock;
};
BPF_HASH(agg_map, u64, struct agg_info);

struct display_info {
  u64 invoke_total_count;
  u64 invoke_total_time;
  char symbol[MAX_SYMBOL_LEN];
};
BPF_PERF_OUTPUT(invoke_events);


int trace_symbol__ZN13TcpConnection14ExtractMessageEv_start(struct pt_regs* ctx) {
  u64 hash_value = hash_str("_ZN13TcpConnection14ExtractMessageEv");
  struct invoke_info* i = symbol_map.lookup(&hash_value);
  if (i == NULL) {
    struct invoke_info ii = {0};
    ii.invoke_start_us = bpf_ktime_get_ns() / 1000ul;
    __builtin_memcpy(&ii.symbol, "_ZN13TcpConnection14ExtractMessageEv", MAX_SYMBOL_LEN);
    symbol_map.update(&hash_value, &ii);
  } else {
    i->invoke_start_us = bpf_ktime_get_ns() / 1000ul;
    symbol_map.update(&hash_value, i);
  }
  return 0;
}

int trace_symbol__ZN13TcpConnection14ExtractMessageEv_end(struct pt_regs* ctx) {
  u64 hash_value = hash_str("_ZN13TcpConnection14ExtractMessageEv");
  struct invoke_info* i = symbol_map.lookup(&hash_value);
  if (i == NULL) {
    return 0;
  }

  struct agg_info* agg = agg_map.lookup(&hash_value);
  if (!agg) {
    struct agg_info new_agg = {0};
    __builtin_memcpy(&new_agg.symbol, "_ZN13TcpConnection14ExtractMessageEv", MAX_SYMBOL_LEN);
    agg_map.update(&hash_value, &new_agg);
    return 0;
  }
  bpf_spin_lock(&agg->lock);
  (agg->invoke_total_count)++;
  agg->invoke_total_time += (bpf_ktime_get_ns() / 1000ul - i->invoke_start_us);
  bpf_spin_unlock(&agg->lock);

  if (agg->invoke_total_count % 100 == 0) {
    struct display_info di = {0};
    di.invoke_total_count = agg->invoke_total_count;
    di.invoke_total_time = agg->invoke_total_time;
    __builtin_memcpy(&di.symbol, agg->symbol, MAX_SYMBOL_LEN);
    invoke_events.perf_submit(ctx, &di, sizeof(struct display_info));
  }
  return 0;
}
