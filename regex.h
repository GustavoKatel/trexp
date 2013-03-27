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
	//
	int break_point;

}tRegex;



extern tRegex *regex_new(const char *regex_string);

extern int regex_get_size_max(tRegex *regex);

extern void regex_go_min_operator(tRegex *regex, int cond_index);

extern int regex_total_simb_cond(tRegex *regex);

/**
* Increments only one case in the case_list.
* @param tRegex* pointer to the regex struct
* @param int index of the case
* @return int 0 if the max of the conditional was not reached, otherwise returns not 0
*/
extern int regex_increment_case(tRegex *regex, int index);

extern void regex_increment_cond(tRegex *regex, int dist);

extern char *regex_next_try(tRegex *regex, int match_size);

extern void regex_destroy(tRegex *regex);

extern void regex_destroy_cond(tCond *cond);

extern void regex_prepare(tRegex *regex);

extern int regex_compare(const char *test, const char *word);

extern int regex_check(const char *regex_string, const char *word);

extern int regex_check_re(tRegex *regex, const char *word);

void (*regex_log_func)(const char *msg);
#endif
