CC = gcc
CFLAGS = -I ../m/lib 
OUT = -o bin/generate_grammar


PROG = generate_grammar
OBJS = generate_grammar.o grammar_parser.o ../m/lib/m_basics.o
SRCS = generate_grammar.c grammar_parser.c ../m/lib/m_basics.c
DEPS = ../m/lib/m_basics.h grammar_parser.h

%.o: %.c $(DEPS)
	$(CC) $(DEBUG) -c -o $@ $< $(CFLAGS)

$(PROG): $(OBJS)
	$(CC) $(DEBUG) $(OUT) $(CFLAGS) $(OBJS)

run:
	./bin/generate_grammar conto.g

debug: DEBUG = -DDEBUG
debug: $(PROG)
