from bcc import BPF
import argh
import os
import subprocess as sub
import re
from jinja2 import Environment, FileSystemLoader

class TraceUserFunctionLatency:
    def __init__(self, program_path, symbol_regex, record_per_round):
        self.program_path = program_path
        self.symbol_regex = symbol_regex
        self.trace_symbol_dict = dict()

        #generate related members
        self.trace_function_template = "trace_symbol_{}_{}"
        self.record_per_round = record_per_round
        self.j2_file_name = "trace_uprobe.c.j2"
        self.c_file_name = "trace_uprobe.c"

    def init_all_symbol(self):
        symbol_list = self.get_all_match_symbol()
        for s in symbol_list:
            start_probe = self.trace_function_template.format(s, "start")
            end_probe = self.trace_function_template.format(s, "end")
            self.trace_symbol_dict[s] = (start_probe, end_probe)

    def generate_c_file(self):
        self.init_all_symbol()
        current_path = os.path.dirname(os.path.abspath(__file__))
        env = Environment(loader=FileSystemLoader(current_path))
        template = env.get_template(self.j2_file_name)

        ret = template.render({
            "trace_symbol_dict": self.trace_symbol_dict,
            "record_per_round": self.record_per_round,
        })
        with open(self.c_file_name, "w+") as f:
            f.write(ret)
    
    def get_all_match_symbol(self):
        ret_list = list()
        ret = sub.check_output("nm {}".format(self.program_path), shell=True)
        ret_str = ret.decode("utf-8")
        total_line = ret_str.split("\n")
        for line in total_line:
            m = re.match(self.symbol_regex, line)
            if m is not None:
                (offset, mode, symbol_inst) = line.split(" ")
                if mode == "W" or mode == "w":
                    continue
                ret_list.append(symbol_inst)
        return ret_list
    
    def print_elf_symbol_with_nm(self):
        print('Symbol is: [{}]\nTotal Match:'.format(self.symbol_regex))
        symbol_list = self.get_all_match_symbol()
        print('*'*50)
        for s in symbol_list:
            print(s)
        print('*'*50)

    def set_bpf(self, bpf):
        self.bpf = bpf
        self.bpf["invoke_events"].open_perf_buffer(self.print_invoke_info)

    def print_header(self):
        print(
            "{:<64} {:<15} {:<15} {:<15}".format(
                "Symbol", "InvokeCount", "InvokeTime", "AvgTime(ms)"
            )
        )

    def print_invoke_info(self, cpu, data, size):
        info = self.bpf["invoke_events"].event(data)
        print(
            "{:<64} {:<15} {:<15} {:<15}".format(
                info.symbol.decode("utf-8", "replace"),
                info.invoke_total_count, info.invoke_total_time,
                info.invoke_total_time / info.invoke_total_count,
            )
        )

def start(program_path, symbol_regex=None, record_per_round=100, list_symbol=False, generate_c_file=True):
    if symbol_regex == None:
        print("Must provide symbol_regex! Exit.")
        return

    tf = TraceUserFunctionLatency(program_path, symbol_regex, record_per_round)
    if generate_c_file:
        print("Start to generate c file: [{}]".format(tf.c_file_name))
        tf.generate_c_file()

    if list_symbol:
        tf.print_elf_symbol_with_nm()
        return

    b = BPF(src_file=tf.c_file_name)

    for symbol_name, function_pair in tf.trace_symbol_dict.items():
        start_probe, end_probe = function_pair
        b.attach_uprobe(name=program_path, sym=symbol_name, fn_name=start_probe)
        b.attach_uretprobe(name=program_path, sym=symbol_name, fn_name=end_probe)

    tf.set_bpf(b)
    tf.print_header()
    while True:
        try:
            b.perf_buffer_poll()
        except ValueError:
            continue
        except KeyboardInterrupt:
            exit()

if __name__ == '__main__':
    argh.dispatch_commands([start])
