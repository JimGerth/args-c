#include <stdio.h>

#include "args.h"

int optc = 4;
ProgramOption optv[] = {
	{ 'r', "recursive", .more=true, .description="Do whatever you want to do recursively because thats cool ;)" },
	{ 'a',       "all", .more=true, .description="Do everything!" },
	{ 'g',                          .description="Do it globally." },
	{     .name="help",             .description="Get help with the program." }
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
