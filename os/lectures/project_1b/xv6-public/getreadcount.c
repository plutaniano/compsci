#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
	printf(1, "The getreadcount syscall has been called %d time(s)!\n", getreadcount());
	exit();
}
