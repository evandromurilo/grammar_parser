CC = gcc
CFLAGS = -I ../lib 
OUT = -o ../bin/generate_grammar

PROG = generate_grammar
OBJS = generate_grammar.o grammar_parser.o ../lib/m_basics.o
SRCS = generate_grammar.c grammar_parser.c ../lib/m_basics.c
DEPS = ../lib/m_basics.h grammar_parser.h

%.o: %.c $(DEPS)
	$(CC) $(DEBUG) -c -o $@ $< $(CFLAGS)

$(PROG): $(OBJS)
	$(CC) $(DEBUG) $(OUT) $(CFLAGS) $(OBJS)

run:
	../bin/generate_grammar nota.g

debug: DEBUG = -DDEBUG
debug: $(PROG)
