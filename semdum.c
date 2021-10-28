# include <stdio.h>
# include "cc.h"
# include "semutil.h"
# include "sem.h"
# include "sym.h"

#define MAXLINES 80

int labelnum = 0;
static char quadbuf[4096];

// The following are declared in semutil.c
extern int formalnum;                  /* number of formal arguments */
extern char formaltypes[];             /* types of formal arguments  */
extern char formalnames[][MAXLINES];   /* names of formal arguments  */
extern int localnum;                   /* number of local variables  */
extern char localtypes[];              /* types of local variables   */
extern char localnames[][MAXLINES];    /* names of local variables   */
extern int localwidths[];              /* widths of local variables  */

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
   fprintf(stdout, "bgntstmt %d\n", lineno);
}

/*
 * call - procedure invocation
 */
struct sem_rec *call(char *f, struct sem_rec *args)
{
   fprintf(stderr, "sem: call not implemented\n");
   return ((struct sem_rec *) NULL);
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
   fprintf(stderr, "sem: ccexpr not implemented\n");
   return ((struct sem_rec *) NULL);
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
   fprintf(stderr, "sem: con not implemented\n");
   return ((struct sem_rec *) NULL);
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
   fprintf(stderr, "sem: doif not implemented\n");
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
   fprintf(stderr, "sem: doret not implemented\n");
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
   fprintf(stderr, "sem: exprs not implemented\n");
   return ((struct sem_rec *) NULL);
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
   fprintf(stderr, "sem: ftail not implemented\n");
}

/*
 * id - variable reference
 */
struct sem_rec *id(char *x)
{
    fprintf(stderr, "sem: id not implemented\n");
    return ((struct sem_rec *) NULL);
    struct id_entry *p = lookup(x, 0);
    return node(labelnum, p->i_type|T_ADDR, 0, 0);
}

/*
 * sindex - subscript
 */
struct sem_rec *sindex(struct sem_rec *x, struct sem_rec *i)
{
   fprintf(stderr, "sem: sindex not implemented\n");
   return ((struct sem_rec *) NULL);
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
   fprintf(stderr, "sem: m not implemented\n");
   labelnum++;
   return labelnum;
   //return (0);
}

/*
 * n - generate goto and return backpatch pointer
 */
struct sem_rec *n()
{
   fprintf(stderr, "sem: n not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * op1 - unary operators
 */
struct sem_rec *op1(char *op, struct sem_rec *y)
{
   fprintf(stderr, "sem: op1 not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * op2 - arithmetic operators
 */
struct sem_rec *op2(char *op, struct sem_rec *x, struct sem_rec *y)
{
   fprintf(stderr, "sem: op2 not implemented\n");
   return ((struct sem_rec *) NULL);
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
   fprintf(stderr, "sem: rel not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * set - assignment operators
 */
struct sem_rec *set(char *op, struct sem_rec *x, struct sem_rec *y)
{
   fprintf(stderr, "sem: set not implemented\n");
   return ((struct sem_rec *) NULL);
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
   fprintf(stderr, "sem: string not implemented\n");
   return ((struct sem_rec *) NULL);
}
