#include "grammar_parser.h"

#ifdef DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

struct DefinitionList *parse(char* filename) {
	if ((freopen(filename, "r", stdin)) == NULL) {
		perror("Could not open file");
		return NULL;
	}

	struct DefinitionList *definitions = malloc(sizeof(struct DefinitionList));
	definitions->first = NULL;
	definitions->last = NULL;

	int size = 0;
	char line[MAX_LINE_SIZE];
	int line_size;

	// definition level
	while (true) {
		struct DefinitionNode *def = malloc(sizeof(struct DefinitionNode));
		def->productions = malloc(sizeof(struct ProductionList));
		def->productions->first = NULL;
		def->productions->last = NULL;
		def->productions->size = 0;

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

			struct ProductionNode *p = malloc(sizeof(struct ProductionNode));
			p->names = malloc(sizeof(struct StringList));
			p->names->size = 0;
			p->names->first = NULL;
			p->names->last = NULL;

			split_linked(p->names, 100, line, ' ');
			append_production(def->productions, p);
		}

		if (line_size == 0) break;
		if (DEBUG) putchar('\n');

		append_definition(definitions, def);
	}

	if (DEBUG) printf("END OF PARSE\n\n");
	return definitions;
}

#define MAX_WORD_SIZE 1000
int split_linked(struct StringList *list, int size, char* str, char goal) {
	char word[MAX_WORD_SIZE+1];
	int i, c, total = 0;

	while (total < size && *str != '\0') {
		while (*str == goal && *str != '\0') ++str;

		if (*str == '\0') break;

		for (i = 0; i < MAX_WORD_SIZE && *str != goal && *str != '\0'; 
				++i, ++str) {
			word[i] = *str;
		}
		word[i] = '\0';

		char* nword = malloc(i);
		strcpy(nword, word);

		append_string(list, nword);
		if (DEBUG) printf("WORD: %s\n", list->last->value);
		++total;
	}

	return total;
}

void expand(struct DefinitionList *grammar, struct StringNode *production, struct StringList *strs) {
	if (DEBUG) printf("Expanding!\n");
	for (; production != NULL; production=production->next) {
		struct DefinitionNode *def;

		if (production->value[0] != '<') def = NULL;
		else def = get_definition(grammar, production->value);

		if (def == NULL) {
			if (DEBUG) printf("appending %s\n", production->value);
			append_string(strs, production->value);
		}
		else expand(grammar, get_random_production(def), strs);
	}
}

struct DefinitionNode *get_definition(struct DefinitionList *grammar, char* name) {
	if (DEBUG) printf("Searching for definition %s\n", name);
	struct DefinitionNode *curr = grammar->first;

	while (curr != NULL && strcmp(curr->name, name) != 0) {
		curr = curr->next;
	}

	if (DEBUG) {
		if (curr != NULL) printf("got it: %s\n", curr->name);
		else printf("not found! \n");
	}

	return curr;
}

struct StringNode *get_random_production(struct DefinitionNode *def) {
	static bool seeded = false;

	if (!seeded) {
		srand(time(NULL));
		seeded = true;
	}

	if (DEBUG) printf("Getting random production\n");
	int r = rand()%(def->productions->size);
	if (DEBUG) printf("random index is %d\n", r);
	struct ProductionNode *p = def->productions->first;

	for (int i = 0; i < r; ++i) p = p->next;

	if (DEBUG) print_linked(p->names), putchar('\n');

	return p->names->first;
}

struct StringNode *append_string(struct StringList *list, char* word) {
	struct StringNode *new = malloc(sizeof(struct StringNode));

	new->value = word;
	new->next = NULL;
	
	if (list->first == NULL) list->first = list->last = new;
	else list->last = list->last->next = new;

	(list->size)++;

	return new;
}

struct ProductionNode *append_production(struct ProductionList *list, struct ProductionNode* production) {
	production->next = NULL;
	
	if (list->first == NULL) list->first = list->last = production;
	else list->last = list->last->next = production;

	(list->size)++;

	return production;
}

struct DefinitionNode *append_definition(struct DefinitionList *list, struct DefinitionNode* definition) {
	definition->next = NULL;
	
	if (list->first == NULL) list->first = list->last = definition;
	else list->last = list->last->next = definition;

	(list->size)++;

	return definition;
}

void print_linked(struct StringList *list) {
	struct StringNode *current = list->first;
	while (current != NULL) {
		printf("%s ", current->value);
		current = current->next;
	}
}

void print_definitions(struct DefinitionList *definitions) {
	struct DefinitionNode *d = definitions->first;
	while (d != NULL) {
		printf("DEFINITION %s\n", d->name);
		struct ProductionNode *p = d->productions->first;
		while (p != NULL) {
			print_linked(p->names);
			p = p->next;
			printf("\n");
		}
		putchar('\n');
		d = d->next;
	}
}
