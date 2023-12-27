## Install libbpf
1. Download And Install llvm
``` bash
wget https://apt.llvm.org/llvm.sh
sudo bash llvm.sh 17
```

2. Download libbpf Dependencies
```
sudo apt install libelf python3-docutils
```

3. Download And Install bpftool
``` bash
git clone --recurse-submodules https://github.com/libbpf/bpftool.git
cd bpftool/src/
make
sudo make install
cd ../dock
make
sudo make install
```

4. Download And Install libbpf
``` bash
git clone --depth 1 https://github.com/libbpf/libbpf
cd libbpf/src/
make
sudo make install
```
