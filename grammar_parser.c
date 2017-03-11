#include "grammar_parser.h"

#ifdef DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

int main(void) {
	struct DefinitionList *grammar = parse();
	print_definitions(grammar);

	return 0;
}

struct DefinitionList *parse() {
	struct DefinitionList *definitions = malloc(sizeof(struct DefinitionList));
	definitions->first = NULL;
	definitions->last = NULL;

	int size = 0;
	char line[MAX_LINE_SIZE];
	int line_size;

	// definition level
	while (true) {
		struct DefinitionNode *def = malloc(sizeof(struct DefinitionNode));
		def->products = malloc(sizeof(struct ProductList));
		def->products->first = NULL;
		def->products->last = NULL;

		discard_until('{');
		read_char();
		discard_while(" \n\t");

		line_size = read_line(line, MAX_LINE_SIZE);
		if (line_size == 0) break;

		def->name = malloc(line_size+1);
		strcpy(def->name, line);
		def->size = 0;

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

			struct ProductNode *p = malloc(sizeof(struct ProductNode));
			p->names = malloc(sizeof(struct StringList));
			p->size = split_linked(p->names, 100, line, ' ');

			append_product(def->products, p);
		}

		if (line_size == 0) break;

		append_definition(definitions, def);
	}

	return definitions;
}

#define MAX_WORD_SIZE 100
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
		if (DEBUG) printf("Read word: %s\n", list->last->value);
		++total;
	}

	return total;
}

struct StringNode *append_string(struct StringList *list, char* word) {
	struct StringNode *new = malloc(sizeof(struct StringNode));

	new->value = word;
	new->next = NULL;
	
	if (list->first == NULL) list->first = list->last = new;
	else list->last = list->last->next = new;

	return new;
}

struct ProductNode *append_product(struct ProductList *list, struct ProductNode* product) {
	product->next = NULL;
	
	if (list->first == NULL) list->first = list->last = product;
	else list->last = list->last->next = product;

	return product;
}

struct DefinitionNode *append_definition(struct DefinitionList *list, struct DefinitionNode* definition) {
	definition->next = NULL;
	
	if (list->first == NULL) list->first = list->last = definition;
	else list->last = list->last->next = definition;

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
		struct ProductNode *p = d->products->first;
		while (p != NULL) {
			print_linked(p->names);
			p = p->next;
			printf("\n");
		}
		putchar('\n');
		d = d->next;
	}
}
