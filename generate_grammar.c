#include <stdio.h>
#include "grammar_parser.h"

int main(int argc, char **argv) {
	if (argc == 1) {
		fprintf(stderr, "Use: generate_grammar filename\n");
		return EXIT_FAILURE;
	}

	struct DefinitionList *grammar = parse(argv[1]);
	if (grammar == NULL) return EXIT_FAILURE;

	struct DefinitionNode *start = get_definition(grammar, "<start>");
	if (grammar == NULL) {
		fprintf(stderr, "No <start> definition found.\n");
	       	return EXIT_FAILURE;
	}

	struct StringList strs;
	strs.first = NULL;
	strs.last = NULL;

	expand(grammar, get_random_production(start), &strs);
	print_linked(&strs);
	putchar('\n');

	return 0;
}

