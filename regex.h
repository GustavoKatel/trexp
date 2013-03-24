#ifndef _REGEX_H
#define _REGEX_H

typedef struct {

	int simbolos_count;
	char *simbolos;
	char operador;
	int base_index;

}tCond;

typedef struct {

	char *string;
	//
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

extern int total_simb_cond(tRegex *regex);

extern void increment_cond(tRegex *regex, int dist);

extern char *next_try(tRegex *regex, int match_size);

extern void regex_destroy(tRegex *regex);

extern void regex_destroy_cond(tCond *cond);

extern int compare(const char *test, const char *word);

extern int check(const char *regex_string, const char *word);

extern int check_re(tRegex *regex, const char *word);
#endif
