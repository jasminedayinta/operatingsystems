//
//  main.c
//  problem1
//
//  Created by Jasmine Juwono on 27.09.18.
//  Copyright © 2018 Jasmine Juwono. All rights reserved.
//
/*
 Jasmine Dayinta
 Operating Systems
 Problem 1.1
 Problem Sheet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <getopt.h>
#include <unistd.h>

int main(int argc, const char **argv) {
    int in, counter;
    char input[1];
    
    switch(in){
        case '1':{
            input[0] = getc(stdin);
            if(input[0] == EOF){
                return 0;
            }else{
                while(input[0] != EOF){
                counter = putc(input[0], stdout);
            
                    if(counter == EOF){
                        return 1;
                    }
                    input[0] = getc(stdin);
                }
            }
            break;
        }
        
        case 's':{
            ssize_t counter = read(0, &input, 1);
            if(counter == -1){
                return 1;
            }
            counter = write(1, &input, 1);
            if(counter == -1 || counter != sizeof(input)){
                return 1;
            }
            counter = read(0, &input, 1);
            break;
        }

        case 'p':{
            while(sendfile(1, 0, NULL, 1));
        }
    }
}
