#ifndef GRAMMAR_PARSER_H
#define GRAMMAR_PARSER_H

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

struct ProductNode {
	int size;
	struct StringList *names;
	struct ProductNode *next;
};

struct ProductList {
	struct ProductNode *first;
	struct ProductNode *last;
};

struct DefinitionNode {
	char* name;
	int size;
	struct ProductList *products;
	struct DefinitionNode *next;
};

struct DefinitionList {
	struct DefinitionNode *first;
	struct DefinitionNode *last;
};

struct DefinitionList *parse();
int split_linked(struct StringList *list, int size, char* str, char goal);
void print_definitions(struct DefinitionList *definitions);
void print_linked(struct StringList *list);
struct StringNode *append_string(struct StringList *list, char* word);
struct ProductNode *append_product(struct ProductList *list, struct ProductNode* product);
struct DefinitionNode *append_definition(struct DefinitionList *list, struct DefinitionNode *definition);

#endif
