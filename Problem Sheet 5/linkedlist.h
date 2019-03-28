//
//  linkedlist.h
//  wordguessing
//
//  Created by Jasmine Juwono on 22.11.18.
//  Copyright © 2018 Jasmine Juwono. All rights reserved.
//

#ifndef linkedlist_h
#define linkedlist_h

#include <stdio.h>
typedef struct status {
    int total_guesses;
    int correct_guesses;
    char curr_fortune[50];
    char curr_missing[50];
} status;

typedef struct node {
    int i;
    status *status;
    struct event *e;
    struct node *next;
} server_node;

server_node* add_new_server_node(server_node **head, int i);

#endif /* linkedlist_h */
