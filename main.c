#include <stdio.h>

#include "errors.h"

main(int argc, char *argv[])
{
	
#if DEBUG
	printf("DEBUG");
#else
	printf("NOT DEBUG");
#endif
	

	return 0;
}
