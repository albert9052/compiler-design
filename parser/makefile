a.out: lex.yy.c y.tab.c
		gcc lex.yy.c y.tab.c -ll

lex.yy.c: d.l
		lex d.l

y.tab.c: d.y
		yacc -d d.y

clean:
		rm -f lex.yy.c y.tab.c
