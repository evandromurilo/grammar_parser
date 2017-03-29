#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "../lib/m_basics.h"
#include "grammar_parser.h"

#ifndef DEBUG
#define DEBUG 0
#endif

// print_linked: print every string in StringList separated by a whitespace
static void print_linked(struct LinkedNode *list);

void *parse(struct Hashtable *hash, char* filename) {
	if ((freopen(filename, "r", stdin)) == NULL) {
		perror("Could not open file");
		return NULL;
	}

	int size = 0;
	char line[MAX_LINE_SIZE];
	int line_size;

	// definition level
	while (true) {
		struct DefinitionNode *def = malloc(sizeof(struct DefinitionNode));
		def->productions = init_list();

		discard_until('{');
		read_char();
		discard_while(" \n\t");

		line_size = read_line(line, MAX_LINE_SIZE);
		if (line_size == 0) break;

		def->name = malloc(line_size+1);
		strcpy(def->name, line);

		if (DEBUG) printf("DEFINITION NAME: %s\n", line);

		// production level
		while (true) {
			discard_while(" \n\t");

			char first = read_char();
			if (first == '}') break;
			else push_char(first);
				
			line_size = read_until(';', line, MAX_LINE_SIZE);
			read_char(); // discard ';'
			if (DEBUG) printf("LINE: %s\n", line);
			if (line_size == 0) break;

			struct LinkedList *p = init_list();

			split_linked(p, line, " ");
			list_append(def->productions, p);
		}

		if (line_size == 0) break;
		if (DEBUG) putchar('\n');

		hash_add(hash, def->name, def);
	}

	if (DEBUG) printf("END OF PARSE\n\n");
}

void expand(struct Hashtable *grammar, struct LinkedList *production, struct LinkedList *strs) {
	if (DEBUG) printf("Expanding!\n");

	for (struct LinkedNode *curr = production->first; curr != NULL; curr = curr->next) {
		struct DefinitionNode *def;

		if (((char *)curr->value)[0] != '<') def = NULL;
		else def = hash_getv(grammar, curr->value);

		if (def == NULL) {
			if (DEBUG) printf("appending %s\n", (char *)curr->value);
			list_append(strs, curr->value);
		}
		else expand(grammar, get_random_production(def), strs);
	}
}

struct LinkedList *get_random_production(struct DefinitionNode *def) {
	static bool seeded = false;

	if (!seeded) {
		srand(time(NULL));
		seeded = true;
	}

	if (DEBUG) printf("Getting random production\n");
	int r = rand()%(def->productions->length);
	if (DEBUG) printf("random index is %d\n", r);
	struct LinkedNode *p = def->productions->first;

	for (int i = 0; i < r; ++i) p = p->next;

	if (DEBUG) print_linked(p), putchar('\n');

	return p->value;
}

static void print_linked(struct LinkedNode *curr) {
	while (curr != NULL) {
		printf("%s ", (char *)curr->value);
		curr = curr->next;
	}
}
