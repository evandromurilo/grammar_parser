#include <stdio.h>
#include <stdbool.h>
#include "grammar_parser.h"

bool isPunctuation(char c);
void print_expansion(struct StringList *strs);

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
	print_expansion(&strs);
	putchar('\n');

	return 0;
}

#define MAX_LINE_LENGTH 80
void print_expansion(struct StringList *strs) {
	struct StringNode *curr = strs->first;
	int l_length = 0;

	while (curr != NULL) {
		int w_length = len(curr->value);

		if (w_length == 1 && isPunctuation(curr->value[0])) {
			printf("%c", curr->value[0]);
			l_length += 1;
		}
		else {
			putchar(' ');
			if (l_length + w_length < MAX_LINE_LENGTH) {
				l_length += w_length;
				printf("%s", curr->value);
			}
			else {
				l_length = w_length;
				printf("\n%s", curr->value);
			}
		}

		curr = curr->next;
	}
}

bool isPunctuation(char c) {
	switch (c) {
		case ',': case ';': case ':': case '.': case '/': case '!': case '?': return true;
		default: return false;
	}
}

