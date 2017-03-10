#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "m_basics.h"

#define MAX_LINE_SIZE 100
#define TEMP_MAX 100

struct StringNode {
	char* value;
	struct StringNode *next;
};

struct StringList {
	struct StringNode *first;
	struct StringNode *last;
};

struct Product {
	int size;
	struct StringList *names;
};

struct Definition {
	char* name;
	int size;
	struct Product products[TEMP_MAX];
};

int split_linked(struct StringList *list, int size, char* str, char goal);
void print_linked(struct StringList *list);
struct StringNode *append_string(struct StringList *list, char* word);

int main(void) {
	struct Definition definitions[TEMP_MAX];
	int size = 0;
	char line[MAX_LINE_SIZE];
	int line_size;

	while (true) {
		struct Definition *def = malloc(sizeof(struct Definition));

		discard_until('{');
		discard_line();

		line_size = read_line(line, MAX_LINE_SIZE);
		if (line_size == 0) break;

		def->name = malloc(line_size+1);
		strcpy(def->name, line);
		def->size = 0;

		printf("DEFINITION NAME: %s\n", line);

		while (true) {
			discard_while(" \n\t");

			char first = read_char();
			if (first == '}') break;
			else push_char(first);
				
			line_size = read_until(';', line, MAX_LINE_SIZE);
			printf("LINE: %s\n", line);
			read_char(); // discard ';'

			if (line_size == 0) break;

			struct Product *p = malloc(sizeof(struct Product));
			p->names = malloc(sizeof(struct StringList));
			p->size = split_linked(p->names, 100, line, ' ');

			def->products[def->size++] = *p;
		}

		if (line_size == 0) break;

		definitions[size++] = *def;
	}

	for (int d = 0; d < size; ++d) {
		printf("DEFINITION %s\n", definitions[d].name);
		for (int i = 0; i < definitions[d].size; ++i) {
			print_linked(definitions[d].products[i].names);
			printf("\n");
		}
		putchar('\n');
	}
	return 0;
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
		printf("Read word: %s\n", list->last->value);
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

void print_linked(struct StringList *list) {
	struct StringNode *current = list->first;
	while (current != NULL) {
		printf("%s ", current->value);
		current = current->next;
	}
}
