#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "regex.h"

int main()
{

	char *regex_string = "ab(a)+(ab)*";
	char *word = "abaababab";

	char regex_get_string[255];
	char word_get_string[255];

	while(1)
	{
		printf("Digite a expressao regular: ");
		fgets(regex_get_string, 255, stdin);
		printf("Digite a palavra: ");
		fgets(word_get_string, 255, stdin);


		printf("Regex: %s\n", regex_get_string);
		printf("Word: %s\n", word_get_string);
		printf("test: %s\n", (check(regex_get_string, word_get_string) ? "Match!" : "Not match!" ) );
	}

	return 0;
}
