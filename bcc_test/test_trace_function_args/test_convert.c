#include <stdio.h>
#include <linux/types.h>
#include <arpa/inet.h>

void local_inet_ntop(__u32 src, char* dst) {
  int index = 0;
  unsigned char bytes[4];
  bytes[0] = src & 0XFF;
  bytes[1] = (src >> 8) & 0XFF;
  bytes[2] = (src >> 16) & 0XFF;
  bytes[3] = (src >> 24) & 0XFF;
  printf("%d.%d.%d.%d\n", bytes[0], bytes[1], bytes[2], bytes[3]);
  for (int i = 0; i < 4; ++i) {
    int section_len = 0;
    while (bytes[i] != 0) {
      unsigned char c = bytes[i] % 10 + 48;
      bytes[i] /= 10;
      dst[index++] = c;
      section_len++;
    }
    if (section_len == 2 || section_len == 3) {
      int start_index = index - section_len;
      int end_index = index - 1;
      unsigned char cur = dst[start_index];
      dst[start_index] = dst[end_index];
      dst[end_index] = cur;
    }
    if (i != 3) {
      dst[index++] = '.';
    }
  }
  dst[index] = '\0';
}

int main(int argc, char** argv) {
  char dst[64];
  __u32 ip = 40151232;
  local_inet_ntop(ip, dst);
  printf("%s\n", dst);
  return 0;
}
