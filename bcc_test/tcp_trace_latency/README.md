## 原理

Send SYN:
    `tcp_v4_connect`  

Receive SYN+ACK and change `struct sock` to `TCP_ESTABLISHED`:  
    1. `tcp_v4_do_rcv`  
    2. `tcp_rcv_state_process`  
    3. `tcp_rcv_synsent_state_process`  
    4. `tcp_finish_connect ##change state to TCP_ESTABLISHED`  

Tracing Connection latency:  
    1. start\_time at end of `tcp_v4_connect` function  
    2. end\_time at end of `tcp_finish_connect` function  

Using BPF struct:
``` c
struct {
    char src_addr[];
    int src_port[];
    char dst_addr[];
    int dst_port[];
    PROTOCOL_TYPE type; // tcp == 6;
};
```

## 问题
1. 在`deal_with_established`函数里面，为什么要判断成`SYN_SENT`?

因为插入的函数会在这个函数开始之前执行, 所以在`tcp_finish_connect`的开始, socket的状态肯定先是`SYN_SENT`, 并不会直接改成`TCP_ESTABLISHED`

``` c
void tcp_finish_connect(struct sock *sk, struct sk_buff *skb)
{
  ...
  tcp_set_state(sk, TCP_ESTABLISHED);
  ...
}
```

2. 为什么不在kretprobe里面做?
因为插入的函数是在这个函数return之后做,sk并不一定会保留内核函数正在执行的信息.所以取sk里面的信息可能是错的
