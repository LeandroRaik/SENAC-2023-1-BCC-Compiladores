#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 90000

int main(int argc, char** argv) {
  char ch;
  char alphabet[] = { '>', '<', '[', ']','+', '-', '.', ','};
  int memory[MAXSIZE] = {0};
  int source[MAXSIZE];
  int mPtr = 0;
  int sptr = 0;
  int size = 0;
  int opnKey = 0;
  while ((ch = getc(input_file)) != EOF) {
    if (memchr(alphabet, ch, sizeof(alphabet))) {
      source[sptr] = ch;
      sptr++;
    }
  }
  size = sptr;
  sptr = 0;
  while (sptr < size) {
    ch = source[sptr];
    if (ch == '>') mPtr++;
    else if (ch == '<') mPtr--;
    else if (ch == '+') memory[mPtr]++;
    else if (ch == '-') memory[mPtr]--;
    else if (ch == '.') printf("%c", memory[mPtr]);
    else if (ch == ',') memory[mPtr] = fgetc(stdin);
    else if (ch == '[' && !memory[mPtr]) {
      opnKey=1;
      while (opnKey > 0) {
        sptr++;
        if (source[sptr] == '[') opnKey++;
        else if (source[sptr] == ']') opnKey--;
      }
    }
    else if (ch == ']' && memory[mPtr]) {
      opnKey = 1;
      while (opnKey > 0) {
        sptr--;
        if (source[sptr] == '[') opnKey--;
        else if (source[sptr] == ']') opnKey++;
      }
    }
    sptr++;
  }

  return 0;
}
