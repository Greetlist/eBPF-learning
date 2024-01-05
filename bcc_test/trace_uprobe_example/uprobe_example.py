from bcc import BPF
import argh
import os
import subprocess as sub
import re
import jinjia2

class TraceUserFunctionLatency:
    def __init__(self, program_path, symbol, symbol_regex):
        self.program_path = program_path
        self.symbol_regex = symbol_regex
        self.trace_symbol_dict = dict()

        #generate related members
        self.trace_function_template = "trace_symbol_{}_start"
        self.j2_file_name = "trace_probe.c.j2"

    def init_all_symbol(self):
        symbol_list = get_all_match_symbol(self.program_path, self.symbol)
        for s in symbol_list:
            start_probe = self.trace_function_template.format(s)
            end_probe = self.trace_function_template.format(s)
            self.trace_symbol_dict[s] = (start_probe, end_probe)

    def generate_c_file(self):
        self.init_all_symbol()
        
            


    def gen_symbol_regex(self):
        return r".*{}.*".format(self.symbol)
    
    def get_all_match_symbol(self):
        ret_list = list()
        ret = sub.check_output("nm {}".format(self.program_path), shell=True)
        ret_str = ret.decode("utf-8")
        total_line = ret_str.split("\n")
        pattern = gen_symbol_regex(self.symbol)
        for line in total_line:
            m = re.match(pattern, line)
            if m is not None:
                (offset, mode, symbol_inst) = line.split(" ")
                ret_list.append(symbol_inst)
        return ret_list
    
    def print_elf_symbol_with_nm(self):
        pattern = gen_symbol_regex(self.symbol)
        print('Symbol Regex is: [{}]\nTotal Match:'.format(pattern))
        symbol_list = get_all_match_symbol(self.program_path, self.symbol)
        print('*'*50)
        for s in symbol_list:
            print(s)
        print('*'*50)

def trace(program_path, symbol=None, symbol_regex=None, list_symbol=False, generate_c_file=True):
    if symbol == None and symbol_regex == None:
        print("Must provide symbol or symbol_regex")
        return

    c_file_name = "trace_function_uprobe.c"
    if generate_c_file:
        print("Start to generate c file: [{}]".format(c_file_name))
        tf.generate_c_file()

    b = BPF(src_file=c_file_name)
    tf = TraceUserFunctionLatency(program_path, symbol, symbol_regex)

    if list_symbol:
        tf.print_elf_symbol_with_nm()
        return

    total_symbol_list = get_all_match_symbol(program_path, symbol)
    for symbol_name, function_pair in tf.trace_symbol_dict.items():
        start_probe, end_probe = function_pair
        b.attach_uprobe(name=program_path, sym=symbol_name, fn_name=start_probe)
        b.attach_uretprobe(name=program_path, sym=symbol_name, fn_name=end_probe)

    while True:
        try:
            b.perf_buffer_poll()
        except ValueError:
            continue
        except KeyboardInterrupt:
            exit()

if __name__ == '__main__':
    argh.dispatch_commands([trace, generate_c_file])
