#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

typedef enum {
    TK_PLUS,     
    TK_MINUS,    
    TK_ASTERISK, 
    TK_SLASH,    
    TK_POWER,    
    TK_INTEGER,  
    TK_FLOAT,    
    TK_EOF,      
    TK_INVALID   
} TokenKind;

typedef struct {
    TokenKind kind;  
    union {
        int int_value;       
        float float_value;  
    };
} Token;

char buffer[BUFFER_SIZE];
int pos = 0;

Token get_next_token(FILE *fp) {
    Token token;
    int c = fgetc(fp);

    while (isspace(c)) {
        c = fgetc(fp);
    }

    if (c == '+') {
        token.kind = TK_PLUS;
    } else if (c == '-') {
        token.kind = TK_MINUS;
    } else if (c == '*') {
        if ((c = fgetc(fp)) == '*') {
            token.kind = TK_POWER;
        } else {
            ungetc(c, fp);
            token.kind = TK_ASTERISK;
        }
    } else if (c == '/') {
        token.kind = TK_SLASH;
    } else if (isdigit(c)) {
        int value = c - '0';
        while (isdigit(c = fgetc(fp))) {
            value = value * 10 + (c - '0');
        }
        if (c == '.') {
            float float_value = value;
            float divisor = 10.0;
            while (isdigit(c = fgetc(fp))) {
                float_value = float_value + (c - '0') / divisor;
                divisor *= 10.0;
            }
            ungetc(c, fp);
            token.kind = TK_FLOAT;
            token.float_value = float_value;
        } else {
            ungetc(c, fp);
            token.kind = TK_INTEGER;
            token.int_value = value;
        }
    } else if (c == EOF) {
        token.kind = TK_EOF;
    } else {
        token.kind = TK_INVALID;
    }

    return token;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }

    Token token;
    do {
        token = get_next_token(fp);
        switch (token.kind) {
            case TK_PLUS:
                printf("PLUS\n");
                break;
            case TK_MINUS:
                printf("MINUS\n");
                break;
            case TK_ASTERISK:
                printf("ASTERISK\n");
                break;
            case TK_SLASH:
                printf("SLASH\n");
                break;
            case TK_POWER:
                printf("POWER\n");
                break;
            case TK_INTEGER:
                printf("INTEGER(%d)\n", token.int_value);
                break;
            case TK_FLOAT:
                printf("FLOAT(%f)\n", token.float_value);
                break;
            case TK_EOF:
                printf("EOF\n");
                break;
            case TK_INVALID:
                printf("INVALID\n");
                break;
        }
    } while (token.kind != TK_EOF);
fclose(fp);
return 0;
}

