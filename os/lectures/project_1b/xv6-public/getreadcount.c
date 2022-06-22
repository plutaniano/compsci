#include "types.h"
#include "stat.h"
#include "user.h"


int main(int argc, char* argv[])
{
	printf(1, "The syscall getreadcount() has been called %d time(s).\n", getreadcount());
	exit();
}
