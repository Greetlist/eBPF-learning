from bcc import BPF
import argh
import os
import subprocess as sub
import re
import time
from jinja2 import Environment, FileSystemLoader

class TraceUserFunctionLatency:
    def __init__(self, program_path, symbol_regex):
        self.program_path = program_path
        self.symbol_regex = symbol_regex
        self.trace_symbol_dict = dict()

        #generate related members
        self.trace_function_template = "trace_symbol_{}_{}"
        self.j2_file_name = "trace_uprobe.c.j2"
        self.c_file_name = "trace_uprobe.c"

    def init_all_symbol(self):
        self.get_all_match_symbol()
        for index, symbol in self.symbol_dict.items():
            start_probe = self.trace_function_template.format(index, "start")
            end_probe = self.trace_function_template.format(index, "end")
            self.trace_symbol_dict[index] = (start_probe, end_probe)

    def generate_c_file(self):
        self.init_all_symbol()
        current_path = os.path.dirname(os.path.abspath(__file__))
        env = Environment(loader=FileSystemLoader(current_path))
        template = env.get_template(self.j2_file_name)

        ret = template.render({
            "trace_symbol_dict": self.trace_symbol_dict,
            "symbol_dict_len": len(self.symbol_dict),
        })
        with open(self.c_file_name, "w+") as f:
            f.write(ret)
    
    def get_all_match_symbol(self):
        self.symbol_dict = dict()
        ret = sub.check_output("nm {}".format(self.program_path), shell=True)
        ret_str = ret.decode("utf-8")
        total_line = ret_str.split("\n")
        i = 0
        for line in total_line:
            m = re.match(self.symbol_regex, line)
            if m is not None:
                (offset, mode, symbol_inst) = line.split(" ")
                if mode == "W" or mode == "w":
                    continue
                self.symbol_dict[i] = symbol_inst
                i += 1
    
    def print_elf_symbol_with_nm(self):
        print('Symbol is: [{}]\nTotal Match:'.format(self.symbol_regex))
        self.get_all_match_symbol()
        print('*'*50)
        for index, symbol in self.symbol_dict.items():
            print('{}: [{}]'.format(index, symbol))
        print('*'*50)

    def set_bpf(self, bpf):
        self.bpf = bpf
        #self.bpf["invoke_events"].open_perf_buffer(self.print_invoke_info)

    def print_header(self):
        print(
            "{:<64} {:<15} {:<15} {:<15}".format(
                "Symbol", "InvokeCount", "InvokeTime", "AvgTime(ms)"
            )
        )

    def print_invoke_info(self):
        #info = self.bpf["invoke_events"].event(data)
        invoke_counts, invoke_time = self.get_invoke_counters()
        arr_len = len(invoke_counts)
        for i in range(arr_len):
            counts_value = invoke_counts[i].value
            time_value = invoke_time[i].value
            if counts_value > 0:
                print(
                    "{:<64} {:<15} {:<15} {:<15}".format(
                        self.symbol_dict[i],
                        counts_value, time_value,
                        round(time_value / counts_value / 1000, 3)
                    )
                )
            else:
                print(
                    "{:<64} {:<15} {:<15} {:<15}".format(
                        self.symbol_dict[i], 0, 0, 0
                    )
                )

    def get_invoke_counters(self):
        return self.bpf["invoke_counts"], self.bpf["invoke_time"]

def start(program_path, symbol_regex=None, list_symbol=False, generate_c_file=True):
    if symbol_regex == None:
        print("Must provide symbol_regex! Exit.")
        return

    tf = TraceUserFunctionLatency(program_path, symbol_regex)
    if generate_c_file:
        print("Start to generate c file: [{}]".format(tf.c_file_name))
        tf.generate_c_file()

    if list_symbol:
        tf.print_elf_symbol_with_nm()
        return

    b = BPF(src_file=tf.c_file_name)

    for symbol_index, symbol in tf.symbol_dict.items():
        start_probe, end_probe = tf.trace_symbol_dict[symbol_index]
        b.attach_uprobe(name=program_path, sym=symbol, fn_name=start_probe)
        b.attach_uretprobe(name=program_path, sym=symbol, fn_name=end_probe)

    tf.set_bpf(b)
    tf.print_header()
    while True:
        try:
            #b.perf_buffer_poll()
            tf.print_invoke_info()
            time.sleep(5)
        except ValueError:
            continue
        except KeyboardInterrupt:
            exit()

if __name__ == '__main__':
    argh.dispatch_commands([start])
