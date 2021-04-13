#include <stdio.h>

#include "args.h"

int optc = 2;
ProgramOption optv[] = {
	{ 'r', "recursive", .more=true },
	{ 'a',       "all", .more=true },
};

int main(int argc, char *argv[]) {
	int status = parse_args(argc, argv, optc, optv);

	if (status == PARSE_ERROR) {
		printf("Error: Bad arguments. Correct usage:...\n");
		// return -1;
	}

	printf(
		"recursive set: %d (more: %s), all set: %d (more: %s)\n",
		optv[0].set,
		optv[0].arg,
		optv[1].set,
		optv[1].arg
	);

	return 0;
}
