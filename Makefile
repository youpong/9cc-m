CC = clang
#CFLAGS = -Wall -g -DYYDEBUG=1
CFLAGS = -Wall -std=c11 -g -D_POSIX_C_SOURCE=200809L
YACC = yacc
LEX = flex

TARGET = 9cc
OBJS = lex.yy.o y.tab.o main.o myinput.o util.o
LIBS = -ly -ll -lm

all: $(TARGET)

clean:
	- rm -f *.o test_lex a.out \
                y.tab.h y.tab.c lex.yy.c lex.yy.h $(TARGET)

test: $(TARGET)
	./test.sh

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

y.tab.c y.tab.h: parse.y
	$(YACC) -d $<
lex.yy.h lex.yy.c: lex.l
	$(LEX) --header-file=lex.yy.h $<

main.o lex.yy.o: y.tab.h util.h
y.tab.o: lex.yy.h util.h
$(OBJS): 9cc.h

# test yylex
test_lex: lex.yy.o y.tab.o test_lex.o myinput.o
	$(CC) -o $@  lex.yy.o y.tab.o test_lex.o myinput.o $(LIBS)
test_lex.o: lex.yy.h y.tab.h

.c.o:
	$(CC) -c $< $(CFLAGS) $(DEBUG)
