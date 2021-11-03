# include <stdio.h>
# include <string.h>
# include "cc.h"
# include "semutil.h"
# include "sem.h"
# include "sym.h"

#define MAXLINES 80
#define MAXARGS 80

int labelnum = 0;
static char quadbuf[4096];
int numlabels = 0;
int numblabels = 0;
int number_of_arguments = 0;

// The following are declared in semutil.c
extern int formalnum;                  /* number of formal arguments */
extern char formaltypes[];             /* types of formal arguments  */
extern char formalnames[][MAXLINES];   /* names of formal arguments  */
extern int localnum;                   /* number of local variables  */
extern char localtypes[];              /* types of local variables   */
extern char localnames[][MAXLINES];    /* names of local variables   */
extern int localwidths[];              /* widths of local variables  */

// function call arguments
struct sem_rec *function_arguments[MAXARGS];


/*
 * backpatch - backpatch list of quadruples starting at p with k
 */
void backpatch(struct sem_rec *p, int k)
{
   fprintf(stderr, "sem: backpatch not implemented\n");
}

/*
 * bgnstmt - encountered the beginning of a statement
 */
void bgnstmt()
{
   extern int lineno;
   fprintf(stdout, "bgnstmt %d\n", lineno);
}

/*
 * call - procedure invocation
 */
struct sem_rec *call(char *f, struct sem_rec *args)
{
    if (args == NULL)
    {
        if (number_of_arguments != 0)
            yyerror("call() was passed a null pointer but number_of_arguments wasn't 0");
    }
    else
    {
        if (number_of_arguments == 0) {
            number_of_arguments = 1;
            function_arguments[0] = args;
        }
    }
    for (int i = 0; i < number_of_arguments; i++)
        printf("argi t%d\n", function_arguments[i]->s_place);
    struct sem_rec *p;
    int ftnum = nexttemp();
    sprintf(quadbuf, "t%d := global %s", ftnum, f);
    printf("%s\n", quadbuf);
    int quadnum = nexttemp();
    sprintf(quadbuf, "t%d := fi t%d %d ", quadnum, ftnum, number_of_arguments);
    printf("%s", quadbuf);
    if (number_of_arguments > 0)
    {
        for (int i = 0; i < number_of_arguments; i++)
            printf("t%d ", function_arguments[i]->s_place);
        printf("\n");
    }
    number_of_arguments = 0;
    return ((struct sem_rec*) NULL);
}

/*
 * ccand - logical and
 */
