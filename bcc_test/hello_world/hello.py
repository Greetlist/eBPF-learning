from bcc import BPF
#from bcc.utils import printb
import argh

def run():
    b = BPF(src_file="hello.c")
    b.attach_kprobe(event="_do_fork", fn_name="hello_world")

    while True:
        try:
            ret = b.trace_fields()
        except ValueError:
            continue
        except KeyboardInterrupt:
            exit()
        #printb(ret)
        print(ret)

if __name__ == "__main__":
    argh.dispatch_commands([run])
