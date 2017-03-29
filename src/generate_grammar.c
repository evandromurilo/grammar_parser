#include <stdio.h>
#include <stdbool.h>
#include "../lib/hash.h"
#include "../lib/m_basics.h"
#include "../lib/m_list.h"
#include "grammar_parser.h"

bool isPunctuation(char c);
void print_expansion(struct LinkedList *strs);

int main(int argc, char **argv) {
	if (argc == 1) {
		fprintf(stderr, "Use: generate_grammar filename\n");
		return 1;
	}

	struct Hashtable *grammar = hash_init();
	parse(grammar, argv[1]);

	struct DefinitionNode *start = hash_getv(grammar, "<start>");
	if (start == NULL) {
		fprintf(stderr, "No <start> definition found.\n");
	       	return 1;
	}

	struct LinkedList *strs = init_list();

	expand(grammar, get_random_production(start), strs);
	print_expansion(strs);
	putchar('\n');

	return 0;
}

#define MAX_LINE_LENGTH 80
void print_expansion(struct LinkedList *strs) {
	struct LinkedNode *curr = strs->first;
	int l_length = 0;

	while (curr != NULL) {
		int w_length = len(curr->value);

		if (w_length == 1 && isPunctuation(((char *)curr->value)[0])) {
			printf("%c", ((char *)curr->value)[0]);
			l_length += 1;
		}
		else {
			putchar(' ');
			if (l_length + w_length < MAX_LINE_LENGTH) {
				l_length += w_length;
				printf("%s", (char *)curr->value);
			}
			else {
				l_length = w_length;
				printf("\n%s", (char *)curr->value);
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
