from bcc import BPF
import argh
import os
import subprocess as sub
import re
import time
from jinja2 import Environment, FileSystemLoader

class TraceKernelFunctionLatency:
    def __init__(self, kfunc_name):
        self.j2_file_name = "trace_kprobe.c.j2"
        self.c_file_name = "trace_kprobe.c"
        self.kfunc_name = kfunc_name
        self.trace_start_funcname = "trace_{}_start".format(kfunc_name)
        self.trace_end_funcname = "trace_{}_end".format(kfunc_name)
        self.print_template = "{:<64} {:<15} {:<15} {:<15}"

        self.generate_c_file()

    def generate_c_file(self):
        current_path = os.path.dirname(os.path.abspath(__file__))
        env = Environment(loader=FileSystemLoader(current_path))
        template = env.get_template(self.j2_file_name)

        ret = template.render({
            "start_funcname": self.trace_start_funcname,
            "end_funcname": self.trace_end_funcname,
            "symbol_index": 0,
            "symbol_dict_len": 1,
        })
        with open(self.c_file_name, "w+") as f:
            f.write(ret)

    def set_bpf(self, bpf):
        self.bpf = bpf

    def print_header(self):
        print(
            self.print_template.format(
                "FunctionName", "InvokeCount", "InvokeTime", "AvgTime(us)"
            )
        )

    def print_invoke_info(self):
        invoke_counts, invoke_time = self.get_invoke_counters()
        arr_len = len(invoke_counts)
        for i in range(arr_len):
            counts_value = invoke_counts[i].value
            time_value = invoke_time[i].value
            if counts_value > 0:
                print(
                    self.print_template.format(
                        self.kfunc_name,
                        counts_value, time_value,
                        round(time_value / counts_value / 1000, 3)
                    )
                )
            else:
                print(
                    self.print_template.format(
                        self.kfunc_name, 0, 0, 0
                    )
                )

    def get_invoke_counters(self):
        return self.bpf["invoke_counts"], self.bpf["invoke_time"]

def start(func_name=None):
    if func_name == None:
        print("Must provide kernel function name! Exit.")
        return

    tf = TraceKernelFunctionLatency(func_name)

    b = BPF(src_file=tf.c_file_name)
    b.attach_kprobe(event=func_name, fn_name=tf.trace_start_funcname)
    b.attach_kretprobe(event=func_name, fn_name=tf.trace_end_funcname)

    tf.set_bpf(b)
    tf.print_header()
    while True:
        try:
            tf.print_invoke_info()
            time.sleep(5)
        except ValueError:
            continue
        except KeyboardInterrupt:
            exit()

if __name__ == '__main__':
    argh.dispatch_commands([start])
