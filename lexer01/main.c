#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS 30000

typedef enum Token {
  ADD,
  SUBTRACT,
  MULTIPLY,
  DIVIDE,
  OTHER,
} Token;

typedef struct TokenInfo {
  Token token;
  char value;
} TokenInfo;

TokenInfo tokenize(char ch) {
  TokenInfo info;
  switch(ch) {
    case '+':
      info.token = ADD;
      info.value = ch;
      break;
    case '-':
      info.token = SUBTRACT;
      info.value = ch;
      break;
    case '*':
      info.token = MULTIPLY;
      info.value = ch;
      break;
    case '/':
      info.token = DIVIDE;
      info.value = ch;
      break;
    default:
      info.token = OTHER;
      info.value = ch;
  }
  return info;
}

int main(int argc, char** argv) {
  TokenInfo tokens[MAX_TOKENS];
  int num_tokens = 0;
  
  FILE *input_file;
  input_file = fopen(argv[1],"r");

  char ch;
  while ((ch = getc(input_file)) != EOF) {
    tokens[num_tokens] = tokenize(ch);
    num_tokens++;
  }

  fclose(input_file);

  for (int i = 0; i < num_tokens; i++) {
    switch(tokens[i].token) {
      case ADD:
        printf("\nAddition: %c", tokens[i].value);
        break;
      case SUBTRACT:
        printf("\nSubtraction: %c", tokens[i].value);
        break;
      case MULTIPLY:
        printf("\nMultiplication: %c", tokens[i].value);
        break;
      case DIVIDE:
        printf("\nDivision: %c", tokens[i].value);
        break;
      default:
        printf("\nOther: %c", tokens[i].value);
    }
  }

  printf("\n");
  return 0;
}
