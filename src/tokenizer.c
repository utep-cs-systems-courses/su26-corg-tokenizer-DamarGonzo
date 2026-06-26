#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

// Case B: Working with Strings & memory allocation for strings

int space_char(char c) {
    return (c == ' ' || c == '\t');
}

int non_space_char(char c) {
    return (c != ' ' && c != '\t' && c != '\0');
}

char *token_start(char *str) {
    if (str == NULL) return NULL;
    while (*str != '\0') {
        if (non_space_char(*str)) {
            return str;
        }
        str++;
    }
    return NULL;
}

char *token_terminator(char *token) {
    if (token == NULL) return NULL;
    char *ptr = token;
    while (*ptr != '\0' && non_space_char(*ptr)) {
        ptr++;
    }
    return ptr;
}

int count_tokens(char *str) {
    int count = 0;
    char *ptr = str;
    while ((ptr = token_start(ptr)) != NULL) {
        count++;
        ptr = token_terminator(ptr);
    }
    return count;
}

char *copy_str(char *inStr, short len) {
    char *new_str = (char *)malloc((len + 1) * sizeof(char));
    if (new_str == NULL) return NULL;
    for (int i = 0; i < len; i++) {
        new_str[i] = inStr[i];
    }
    new_str[len] = '\0';
    return new_str;
}

// Case C: Adding tokens

char **tokenize(char *str) {
    int num_tokens = count_tokens(str);
    char **tokens = (char **)malloc((num_tokens + 1) * sizeof(char *));
    if (tokens == NULL) return NULL;

    char *ptr = str;
    for (int i = 0; i < num_tokens; i++) {
        ptr = token_start(ptr);
        char *end = token_terminator(ptr);
        short len = (short)(end - ptr);
        tokens[i] = copy_str(ptr, len);
        ptr = end;
    }
    tokens[num_tokens] = NULL;
    return tokens;
}

void print_tokens(char **tokens) {
    if (tokens == NULL) return;
    for (int i = 0; tokens[i] != NULL; i++) {
        printf("tokens[%d] = \"%s\"\n", i, tokens[i]);
    }
}

void free_tokens(char **tokens) {
    if (tokens == NULL) return;
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
}
