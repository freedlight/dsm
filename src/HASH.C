// hash.c - general purpose hash table functions
// Copyright (c) 1987-1993  Freedlight, Inc.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

/*
	Hash table structures are defined in hash.h. a HASH_TABis a structure
	that contains the table size, the number of elements in the table and
	a pointer to the table itself, this last an array of BUCKET pointers.
	Collisions are resolved by putting the buckets into a double-linked
	list.

	the array pointed to by the HASH_TAB structure is an array of pointers
	to BUCKETs. These buckets each have a "next" field, which points to the
	next bucket in the chain, or NULL if there is no other. The "prev"
	field points to the "next" field in the previous bucket, or the actual
	HASH_TAB element.

	The BUCKET itself is actually a header, similar to that used by malloc().
	The pointer returned by addsym() or findsym() points after this header,
	and can be used as a structure pointer by the application.
*/

// compute hash value
// note that MOD table length is done by calling routine
unsigned hash(char *name, HASH_TAB *tabp)
{
	register unsigned i;

	for (i=0; *name; i += *name++)
		;
	return(i % tabp->size);
}

// make a hash table of indicated size
// useful (prime) sizes are:
//		47, 61, 89, 113, 127, 157, 193,211, 257, 293, 359, 401
HASH_TAB *maketab(unsigned maxsyms)
{
	HASH_TAB *p;

	if ((p = (HASH_TAB *) calloc(1, (maxsyms * sizeof(BUCKET *)) + sizeof(HASH_TAB))) == NULL)
	{
		fprintf(stderr, "no memory for symbol table");
		exit(3);
	}
	p->table = (BUCKET **)(p + 1);
	p->size = maxsyms;
	p->numsyms = 0;
	return(p);
}

// add a symbol to table
char *addsym(HASH_TAB *tabp, char *name, short size)
{
	BUCKET **p, *tmp;
	BUCKET *sym;

	if ((sym = (BUCKET *) calloc(size + sizeof(BUCKET), 1)) == NULL)
	{
		fprintf(stderr, "out of memory for symbols");
		exit(3);
	}
#if 0
	else
		fprintf(stderr, "mem: %ld\n", coreleft());
#endif
	strncpy(sym->sname, name, MAXNAME);
	p = &(tabp->table)[ hash(name,tabp) ];
	tmp = *p;
	*p = sym;
	sym->prev = p;
	sym->next = tmp;
	if (tmp)
		tmp->prev = &sym->next;
	tabp->numsyms++;
	return((char *)(sym + 1));
}

// return pointer to hash table element having indicated name
// returns NULL if not found
char *findsym(HASH_TAB *tabp, char *name)
{
	BUCKET *p;

	p = (tabp->table)[ hash(name,tabp) ];
	while (p && strncmp(name, p->sname, MAXNAME))
		p = p->next;
	return((char *)(p ? p+1 : NULL));
}

// compare symbols
static int symcmp(const void _FAR *s1, const void _FAR *s2)
{
	BUCKET **p1 = (BUCKET **)s1, **p2 = (BUCKET **)s2;
	return(strcmp((*p1)->sname, (*p2)->sname));
}

// print the hash table, sorted by key
void hash_print(HASH_TAB *tabp, hprint_t print)
{
	BUCKET **outtab, **outp, *sym, **symtab;
	short i;

	if ((outtab = (BUCKET **) malloc(tabp->numsyms * sizeof(BUCKET *))) == NULL)
	{
		fprintf(stderr, "no memory to print symbols");
		exit(3);
	}
	outp = outtab;
	for (symtab = tabp->table, i=tabp->size; --i>=0; symtab++)
		for (sym=*symtab; sym; sym = sym->next)
			*outp++ = sym;
	qsort(outtab, tabp->numsyms, sizeof(BUCKET *), symcmp);
	for (outp = outtab, i=tabp->numsyms; --i>=0; outp++)
		(*print)( (*outp)->sname, (*outp)+1);
	free(outtab);
}


