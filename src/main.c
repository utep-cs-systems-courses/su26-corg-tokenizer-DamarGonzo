#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

// Case A: Building a Simple UI 

int main() {
    char input[256];
    List *history = init_history();

    while (1) {
        printf("$ "); /* Indicator */
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Remove newline character if present 
        int len = 0;
        while (input[len] != '\0') len++;
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
            len--;
        }

        if (len == 0) continue;

        // Case D: Recall History Logic
        if (input[0] == '!') {
            int id = 0;
            int i = 1;
            while (input[i] >= '0' && input[i] <= '9') {
                id = id * 10 + (input[i] - '0');
                i++;
            }
            
            char *hist_str = get_history(history, id);
            if (hist_str != NULL) {
                // Echo the recalled string
                printf("%s\n", hist_str);
                
                // Tokenize the recalled string
                char **tokens = tokenize(hist_str);
                print_tokens(tokens);
                free_tokens(tokens);
            } else {
                printf("History item !%d not found.\n", id);
            }
        } else {
            // Echo the input
            printf("%s\n", input);

            // Add to history
            add_history(history, input);

            // Case C: Tokenize and print
            char **tokens = tokenize(input);
            print_tokens(tokens);
            free_tokens(tokens);
        }
    }

    free_history(history);
    return 0;
}
