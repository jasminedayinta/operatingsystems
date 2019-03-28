//
//  main.c
//  wordguessing
//
//  Created by Jasmine Juwono on 22.11.18.
//  Copyright © 2018 Jasmine Juwono. All rights reserved.
//


#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include "server.h"
#include "linkedlist.h"

static void read_fortune(evutil_socket_t evfd, short evwhat, void *evarg);
static void get_fortune(server_node *connection);
static void hide_the_words(status* s);

//part c. Write code to start fortune as a separate process with a pipe to read the
//output produced by fortune.
static void read_fortune(evutil_socket_t s, short evwhat, void *v){
    int i, pipe_fd = s;
    server_node *connection = (server_node*) v;
    
    // read fortune from the pipe and store in the buffer
    i = server_read(pipe_fd, connection->status->curr_fortune, 32);
    if (i == -1) {
        syslog(LOG_ERR, "failed to read from fortune");
        connection->status->curr_fortune[0] = '\0';
    } else {
        connection->status->curr_fortune[i] = '\0';
    }
}

//part e. Write code to select a random word from a phrase and to
//hide the word usinng underscores
static void hide_the_word(status* s){
    int count, num;
    char *token, *pos;
    char fortune[50];
    char limit[] = "\t\r\n\v\f.,;!~`_-";
    
    pos = s->curr_fortune;
    while((pos = strpbrk(pos, limit)) != NULL){
        pos++;
        count++;
    }
rand_word:
    srand(time(NULL));
    num = rand() % count;
    count = 0;
    
    //going through the phrase
    strcpy(fortune, s->curr_fortune);
    token = strtok(fortune, limit);
    while(token){
        if(count == num){
            pos = strstr(s->curr_fortune, token);
            if(!pos){
                goto rand_word;
            }
            //replacing the missing word with underscores
            memset(pos, '_', strlen(token));
            strcpy(s->curr_missing, token);
            break;
        }
        count++;
        token = strtok(NULL, limit);
    }
    //no word was chosen
    if (token == NULL){
        goto rand_word;
    }
}
