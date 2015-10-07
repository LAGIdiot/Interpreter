#include <stdio.h>

#include "errors.h"

main(int argc, char *argv[])
{
#if DEBUG
	printf("Working in DEBUG mode!\n");
#endif
	
	return 0;
}
