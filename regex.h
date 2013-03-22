#ifndef _REGEX_H
#define _REGEX_H

typedef struct {

	int simbolos_count;
	char *simbolos;
	char operador;
	int base_index;

}tCond;

typedef struct {

	int incond;
	int cond_count;
	tCond **cond_list;
	//
	char *base;
	//
	int *case_list;
	int tentativas;

}tRegex;



extern tRegex *process_regex(const char *regex_string);

extern void increment_cond(tRegex *regex, int dist);

extern char *next_try(tRegex *regex, int match_size);

extern int check(const char *regex, const char *word);

extern void regex_destroy(tRegex *regex);

extern void regex_destroy_cond(tCond *cond);

#endif
