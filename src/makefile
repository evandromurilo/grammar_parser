CC = gcc
CFLAGS = -I ../lib -g
OUT = -o ../bin/generate_grammar

PROG = generate_grammar
OBJS = generate_grammar.o grammar_parser.o ../lib/m_basics.o ../lib/m_list.o ../lib/hash.o
SRCS = generate_grammar.c grammar_parser.c ../lib/m_basics.c ../lib/m_list.c ../lib/hash.c
DEPS = ../lib/m_basics.h grammar_parser.h ../lib/m_list.h ../lib/hash.h

%.o: %.c $(DEPS)
	$(CC) $(DEBUG) -c -o $@ $< $(CFLAGS)

$(PROG): $(OBJS)
	$(CC) $(DEBUG) $(OUT) $(CFLAGS) $(OBJS)

run:
	../bin/generate_grammar nota.g

debug: DEBUG = -DDEBUG
debug: $(PROG)
