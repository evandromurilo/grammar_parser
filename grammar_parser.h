#ifndef GRAMMAR_PARSER_H
#define GRAMMAR_PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "m_basics.h"

#define MAX_LINE_SIZE 1000
#define TEMP_MAX 100

/* a Definition is a name + a list of possible productions
 * a Producion is basically a list of strings */

/* the structs are all linked lists, even though definitions
 * would be better as a hashmap */

struct StringNode {
	char* value;
	struct StringNode *next;
};

struct StringList {
	int size;
	struct StringNode *first;
	struct StringNode *last;
};

struct ProductionNode {
	struct StringList *names;
	struct ProductionNode *next;
};

struct ProductionList {
	int size;
	struct ProductionNode *first;
	struct ProductionNode *last;
};

struct DefinitionNode {
	char* name;
	struct ProductionList *productions;
	struct DefinitionNode *next;
};

struct DefinitionList {
	int size;
	struct DefinitionNode *first;
	struct DefinitionNode *last;
};

// parse: takes the filename of a grammar file and parses it
// returns a list of definitions (the grammar) or NULL if it can't read the file
struct DefinitionList *parse(char* filename);

// split_linked: splits the contents of 'str' into words separated by 'goal'
// stores the words into 'list'
// returns the amount of words found
int split_linked(struct StringList *list, int size, char* str, char goal);

// expand: expands 'production' into a StringList
// for every string, if it is a definition, expands it; if it is not, appends it to 'strs'
void expand(struct DefinitionList *grammar, struct StringNode *production, struct StringList *strs);

// get_random_production:
// returns the first StringNode of a random production from 'def'
struct StringNode *get_random_production(struct DefinitionNode *def);

// get_definition:
// returns the first DefinitionNode of name 'name', or NULL if none is found
struct DefinitionNode *get_definition(struct DefinitionList *grammar, char* name);

// print_definitions: for debug purposes; prints every definition in 'definitions'
void print_definitions(struct DefinitionList *definitions);

// print_linked: print every string in StringList separated by a whitespace
void print_linked(struct StringList *list);

// append_string: appends 'word' into 'list'
struct StringNode *append_string(struct StringList *list, char* word);

// append_string: appends 'production' into 'list'
struct ProductionNode *append_production(struct ProductionList *list, struct ProductionNode* production);

// append_string: appends 'definition' into 'list'
struct DefinitionNode *append_definition(struct DefinitionList *list, struct DefinitionNode *definition);

#endif
