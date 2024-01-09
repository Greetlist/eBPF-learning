from bcc import BPF
import argh
import sys
import socket
from struct import pack

class TcpTracing:
    def __init__(self, tcp_action):
        self.source_file = "tcp_trace.c"
        self.tcp_action = tcp_action
        self.bpf = BPF(src_file=self.source_file)
        self.attach_func_info = {
            "drop": {
                "type": "kprobe",
                "function": "tcp_drop",
                "c_start_function": "deal_tcp_drop",
                #"c_end_function": "deal_tcp_drop",
            },
            "retransmit": {
                "type": "tracepoint",
                "function": "tcp:tcp_retransmit_skb",
                "c_start_function": "deal_tcp_retransmit",
            },
        }
        self.attach_probes()

    def attach_probes(self):
        if self.tcp_action not in self.attach_func_info.keys():
            print("Unsupport tcp action {}, Support list is:".format(self.tcp_action))
            print("*"*50)
            for key in self.attach_func_info.keys():
                print(key)
            print("*"*50)
            print("Exit")
            exit()

        attach_info = self.attach_func_info[self.tcp_action]
        if attach_info["type"] == "kprobe":
            self.bpf.attach_kprobe(event=attach_info["function"], fn_name=attach_info["c_start_function"])
            if "c_end_function" in attach_info:
                self.bpf.attach_kretprobe(event=attach_info["function"], fn_name=attach_info["c_end_function"])
        elif attach_info["type"] == "tracepoint":
            self.bpf.attach_tracepoint(tp=attach_info["function"], fn_name=attach_info["c_start_function"])

    def open_perf_buffer(self):
        self.bpf["export_events"].open_perf_buffer(self.print_info)

    def print_header(self):
        print(
            "{:<10} {:<10} {:<15} {:<6} {:<15} {:<6} {:<10}".format(
                "PID", "COMM", "SADDR", "SPORT", "DADDR", "DPORT", "COUNTS"
            )
        )

    def print_info(self, cpu, data, size):
        info = self.bpf["export_events"].event(data)
        print(
            "{:<10} {:<10} {:<15} {:<6} {:<15} {:<6} {:<10}".format(
                info.pid, info.task_command.decode("utf-8", "replace"),
                socket.inet_ntop(socket.AF_INET, pack("I", info.saddr)), info.sport,
                socket.inet_ntop(socket.AF_INET, pack("I", info.daddr)), info.dport,
                info.count,
            )
        )

    def start(self):
        self.open_perf_buffer()
        self.print_header()

        while True:
            try:
                self.bpf.perf_buffer_poll()
            except ValueError:
                continue
            except KeyboardInterrupt:
                exit()

def trace(tcp_action="drop"):
    tt = TcpTracing(tcp_action)
    tt.start()

if __name__ == "__main__":
    argh.dispatch_commands([trace])
