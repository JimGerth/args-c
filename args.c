#include <stdio.h>
#include <string.h>

#include "args.h"

int parse_args(int argc, char *argv[], int optc, ProgramOption optv[]) {
	bool illegal_options_found = false;
	// Loop through all command line arguments, except for the program name.
	for (int argi = 1; argi < argc; argi++) {
		// Check long flags.
		if (argv[argi][0] == '-' && argv[argi][1] == '-') {
			// Ignore just "--".
			if (argv[argi][2]) {
				bool argfound = false;
				for (int opti = 0; opti < optc; opti++) {
					// Skip if option does not have a name.
					if (!optv[opti].name) {
						continue;
					}

					// Compute the length of the name of the option.
					// It will be needed a few times.
					int namelen = strlen(optv[opti].name);

					// Check for matches of the current argument under all defined options.
					// But only up to the length of any given option, as the argument could
					// be "--all=true", where we only want to match "--all".
					if (strncmp(argv[argi] + 2, optv[opti].name, namelen) == 0) {
						optv[opti].set = true;
						argfound = true;

						if (optv[opti].name) {
							printf("New option found: %s\n", optv[opti].name);
						} else if (optv[opti].flag) {
							printf("New option found: %c\n", optv[opti].flag);
						} else {
							printf("New option found.\n");
						}

						// Read in additional argument if the optoion takes one.
						if (optv[opti].more) {
							if (argv[argi][2 + namelen] == '=') {
								optv[opti].arg = argv[argi] + 2 + namelen + 1;
							} else {
								// Read in next string from argv.
								argi++;
								// TODO: Check for '-', "--" etc.
								optv[opti].arg = argv[argi];
							}
						}

						break;
					}
				}

				if (!argfound) {
					printf("Illegal option! (%s)\n", argv[argi] + 2);
					illegal_options_found = true;
					print_usage(argv[0], optc, optv);
				}
			}
		// Check short flags.
		} else if (argv[argi][0] == '-') {
			int charc = strlen(argv[argi]);
			// Loop through all characters in the current argument.
			for (int chari = 1; chari < charc; chari++) {
				bool argfound = false;
				for (int opti = 0; opti < optc; opti++) {
					// Skip if option does not have a flag (if it is '\0').
					if (!optv[opti].flag) {
						continue;
					}

					if (argv[argi][chari] == optv[opti].flag) {
						optv[opti].set = true;
						argfound = true;

						if (optv[opti].name) {
							printf("New option found: %s\n", optv[opti].name);
						} else if (optv[opti].flag) {
							printf("New option found: %c\n", optv[opti].flag);
						} else {
							printf("New option found.\n");
						}

						if (optv[opti].more) {
							if (argv[argi][chari + 1] == '=') {
								optv[opti].arg = argv[argi] + chari + 2;
							} else if (argv[argi][chari + 1]) {
								optv[opti].arg = argv[argi] + chari + 1;
							} else {
								// Read in next string from argv.
								argi++;
								// TODO: Check for '-', "--" etc.
								optv[opti].arg = argv[argi];
							}
							// Skip checking the rest of this argument.
							chari = charc;
						}
						break;
					}
				}
				if (!argfound) {
					printf("Illegal option! (%c)\n", argv[argi][chari]);
					illegal_options_found = true;
					print_usage(argv[0], optc, optv);
				}
			}
		} else {
			printf("Unknown option: %s\n", argv[argi]);
			illegal_options_found = true;
			print_usage(argv[0], optc, optv);
		}
	}
	return illegal_options_found ? PARSE_ERROR : PARSE_SUCCESS;
}

void print_usage(char *name, int optc, ProgramOption optv[]) {
	if (optc == 0) {
		printf("Usage: %s\n", name);
		return;
	}

	printf("Usage: %s [OPTIONS...]\n", name);
	printf("\n");
	printf("Options:\n");

	for (int opti = 0; opti < optc; opti++) {
		printf("\t");

		if (optv[opti].flag) {
			printf("-%c", optv[opti].flag);
			if (optv[opti].more && !optv[opti].name) {
				printf("=ARG");
			}
		}

		if (optv[opti].name) {
			if (optv[opti].flag) {
				printf(", ");
			}
			printf("--%s", optv[opti].name);
			if (optv[opti].more) {
				printf("=ARG");
			}
		}

		printf("\n");

		if (optv[opti].description) {
			printf("\t\t%s\n", optv[opti].description);
		}

		printf("\n");
	}
}
