/*
 * The code below has been developed by Johan Nordlander and Fredrik Bengtsson at LTU.
 * Part of the code has been also developed, modified and extended to ARMv8 by Wagner de Morais and Hazem Ali.
*/
/*
 * Modified by Wagner Morais on Sep 2022.
 */

#ifndef _TINYTHREADS_H
#define _TINYTHREADS_H

#define MUTEX_INIT {0,0}

struct thread_block;
typedef struct thread_block *thread;

struct mutex_block {
    int locked;
    thread waitQ;
};
typedef struct mutex_block mutex;

void lock(mutex *m);
void unlock(mutex *m);

void spawn(void (*code)(int), int arg);
void spawnWithDeadline(void (* function)(int), int arg, unsigned int deadline, unsigned int rel_deadline);
void yield(void);

void scheduler(void);

void printTinyThreadsPiface(void);
void printTinyThreadsUART(void);

#endif

