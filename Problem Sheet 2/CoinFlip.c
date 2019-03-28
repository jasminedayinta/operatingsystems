//
//  main.c
//  problem2
//
//  Created by Jasmine Juwono on 11.10.18.
//  Copyright © 2018 Jasmine Juwono. All rights reserved.
//
/*
 Jasmine Dayinta
 Operating Systems
 Problem Sheet 2
 */

#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <semaphore.h>
#include <errno.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int persons = 100;
int n = 10000;
char coins[] = {'O','O','O','O','O','O','O','O','O', 'X','X','X','X','X','X','X','X','X'};

char coin_flip(char cf){
    if(cf == 'O'){
        return 'X';
    }else{
        return 'O';
    }
}

//Source code extracted from Prof. Schoenwaelder's website
void run_threads(unsigned int n, void* (*work)(void*)){
    static const char *progname = "pthread";
    pthread_t *thread;
    int rc;
    
    thread = calloc(n, sizeof(pthread_t));
    if (! thread) {
        fprintf(stderr, "%s: %s: %s\n", progname, __func__, strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < n; i++) {
        rc = pthread_create(&thread[i], NULL, work, NULL);
        if (rc) {
            fprintf(stderr, "%s: %s: unable to create thread %d: %s\n",
                    progname, __func__, i, strerror(rc));
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (thread[i]) {
            (void) pthread_join(thread[i], NULL);
        }
    }
    
    (void) free(thread);
}

//Source code given in the problem sheet
static double timeit(int n, void* (*proc)(void *)){
    clock_t t1, t2;
    t1 = clock();
    run_threads(n, proc);
    t2 = clock();
    return ((double) t2 - (double) t1) / CLOCKS_PER_SEC * 1000;
}

static void *first(void *func){
    pthread_mutex_lock(&m);
    int i, j;
    
    for(i = 0; i < n; i++){
        for(j = 0; j < 20; j++){
            coins[j] = coin_flip(coins[j]);
        }
    }
    pthread_mutex_unlock(&m);
    return NULL;
}

static void *second(void *func){
    int i, j;
    for(i = 0; i < n; i++){
        pthread_mutex_lock(&m);
        for(j = 0; j < 20; j++){
            coins[j] = coin_flip(coins[j]);
        }
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

static void *third(void *func){
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < 20; j++){
            pthread_mutex_lock(&m);
            coins[j] = coin_flip(coins[j]);
            pthread_mutex_unlock(&m);
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    int in, ptemp, ntemp;
    double time1, time2, time3;
    
    while((in = getopt(argc, argv, "p:n:")) != -1){
        switch(in){
            case 'p':
                ptemp = atoi(optarg);
                if(ptemp <= 0){
                    perror("Invalid!");
                    exit(1);
                }
                persons = ptemp;
            case 'n':
                ntemp = atoi(optarg);
                if(ntemp <= 0){
                    perror("Invalid!");
                    exit(1);
                }
                n = ntemp;
            default:
                perror("Invalid command");
                exit(1);
        }
    }
    
    printf("coins: %s (start - global lock)\n", coins);
    time1 = timeit(persons, first);
    printf("coins: %s (end - global lock)\n", coins);
    printf("%d threads x %d flips: %.3lf ms\n\n", persons, n, time1);
    
    printf("coins: %s (start - iteration lock)\n", coins);
    time2 = timeit(persons, second);
    printf("coins: %s (end - table lock)\n", coins);
    printf("%d threads x %d flips: %.3lf ms\n\n", persons, n, time2);
    
    printf("coins: %s (start - coin lock)\n", coins);
    time3 = timeit(persons, third);
    printf("coins: %s (end - coin lock)\n", coins);
    printf("%d threads x %d flips: %.3lf ms\n\n", persons, n, time3);

    return 0;
}
