
/*
 * Thread test code.
 */
#include <types.h>
#include <lib.h>
#include <thread.h>
#include <synch.h>
#include <test.h>

#define NTHREADS  10

//static struct semaphore *tsem = NULL;
static int count;

static
void
myUnsafeThread(void *junk, unsigned long num)
{
	//int ch = '0' + num;
	//volatile int i;
	(void)num; //make void for now but will become an input parameter to see change on inc
	(void)junk;
	//kprintf("Count currently is %d \n", count);
	count = count + 1;
	//kprintf("Updated count is %d \n", count);
	//V(tsem);
}

int myUnsafeThreadTest(int nargs, char *args[]) {
        (void)nargs;
	(void)args;
	count = 0;
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
                result = thread_fork(name, NULL, myUnsafeThread, NULL, i);

		 if (result) {
                        panic("threadtest: thread_fork failed %s)\n", 
                              strerror(result));
                }
	}

	for (int z=0; z<10; z++) {
               // P(tsem);
        }
	kprintf("Unsafe Thread test done");
	kprintf("\n");
	kprintf("Count is equal to: %d", count);
	kprintf("\n");
	return 0;
}
