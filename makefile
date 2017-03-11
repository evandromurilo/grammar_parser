CC = gcc
CFLAGS = -I ../m/lib 
OUT = -o bin/grammar_parser


PROG = grammar_parser
OBJS = grammar_parser.o ../m/lib/m_basics.o
SRCS = grammar_parser.c ../m/lib/m_basics.c
DEPS = ../m/lib/m_basics.h grammar_parser.h

%.o: %.c $(DEPS)
	$(CC) $(DEBUG) -c -o $@ $< $(CFLAGS)

$(PROG): $(OBJS)
	$(CC) $(DEBUG) $(OUT) $(CFLAGS) $(OBJS)

run:
	./bin/grammar_parser < conto.g

debug: DEBUG = -DDEBUG
debug: $(PROG)
