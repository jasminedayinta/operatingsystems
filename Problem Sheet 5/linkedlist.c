//
//  linkedlist.c
//  wordguessing
//
//  Created by Jasmine Juwono on 22.11.18.
//  Copyright © 2018 Jasmine Juwono. All rights reserved.
//

#include "linkedlist.h"

server_node* add_new_server_node(server_node **top, int i){
server_node *curr_node = NULL;
status *curr_game = NULL;

if(*top == NULL){
    *top = (server_node*) malloc(sizeof(server_node));
    (*top)->next = NULL;
    curr_node = *top;
    goto reset;
}else{
    curr_node = *top;
    while (curr_node->next != NULL) {
        curr_node = curr_node->next;
    }
    curr_node->next = (server_node*) malloc(sizeof(server_node));
    curr_node = curr_node->next;
    curr_node->next = NULL;
}

reset:
    curr_node->i = i;
    curr_node->e = NULL;
    curr_node->status = (status*) malloc(sizeof(status));
    curr_game = curr_node->status;

curr_game->total_guesses = 0;
curr_game->correct_guesses = 0;
curr_game->current_fortune[0] = '\0';
curr_game->current_missing_word[0] = '\0';

return curr_node;
}
