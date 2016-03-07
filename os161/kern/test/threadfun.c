
/*
 * Thread test code.
 */
#include <types.h>
#include <lib.h>
#include <thread.h>
#include <synch.h>
#include <test.h>

#define NTHREADS  10

static struct semaphore *tsem = NULL;

static
void
myThread(void *junk, unsigned long num)
{
	int ch = '0' + num;
	//volatile int i;

	(void)junk;

	putch(ch);

	V(tsem);
}

int myThreadTest(int nargs, char *args[]) {
        (void)nargs;
	unsigned long input = NTHREADS;
	//(void)args;
        //note args[0] is the actual threadprog, args start at 1
	if (nargs > 1)
		input = atoi(args[1]);;
	kprintf("Starting threadfun test \n");
        if (tsem==NULL) {
                tsem = sem_create("tsem", 0);
                if (tsem == NULL) {
                        panic("threadtest: sem_create failed\n");
                }
        }

	int num_threads = input;
	char name[16];
        int result;

	for (int i=0; i<num_threads; i++) { //should be i<input but testing const 10
		snprintf(name, sizeof(name), "threadtest%d", i);
                result = thread_fork(name, NULL, myThread, NULL, i);
		//P(tsem); //remember to comment it out

		 if (result) {
                        panic("threadtest: thread_fork failed %s)\n", 
                              strerror(result));
                }
	}

	for (int z=0; z<num_threads; z++) {
                P(tsem);  //go through and wake up all threads(blocking)
        }
	kprintf("\n");
	kprintf("Thread test done");
	return 0;
}
