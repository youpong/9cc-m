CC = clang
#CFLAGS = -Wall -g -DYYDEBUG=1
CFLAGS = -Wall -std=c11 -g -D_POSIX_C_SOURCE=200809L
YACC = yacc
LEX = flex

TARGET = 9cc
OBJS = lex.yy.o y.tab.o main.o
LIBS = -ly -ll -lm

all: $(TARGET)

clean:
	- rm -f a.out y.tab.h y.tab.c lex.yy.c lex.yy.h $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

y.tab.c y.tab.h: parse.y
	$(YACC) -d $<
lex.yy.h lex.yy.c: lex.l
	$(LEX) --header-file=lex.yy.h $<

main.o lex.yy.o: y.tab.h
y.tab.o: lex.yy.h
$(OBJS): 9cc.h

.c.o:
	$(CC) -c $< $(CFLAGS) $(DEBUG)
