#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "regex.h"

int main()
{

	char *regex_string = "ab(a)+(ab)*";
	char *word = "abaababab";

	tRegex *regex = process_regex(regex_string);

	printf("regex: %s\n",regex_string);
	printf("word: %s\n",word);
	printf("base: %s\n",regex->base);
	printf("incond: %d\ncond_count: %d\n",regex->incond, regex->cond_count);

	int i;
	for(i=0;i<regex->cond_count;i++)
	{
		tCond *cond = regex->cond_list[i];
		printf("cond #%d:\n",i);
		printf("\tsimbolos_count: %d\n",cond->simbolos_count);
		printf("\tsimbolos: %s\n",cond->simbolos);
		printf("\toperador: %c\n",cond->operador);
		printf("\tbase_index: %d\n",cond->base_index);

	}

	for(i=0;i<regex->cond_count;i++)
		printf("cond #%d start count: %d\n",i,regex->case_list[i]);

	char *try = next_try(regex, strlen(word));
	while(try)
	{
		printf("try: %s - res: ",try);
		printf("%s\n", (strcmp(try, word)==0 ? "match!" : "doesn't match!" ) );
		free(try);
		try = next_try(regex, strlen(word));
	}
	regex_destroy(regex);

	return 0;
}
