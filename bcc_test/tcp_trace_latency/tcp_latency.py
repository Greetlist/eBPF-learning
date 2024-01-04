from bcc import BPF
import argh
import sys
import socket
from struct import pack

b = None

def print_header():
    print(
        "{:<10} {:<10} {:<15} {:<6} {:<15} {:<6} {:<10}".format(
            "PID", "COMM", "SADDR", "SPORT", "DADDR", "DPORT", "LAT(ms)"
        )
    )

def print_connect_info(cpu, data, size):
    info = b["connect_events"].event(data)
    print(
        "{:<10} {:<10} {:<15} {:<6} {:<15} {:<6} {:<10}".format(
            info.pid, info.task_command.decode("utf-8", "replace"),
            socket.inet_ntop(socket.AF_INET, pack("I", info.saddr)), info.sport,
            socket.inet_ntop(socket.AF_INET, pack("I", info.saddr)), info.dport,
            #info.saddr, info.sport,
            #info.daddr, info.dport,
            (info.connect_end_us - info.connect_start_us) / 1000,
        )
    )

def trace():
    global b
    b = BPF(src_file="tcp_latency.c")
    b.attach_kprobe(event="tcp_v4_connect", fn_name="deal_with_active_connect")
    b.attach_kprobe(event="tcp_finish_connect", fn_name="deal_with_established")

    print_header()
    b["connect_events"].open_perf_buffer(print_connect_info)
    while True:
        try:
            b.perf_buffer_poll()
        except ValueError:
            continue
        except KeyboardInterrupt:
            exit()

if __name__ == "__main__":
    argh.dispatch_commands([trace])
