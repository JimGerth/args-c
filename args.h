#ifndef ARGS_H
#define ARGS_H

#include <stdbool.h>

#define PARSE_SUCCESS 0
#define PARSE_ERROR -1

// ProgramOption type.
typedef struct {
	// A single letter flag for an option.
	//
	// For example the flag 'r' will be set by
	// adding '-r' when running the program.
	// Must be unique.
	char flag;

	// The long name of the option.
	//
	// Could be 'recursive' for example, which
	// would be set by adding '--recursive'.
	// Must be unique.
	char *name;

	// A description of the option.
	//
	// Describe what the program does when the
	// option is set, what arguments can be
	// passed in, etc.
	char *description;

	// Wether this option was set.
	//
	// This defaults to be false and should only
	// be changed by parse_args().
	bool set;

	// Wether this option takes an additional
	// argument, like --depth=10 for example.
	bool more;

	// An additional argument to this option.
	//
	// This is only vaild if [more] is true.
	char *arg;
} ProgramOption;

// Parse the program arguments [argv] according to the possible
// options specified in [optv].
int parse_args(int argc, char *argv[], int optc, ProgramOption optv[]);

// Print out a help screen with all the possible program
// options [optv] and their descriptions.
void print_usage(char *name, int optc, ProgramOption optv[]);

#endif
