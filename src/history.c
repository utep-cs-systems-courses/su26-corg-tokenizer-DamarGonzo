#include <stdio.h>
#include <stdlib.h>
#include "history.h"

// Case D: Maintaining History

List* init_history() {
    List *list = (List *)malloc(sizeof(List));
    if (list != NULL) {
        list->root = NULL;
    }
    return list;
}

void add_history(List *list, char *str) {
    if (list == NULL || str == NULL) return;

    Item *new_item = (Item *)malloc(sizeof(Item));
    if (new_item == NULL) return;

    // Calculate string length manually to avoid string.h 
    int len = 0;
    while (str[len] != '\0') len++;
    
    new_item->str = (char *)malloc((len + 1) * sizeof(char));
    for (int i = 0; i <= len; i++) {
        new_item->str[i] = str[i];
    }

    new_item->next = NULL;

    if (list->root == NULL) {
        new_item->id = 1;
        list->root = new_item;
    } else {
        Item *curr = list->root;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        new_item->id = curr->id + 1;
        curr->next = new_item;
    }
}

char *get_history(List *list, int id) {
    if (list == NULL) return NULL;
    Item *curr = list->root;
    while (curr != NULL) {
        if (curr->id == id) {
            return curr->str;
        }
        curr = curr->next;
    }
    return NULL;
}

void print_history(List *list) {
    if (list == NULL) return;
    Item *curr = list->root;
    while (curr != NULL) {
        printf("%d: %s\n", curr->id, curr->str);
        curr = curr->next;
    }
}

void free_history(List *list) {
    if (list == NULL) return;
    Item *curr = list->root;
    while (curr != NULL) {
        Item *temp = curr;
        curr = curr->next;
        free(temp->str);
        free(temp);
    }
    free(list);
}
