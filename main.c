#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "regex.h"

void LimpaBuffer();

tRegex *getRegex()
{
	tRegex *regex = NULL;
	char regex_get_string[255];
	while(!regex)
	{
		LimpaBuffer();
		printf("Digite a expressao regular: ");
		fgets(regex_get_string, 255, stdin);
		regex = regex_new(regex_get_string);
	}

}

void LimpaBuffer()
{
	char c = getchar();
	while(c!='\n')
		c = getchar();
}

int leInt(int min, int max)
{
	int teste, i;
	teste = scanf("%d", &i);
	while(teste!=1 || i<min || i>max)
	{
		LimpaBuffer();
		printf("Digite um valor valido!\n.> ");
		teste = scanf("%d", &i);
	}
	return i;
}

int main()
{

	char *regex_string = "ab(a)+(ab)*";
	char *word = "abaababab";

	char word_get_string[255];

	tRegex *regex = NULL;

	int op, loop=1;

	while(loop)
	{
		printf("1 - Nova expressao\n2 - Testar cadeia\n3 - Sair\n.> ");
		op = leInt(1,3);
		switch(op)
		{
			case 1:
				if(regex)
					regex_destroy(regex);
				regex = getRegex();
				break;
			case 2:
				if(!regex)
				{
					printf("Primeiro informe uma expressao valida.\n");
					break;
				}
				LimpaBuffer();
				printf("Digite a cadeia:\n.> ");
				fgets(word_get_string, 255, stdin);
				printf("\tCheck: %s\n", (regex_check_re(regex, word_get_string) ? "MATCH!" : "NOT MATCH!" ));
				break;
			case 3:
				loop = 0;
				break;
		}
		
	}

	if(regex)
		regex_destroy(regex);

	return 0;
}