struct sem_rec *ccand(struct sem_rec *e1, int m, struct sem_rec *e2)
{
   fprintf(stderr, "sem: ccand not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * ccexpr - convert arithmetic expression to logical expression
 */
struct sem_rec *ccexpr(struct sem_rec *e)
{
   //fprintf(stderr, "sem: ccexpr not implemented\n");
   //return ((struct sem_rec *) NULL);

   int trueLabel = ++numblabels;
   int falseLabel = ++numblabels;
   sprintf(quadbuf, "bt t%d B%d\n", e->s_place, trueLabel);
   fprintf(stdout, "%s", quadbuf);
   sprintf(quadbuf, "br B%d\n", falseLabel);
   fprintf(stdout, "%s", quadbuf);
   return(node(0, 0, node(trueLabel, 0, NULL, NULL), node(falseLabel, 0, NULL, NULL)));
}

/*
 * ccnot - logical not
 */
struct sem_rec *ccnot(struct sem_rec *e)
{
   fprintf(stderr, "sem: ccnot not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * ccor - logical or
 */
struct sem_rec *ccor(struct sem_rec *e1, int m, struct sem_rec *e2)
{
   fprintf(stderr, "sem: ccor not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * con - constant reference in an expression
 */
struct sem_rec *con(char *x)
{
   //fprintf(stderr, "sem: con not implemented\n");
   //return ((struct sem_rec *) NULL);

   struct id_entry *p;
   if ((p = lookup(x, 0)) == NULL)
   {
       p = install(x, 0);
       p -> i_type = T_INT;
       p -> i_scope = GLOBAL;
       p -> i_defined = 1;
   }
   int quadnum = nexttemp();
   sprintf(quadbuf, "t%d := %s\n", quadnum, x);
   fprintf(stdout, "%s", quadbuf);
   return node(quadnum, p -> i_type, NULL, NULL);
}

/*
 * dobreak - break statement
 */
void dobreak()
{
   fprintf(stderr, "sem: dobreak not implemented\n");
}

/*
 * docontinue - continue statement
 */
void docontinue()
{
   fprintf(stderr, "sem: docontinue not implemented\n");
}

/*
 * dodo - do statement
 */
void dodo(int m1, int m2, struct sem_rec *e, int m3)
{
   fprintf(stderr, "sem: dodo not implemented\n");
}

/*
 * dofor - for statement
 */
void dofor(int m1, struct sem_rec *e2, int m2, struct sem_rec *n1,
           int m3, struct sem_rec *n2, int m4)
{
   fprintf(stderr, "sem: dofor not implemented\n");
}

/*
 * dogoto - goto statement
 */
void dogoto(char *id)
{
   fprintf(stderr, "sem: dogoto not implemented\n");
}

/*
 * doif - one-arm if statement
 */
void doif(struct sem_rec *e, int m1, int m2)
{
   //fprintf(stderr, "sem: doif not implemented\n");
    sprintf(quadbuf, "B%d=L%d\n", e-> back.s_link -> s_place, m1);
    fprintf(stdout, "%s", quadbuf);
    sprintf(quadbuf, "B%d=L%d\n", e-> s_false -> s_place, m2);
    fprintf(stdout, "%s", quadbuf);
    return;
}

/*
 * doifelse - if then else statement
 */
void doifelse(struct sem_rec *e, int m1, struct sem_rec *n,
                         int m2, int m3)
{
   fprintf(stderr, "sem: doifelse not implemented\n");
}

/*
 * doret - return statement
 */
void doret(struct sem_rec *e)
{
   //fprintf(stderr, "sem: doret not implemented\n");
   char type = tsize(e -> s_mode) == 4 ? 'i' : 'f';
   sprintf(quadbuf, "ret%c t%d\n", type, e -> s_place);
   fprintf(stdout, "%s", quadbuf);
}

/*
 * dowhile - while statement
 */
void dowhile(int m1, struct sem_rec *e, int m2, struct sem_rec *n,
             int m3)
{
   fprintf(stderr, "sem: dowhile not implemented\n");
}

/*
 * endloopscope - end the scope for a loop
 */
void endloopscope(int m)
{
   fprintf(stderr, "sem: endloopscope not implemented\n");
}

/*
 * exprs - form a list of expressions
 */
struct sem_rec *exprs(struct sem_rec *l, struct sem_rec *e)
{
    //printf("l->s_place: %d\ne->s_place: %d\n", l->s_place, e->s_place);
    //printf("argi t%d\n", l->s_place);
    //printf("argi t%d\n", e->s_place);
    if (number_of_arguments == 0)
    {
        function_arguments[0] = l;
        function_arguments[1] = e;
        number_of_arguments = 2;
    }
    else
    {
        function_arguments[number_of_arguments] = e;
        number_of_arguments++;
    }
    return l;
}

/*
 * fhead - beginning of function body
 */
void fhead(struct id_entry *p)
{
    sprintf(quadbuf, "func %s %d\n", p->i_name, p->i_type);
    fprintf(stdout, "%s", quadbuf);
    int i;
    for (i = 0; i < formalnum; i++) {
        int type = formaltypes[i] == 'i' ? T_INT : T_DOUBLE;
        int width = type == T_INT ? 4 : 8;
        sprintf(quadbuf, "formal %s %d %d\n", formalnames[i], type, width);
        fprintf(stdout, "%s", quadbuf);
    }
    for (i = 0; i < localnum; i++) {
        int type = localtypes[i] == 'i' ? T_INT : T_DOUBLE;
        if (localwidths[i] > 1)
            type |= T_ARRAY;
        int width = (type & T_INT) ? 4 * localwidths[i] : 8 * localwidths[i];
        sprintf(quadbuf, "localloc %s %d %d\n", localnames[i], type, width);
        fprintf(stdout, "%s", quadbuf);
    }
}

/*
 * fname - function declaration
 */
struct id_entry *fname(int t, char *id)
{
   struct id_entry *p;

   if ((p = lookup(id, 0)) == NULL) {
       p = install(id, 0);
   }
   else if (p->i_defined)
       yyerror("procedure is previously defined");
   else if (p->i_type != t)
       yyerror("procedure type does not match");

   p->i_type = t;
   p->i_scope = GLOBAL;
   p->i_defined = 1;
   localnum = formalnum = 0;
   enterblock();
   return p;
}

/*
 * ftail - end of function body
 */
void ftail()
{
   //fprintf(stderr, "sem: ftail not implemented\n");
    fprintf(stdout, "fend\n");
    leaveblock();
}

/*
 * id - variable reference
 */
struct sem_rec *id(char *x)
{
    struct id_entry *p;
    if ((p = lookup(x, 0)) == NULL)
    {
        yyerror("undeclared identifier");
    }
    int quadnum = nexttemp();
    if (p->i_scope == GLOBAL)
        sprintf(quadbuf, "t%d := global %s\n", quadnum, x);
    else if (p->i_scope == PARAM)
        sprintf(quadbuf, "t%d := param %s %d\n", quadnum, x, p->i_offset);
    else if (p->i_scope == LOCAL)
        sprintf(quadbuf, "t%d := local %s %d\n", quadnum, x, p->i_offset);

    fprintf(stdout, "%s", quadbuf);
    return (node(quadnum, p->i_type|T_ADDR, NULL, NULL));

}

/*
 * sindex - subscript
 */
struct sem_rec *sindex(struct sem_rec *x, struct sem_rec *i)
{
    //fprintf(stderr, "sem: sindex not implemented\n");
    //return ((struct sem_rec *) NULL);
    int quadnum = nexttemp();
    char type = x->s_mode & T_INT ? 'i' : 'f';
    sprintf(quadbuf, "t%d := t%d []%c t%d", quadnum, x->s_place, type, i->s_place);
    printf("%s\n", quadbuf);
    return node(quadnum, x->s_mode, NULL, NULL);
}

/*
 * labeldcl - process a label declaration
 */
void labeldcl(char *id)
{
   /* you may assume the maximum number of C label declarations is 50 */
   fprintf(stderr, "sem: labeldcl not implemented\n");
}

/*
 * m - generate label and return next temporary number
 */
int m()
{
   //fprintf(stderr, "sem: m not implemented\n");
   //return (0);
   printf("label L%d\n", ++numlabels);
   return numlabels;
}

/*
 * n - generate goto and return backpatch pointer
 */
struct sem_rec *n()
{
    printf("br B%d\n", numlabels);
    return numlabels;
}

/*
 * op1 - unary operators
 */
struct sem_rec *op1(char *op, struct sem_rec *y)
{
   if (*op == '@')
   {
       y->s_mode &= ~T_ADDR;

       int quadnum = nexttemp();
       char type = y->s_mode & T_INT ? 'i' : 'f';
       sprintf(quadbuf, "t%d := @%c t%d\n", quadnum, type, y->s_place);
       fprintf(stdout, "%s", quadbuf);
       return (node(quadnum, y->s_mode, NULL, NULL));
   }
   else
   {
       fprintf(stderr, "sem: op1 not implemented\n");
       return ((struct sem_rec *) NULL);
   }
}

/*
 * op2 - arithmetic operators
 */
struct sem_rec *op2(char *op, struct sem_rec *x, struct sem_rec *y)
{
   if (*op == '+')
   {
       int quadnum = nexttemp();
       char type = tsize(x->s_mode) == 4 ? 'i' : 'f';
       sprintf(quadbuf, "t%d = t%d +%c t%d\n", quadnum, x->s_place, type, y->s_place);
       fprintf(stdout, "%s", quadbuf);
       return node(quadnum, x->s_mode, NULL, NULL);
   }
   else if (*op == '-')
   {
       int quadnum = nexttemp();
       char type = tsize(x->s_mode) == 4 ? 'i' : 'f';
       sprintf(quadbuf, "t%d = t%d -%c t%d\n", quadnum, x->s_place, type, y->s_place);
       fprintf(stdout, "%s", quadbuf);
       return node(quadnum, x->s_mode, NULL, NULL);
   }
   else if (*op == '*')
   {
       int quadnum = nexttemp();
       char type = tsize(x->s_mode) == 4 ? 'i' : 'f';
       sprintf(quadbuf, "t%d = t%d *%c t%d\n", quadnum, x->s_place, type, y->s_place);
       fprintf(stdout, "%s", quadbuf);
       return node(quadnum, x->s_mode, NULL, NULL);
   }
   else if (*op == '/')
   {
       int quadnum = nexttemp();
       char type = tsize(x->s_mode) == 4 ? 'i' : 'f';
       sprintf(quadbuf, "t%d = t%d /%c t%d\n", quadnum, x->s_place, type, y->s_place);
       fprintf(stdout, "%s", quadbuf);
       return node(quadnum, x->s_mode, NULL, NULL);
   }
   else if (*op == '%')
   {
       int quadnum = nexttemp();
       char type = tsize(x->s_mode) == 4 ? 'i' : 'f';
       sprintf(quadbuf, "t%d = t%d %%c t%d\n", quadnum, x->s_place, type, y->s_place);
       fprintf(stdout, "%s", quadbuf);
       return node(quadnum, x->s_mode, NULL, NULL);
   }
   else
   {
       fprintf(stderr, "sem: op2 not implemented\n");
       return ((struct sem_rec *) NULL);
   }
}

/*
 * opb - bitwise operators
 */
struct sem_rec *opb(char *op, struct sem_rec *x, struct sem_rec *y)
{
   fprintf(stderr, "sem: opb not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * rel - relational operators
 */
struct sem_rec *rel(char *op, struct sem_rec *x, struct sem_rec *y)
{
    if ((strcmp(op, ">") == 0)  ||
        (strcmp(op, "<") == 0)  ||
        (strcmp(op, "==") == 0) ||
        (strcmp(op, ">=") == 0) ||
        (strcmp(op, "<=") == 0) ||
        (strcmp(op, "!=") == 0))
    {
        char type = x->s_mode & T_INT ? 'i' : 'f';
        int quadnum = nexttemp();
        sprintf(quadbuf, "t%d := t%d %s%c t%d\n", quadnum, x -> s_place, op, type, y->s_place);
        fprintf(stdout, "%s", quadbuf);
        return ccexpr(node(quadnum, x->s_mode, NULL, NULL));
    }
    /*if (strcmp(op, "==") == 0)
    {
        char type = x->s_mode & T_INT ? 'i' : 'f';
        int quadnum = nexttemp();
        sprintf(quadbuf, "t%d := t%d %s%c t%d\n", quadnum, x -> s_place, op, type, y->s_place);
        fprintf(stdout, "%s", quadbuf);
        return ccexpr(node(quadnum, x->s_mode, NULL, NULL));
    }*/
    else{
        fprintf(stderr, "sem: rel not implemented\n");
        return ((struct sem_rec *) NULL);
    }
}

/*
 * set - assignment operators
 */
struct sem_rec *set(char *op, struct sem_rec *x, struct sem_rec *y) {
    int quadnum;
    char type = x->s_mode & T_INT ? 'i' : 'f';
    if (*op == '\0')
    {
        quadnum = nexttemp();
        sprintf(quadbuf, "t%d := t%d =%c t%d\n", quadnum, x->s_place, type, y->s_place);
    }
    else
    {
        struct sem_rec *o = op1("@", x);
        struct sem_rec *p = op2(op, o, y);
        quadnum = nexttemp();
        sprintf(quadbuf, "t%d := t%d =%c t%d\n", quadnum, x->s_place, type, p->s_place);
    }
    fprintf(stdout, "%s", quadbuf);
    return node(quadnum, x->s_mode, NULL, NULL);
    /*else
    {
        fprintf(stderr, "sem: set not implemented\n");
        return ((struct sem_rec *) NULL);
    }*/
}

/*
 * startloopscope - start the scope for a loop
 */
void startloopscope()
{
   /* you may assume the maximum number of loops in a loop nest is 50 */
   fprintf(stderr, "sem: startloopscope not implemented\n");
}

/*
 * string - generate code for a string
 */
struct sem_rec *string(char *s)
{
    struct id_entry *p;
    if ((p = lookup(s, 0)) == NULL)
    {
        p = install(s, 0);
        p -> i_type = T_STR;
        p -> i_scope = GLOBAL;
        p -> i_defined = 1;
    }
    int quadnum = nexttemp();
    sprintf(quadbuf, "t%d := %s\n", quadnum, s);
    fprintf(stdout, "%s", quadbuf);
    return node(quadnum, p->i_type, NULL, NULL);
}

