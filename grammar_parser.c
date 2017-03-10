#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "m_basics.h"

#define MAX_LINE_SIZE 100
#define TEMP_MAX 100

struct Product {
	int size;
	char* names[TEMP_MAX];
};

struct Definition {
	char* name;
	int size;
	struct Product products[TEMP_MAX];
};

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
			p->size = split(p->names, 100, line, ' ');

			def->products[def->size++] = *p;
		}

		if (line_size == 0) break;

		definitions[size++] = *def;
	}

	for (int d = 0; d < size; ++d) {
		printf("DEFINITION %s\n", definitions[d].name);
		for (int i = 0; i < definitions[d].size; ++i) {
			for (int j = 0; j < definitions[d].products[i].size; ++j) {
				printf("%s ", definitions[d].products[i].names[j]);
			}
			printf("\n");
		}
		putchar('\n');
	}
	return 0;
}
