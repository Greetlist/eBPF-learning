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
  u64 invoke_total_count;
  u64 invoke_total_time;
  char symbol[MAX_SYMBOL_LEN];
};
BPF_PERCPU_HASH(symbol_map, u64, struct invoke_info);

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
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __builtin_memcpy(&ii.symbol, "_ZN13TcpConnection14ExtractMessageEv", MAX_SYMBOL_LEN);
    symbol_map.update(&hash_value, &ii);
  }
  return 0;
}

int trace_symbol__ZN13TcpConnection14ExtractMessageEv_end(struct pt_regs* ctx) {
  u64 hash_value = hash_str("_ZN13TcpConnection14ExtractMessageEv");
  struct invoke_info* i = symbol_map.lookup(&hash_value);
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di = {0};
    di.invoke_total_count = i->invoke_total_count;
    di.invoke_total_time = i->invoke_total_time;
    __builtin_memcpy(&di.symbol, i->symbol, MAX_SYMBOL_LEN);
    invoke_events.perf_submit(ctx, &di, sizeof(struct display_info));
  }
  return 0;
}
