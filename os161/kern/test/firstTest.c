#include <types.h>
#include <lib.h>
#include <array.h>
#include <test.h>


int firstTest
(int nargs, char **args)
{

	for(int i =0; i<nargs; i++) {
		kprintf(args[i]);
	}
	return 0;
}
