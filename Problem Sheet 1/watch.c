//
//  main.c
//  problem2
//
//  Created by Jasmine Juwono on 27.09.18.
//  Copyright © 2018 Jasmine Juwono. All rights reserved.
//
/*
 Jasmine Dayinta
 Operating Systems
 Problem 1.2
 Problem Sheet 1
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <getopt.h>
#include <sys/types.h>
#include <unistd.h>

int watch_(int argc, char **args, int *n, int *b, int *e, int s) {
    
    while(1){
        pid_t p = fork();
        if(p == 0){
            if(execvp(args[0], args) == -1){
                if(*b){
                    printf("a");
                }
                           exit(1);
            }
                           exit(0);
                           }else{
                               int counter;
                               waitpid(-1, &counter, WUNTRACED);
                               
                               if(*n){
                                   if(s < 1){
                                       return 1;
                               }
                                   sleep(s);
                               }else{
                                   sleep(2);
                               }
                           }
                        }
}
    
int main(int argc, char **argv){
        int counter, s;
        int n, b, e = 0;
        
        switch(counter){
            case 'n' :
                n = 1;
                s = atoi(optarg);
                break;
            case 'b' :
                b = 1;
                break;
            case 'e' :
                e = 1;
                break;
        }
    
    char *args[argc - optind + 1];
    int final = watch_(argc, args, &n, &b, &e, s);
        if(final){
            return 1;
        }
    return 0;
}
