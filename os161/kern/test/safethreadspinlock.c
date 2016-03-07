
/*
 * Thread test code.
 */
#include <types.h>
#include <lib.h>
#include <thread.h>
#include <synch.h>
#include <test.h>
#include <spinlock.h>


#define NTHREADS  10

static struct semaphore *tsem = NULL;
static struct spinlock thread_spinlock;
static int count;

static
void
mySpinlockThread(void *junk, unsigned long num)
{
	//int ch = '0' + num;
	//volatile int i;
	(void)num; //make void for now but will become an input parameter to see change on inc
	(void)junk;
	//V(tsem);   //why doesnt this work???!
	//count = count + 1;
	//P(tsem);
	//V(tsem);
	spinlock_acquire(&thread_spinlock);
	count = count +1;
	spinlock_release(&thread_spinlock);
	V(tsem);
}

int SafeSpinlockThreadTest(int nargs, char *args[]) {
        (void)nargs;
	(void)args;
	count = 0;
        if (tsem==NULL) {
                tsem = sem_create("tsem", 0); //maybe init to 1?
                if (tsem == NULL) {
                        panic("threadtest: sem_create failed\n");
                }
        }
	spinlock_init(&thread_spinlock);
        //note args[0] is the actual threadprog, args start at 1
	//int input = *args[1];
	//kprintf("input is: ");
	//kprintf("%c",input); //need to pass char instead of str?
	//kprintf("\n");
	kprintf("Starting unsafe test \n");
	char name[16];
        int i, result;

	for (i=0; i<10; i++) { //should be i<input but testing const 10
		snprintf(name, sizeof(name), "threadtest%d", i);
                result = thread_fork(name, NULL, mySpinlockThread, NULL, i);

		 if (result) {
                        panic("threadtest: thread_fork failed %s)\n", 
                              strerror(result));
                }
	}

	for (int z=0; z<10; z++) {
               P(tsem);
        }
	kprintf("Unsafe Thread test done");
	kprintf("\n");
	kprintf("Count is equal to: %d", count);
	kprintf("\n");
	return 0;
}



