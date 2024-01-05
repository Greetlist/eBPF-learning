#define MAX_SYMBOL_LEN 64

struct invoke_info {
  u64 invoke_total_count;
  u64 invoke_total_time;
  char symbol[MAX_SYMBOL_LEN];
};
BPF_HASH(symbol_map, char*, struct invoke_info);

struct display_info {
  u64 avg_invoke_time;
  char symbol[MAX_SYMBOL_LEN];
};
BPF_PERF_OUTPUT(invoke_events);


int trace_symbol__GLOBAL__sub_I__ZN12LoginHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_GLOBAL__sub_I__ZN12LoginHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__GLOBAL__sub_I__ZN12LoginHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_GLOBAL__sub_I__ZN12LoginHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__GLOBAL__sub_I__ZN12OrderHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_GLOBAL__sub_I__ZN12OrderHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__GLOBAL__sub_I__ZN12OrderHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_GLOBAL__sub_I__ZN12OrderHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__GLOBAL__sub_I__ZN13LogoutHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_GLOBAL__sub_I__ZN13LogoutHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__GLOBAL__sub_I__ZN13LogoutHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_GLOBAL__sub_I__ZN13LogoutHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__GLOBAL__sub_I__ZN14UnknownHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_GLOBAL__sub_I__ZN14UnknownHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__GLOBAL__sub_I__ZN14UnknownHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_GLOBAL__sub_I__ZN14UnknownHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__GLOBAL__sub_I__ZN16HeartbeatHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_GLOBAL__sub_I__ZN16HeartbeatHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__GLOBAL__sub_I__ZN16HeartbeatHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_GLOBAL__sub_I__ZN16HeartbeatHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__GLOBAL__sub_I__ZN16SubscribeHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_GLOBAL__sub_I__ZN16SubscribeHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__GLOBAL__sub_I__ZN16SubscribeHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_GLOBAL__sub_I__ZN16SubscribeHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__GLOBAL__sub_I__ZN17QueryOrderHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_GLOBAL__sub_I__ZN17QueryOrderHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__GLOBAL__sub_I__ZN17QueryOrderHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_GLOBAL__sub_I__ZN17QueryOrderHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__GLOBAL__sub_I__ZN17QueryTradeHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_GLOBAL__sub_I__ZN17QueryTradeHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__GLOBAL__sub_I__ZN17QueryTradeHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_GLOBAL__sub_I__ZN17QueryTradeHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__GLOBAL__sub_I__ZN18CancelOrderHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_GLOBAL__sub_I__ZN18CancelOrderHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__GLOBAL__sub_I__ZN18CancelOrderHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_GLOBAL__sub_I__ZN18CancelOrderHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__GLOBAL__sub_I__ZN19QueryAccountHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_GLOBAL__sub_I__ZN19QueryAccountHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__GLOBAL__sub_I__ZN19QueryAccountHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_GLOBAL__sub_I__ZN19QueryAccountHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__GLOBAL__sub_I__ZN20QueryPositionHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_GLOBAL__sub_I__ZN20QueryPositionHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__GLOBAL__sub_I__ZN20QueryPositionHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_GLOBAL__sub_I__ZN20QueryPositionHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__ZN12LoginHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_ZN12LoginHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__ZN12LoginHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_ZN12LoginHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__ZN12OrderHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_ZN12OrderHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__ZN12OrderHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_ZN12OrderHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__ZN13LogoutHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_ZN13LogoutHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__ZN13LogoutHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_ZN13LogoutHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__ZN14UnknownHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_ZN14UnknownHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__ZN14UnknownHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_ZN14UnknownHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__ZN16HeartbeatHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_ZN16HeartbeatHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__ZN16HeartbeatHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_ZN16HeartbeatHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__ZN16SubscribeHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_ZN16SubscribeHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__ZN16SubscribeHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_ZN16SubscribeHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__ZN17QueryOrderHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_ZN17QueryOrderHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__ZN17QueryOrderHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_ZN17QueryOrderHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__ZN17QueryTradeHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_ZN17QueryTradeHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__ZN17QueryTradeHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_ZN17QueryTradeHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__ZN18CancelOrderHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_ZN18CancelOrderHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__ZN18CancelOrderHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_ZN18CancelOrderHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__ZN19QueryAccountHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_ZN19QueryAccountHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__ZN19QueryAccountHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_ZN19QueryAccountHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}

int trace_symbol__ZN20QueryPositionHandler13HandleRequestEv_start(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    struct invoke_info ii;
    __buildin_memset(&ii, 0, sizeof(struct invoke_info));
    ii.invoke_total_count = 0;
    ii.invoke_total_time = 0;
    __buildin_memcpy(ii.symbol, "_ZN20QueryPositionHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    symbol_map.update(, &ii);
  }
  return 0;
}

int trace_symbol__ZN20QueryPositionHandler13HandleRequestEv_end(struct pt_regs* ctx) {
  struct invoke_info* i = symbol_map.lookup();
  if (i == NULL) {
    return 0;
  }

  i->invoke_total_count++;
  i->invoke_total_time += 1;

  if (i->invoke_total_count % 100 == 0) {
    struct display_info di;
    __buildin_memset(&di, 0, sizeof(struct display_info));
    di.avg_invoke_time = i->invoke_total_time / i->invoke_total_count;
    __buildin_memcpy(di.symbol, "_ZN20QueryPositionHandler13HandleRequestEv", MAX_SYMBOL_LEN);
    invoke_events.perf_submit();
  }
}
