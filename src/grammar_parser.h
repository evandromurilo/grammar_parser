#ifndef GRAMMAR_PARSER_H
#define GRAMMAR_PARSER_H

#include <stdbool.h>
#include "../lib/m_list.h"
#include "../lib/hash.h"

#define MAX_LINE_SIZE 10000
#define TEMP_MAX 100

/* a Definition is a name + a list of possible productions
 * a Producion is basically a list of strings */

/* the structs are all linked lists, even though definitions
 * would be better as a hashmap */

struct DefinitionNode {
	char* name;
	struct LinkedList *productions;
};

// parse: takes the filename of a grammar file and parses it
// returns a list of definitions (the grammar) or NULL if it can't read the file
void *parse(struct Hashtable *grammar, char* filename);

// expand: expands 'production' into a StringList
// for every string, if it is a definition, expands it; if it is not, appends it to 'strs'
void expand(struct Hashtable *grammar, struct LinkedList *production, struct LinkedList *strs);

// get_random_production:
// returns the first StringNode of a random production from 'def'
struct LinkedList *get_random_production(struct DefinitionNode *def);


#endif
