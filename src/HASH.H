// hash.h - includes for hashing functions

#ifndef __hash__
#define __hash__

#ifndef __alloc__
#include <alloc.h>
#endif

#define MAXNAME 14
#define MAXLEN 128		// max # of chain lengths (for debug listing)

typedef struct element_ {
	struct element_ *next;
	struct element_ **prev;
	char sname[MAXNAME+1];
} BUCKET;

typedef struct hash_tab_ {
	BUCKET	**table;	// pointer to hash table
	short	size;		// max number of elements in table
	short	numsyms;	// number of elements currently in table
} HASH_TAB;

// macro to extract the fieldname from a BUCKET
#define symname(p)	( ((BUCKET *)(p) - 1)->sname )

#ifdef __TURBOC__

unsigned hash(char *name, HASH_TAB *tabp);
char	*addsym(HASH_TAB *table, char *symbol, short value);
void	delsym(HASH_TAB *table, BUCKET *bucket);
char	*findsym(HASH_TAB *table, char *symbol);
HASH_TAB*maketab(unsigned size);
void	hash_debug(HASH_TAB *addr);
void	hash_stats(HASH_TAB *table);
typedef void (* hprint_t)(char *s, void/*BUCKET*/ *b);
void 	hash_print(HASH_TAB *tabp, hprint_t print);

#endif // __TURBOC__

#ifdef __AZTEC__

unsigned hash();
char *addsym();
void delsym();
char *findsym();
HASH_TAB *maketab();
void hash_stats();
short symcmp();
short hash_print();

#endif // __AZTEC__

#endif // __hash__

