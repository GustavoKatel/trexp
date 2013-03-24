#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "regex.h"

#define READ_BUFF_MAX 255

//
tRegex *regex_ptr = NULL;
void free_regex_ptr();
//

typedef enum {REGEX, WORD} READING_TYPE;
enum WIN_PAIRS {log=1, info, info_selected, word, regex, regex_bg};

WINDOW *win_main = NULL;

WINDOW *win_log = NULL;
void create_log_box();
void destroy_log_box();
void update_log_box();
//
char **buff=NULL;
int buff_lines=0;
void log_init();
void log_msg(const char *msg);
void log_clear();

WINDOW *win_info = NULL;
void create_info_box();
void destroy_info_box();
void update_info_box();

WINDOW *win_regex = NULL;
void create_regex_box();
void destroy_regex_box();
void update_regex_box();

WINDOW *win_input = NULL;
void create_input_box();
void destroy_input_box();
void update_input_box();
//
READING_TYPE reading_type = WORD;
int reading_state=0;
char read_buff[READ_BUFF_MAX];
int read_buff_pos=0;
void read_buff_clear();
void read_buff_process();
void process_buff_word();
void process_buff_regex();

int main()
{
	win_main = initscr();
	ESCDELAY=0;
	//	use_default_colors();
	start_color();
	raw();
	noecho();
	keypad(stdscr,TRUE);
	/*windows*/
	create_log_box();
	keypad(win_log,TRUE);
	//
	create_info_box();
	keypad(win_info,TRUE);
	//
	create_regex_box();
	keypad(win_regex, TRUE);
	//
	create_input_box();
	keypad(win_input,TRUE);
	//
	log_init();
	//
	int c;
	while((c=getch())!='q' || reading_state)
	{
		if(reading_state && read_buff_pos<READ_BUFF_MAX)
		{
			if(c==KEY_BACKSPACE)
			{
				if(read_buff_pos>0)
					read_buff_pos--;
			}else{
				read_buff[read_buff_pos++]=c;
			}
		}
		switch(c)
		{
			case 'r':
				if(reading_state)
					break;
				//
				reading_type = REGEX;
				reading_state=1;
				break;
			case 'w':
				if(reading_state)
					break;
				//
				reading_type=WORD;
				reading_state=1;
				break;
			case 27:
				reading_state=0;
				read_buff_clear();
				break;
			case '\n':
			case KEY_ENTER:
				if(reading_state)
				{
					read_buff_process();
					reading_state=0;
					read_buff_clear();
				}
				break;
		}
		//
		update_log_box();
		update_info_box();
		update_regex_box();
		update_input_box();
	}
	destroy_log_box();
	destroy_info_box();
	destroy_regex_box();
	destroy_input_box();
	endwin();
	//
	free_regex_ptr();
	return 0;
}

void log_init()
{
	log_msg("TREX: Try regex.\n");
	//
	log_msg("\tGustavoKatel\n");
	//
	log_msg("\tFarrel\n");
	//
	log_msg("\tCMatchelo\n");
	//
	log_msg("\tSane\n");
}

void log_msg(const char *msg)
{
	char *msg_alloc = (char *)malloc(strlen(msg)+1);
	strcpy(msg_alloc, msg);
	//
	char **p = (char **)realloc(buff, sizeof(buff)*buff_lines+1);
	buff = p;
	buff[buff_lines++]=msg_alloc;
	//
	update_log_box();
}

void log_clear()
{
	if(buff)
	{
		int i;
		for(i=0;i<buff_lines;i++)
			free(buff[i]);
		free(buff);
		buff = NULL;
		buff_lines=0;
	}
}

void create_log_box()
{
	win_log = subwin(win_main, LINES-2, COLS-50, 0, 0);
	wrefresh(win_log);
	//init_pair(info, COLOR_BLACK, COLOR_WHITE);
	//
	update_log_box();

}
void destroy_log_box()
{
	if(win_log)
		delwin(win_log);
}
void update_log_box()
{
	wclear(win_log);
	scrollok(win_log, TRUE);
	wmove(win_log,0,0);
	if(buff)
	{
		int i;
		for(i=0;i<buff_lines;i++)
		{
			if(!buff[i])
				continue;
			//wmove(win_log, i,0);
			wprintw(win_log, buff[i]);
		}
	}
	wrefresh(win_log);
}

void create_info_box()
{
	win_info = subwin(win_main, 1,0, LINES-2, 0);
	wrefresh(win_info);
	init_pair(info, COLOR_BLACK, COLOR_CYAN);
	init_pair(info_selected, COLOR_WHITE, COLOR_CYAN);
	//
	update_info_box();
}
void destroy_info_box()
{
	if(win_info)
		delwin(win_info);
}
void update_info_box()
{
	wclear(win_info);
	wattrset(win_info, COLOR_PAIR(info));
	wbkgd(win_info, COLOR_PAIR(info));
	//
	wmove(win_info, 0,0);
	if(reading_type==REGEX && reading_state) wattrset(win_info, COLOR_PAIR(info_selected));
	wprintw(win_info, "[r]egex");
	if(reading_type==REGEX && reading_state) wattrset(win_info, COLOR_PAIR(info));
	//
	wmove(win_info, 0,7);
	wprintw(win_info, " | ");
	//
	wmove(win_info, 0,10);
	if(reading_type==WORD && reading_state) wattrset(win_info, COLOR_PAIR(info_selected));
	wprintw(win_info, "[w]ord");
	if(reading_type==WORD && reading_state) wattrset(win_info, COLOR_PAIR(info));
	//
	wmove(win_info, 0,16);
	wprintw(win_info," | ");
	//
	wmove(win_info, 0,19);
	wprintw(win_info, "[q]uit");
	//
	wrefresh(win_info);
}

void create_regex_box()
{
	win_regex = subwin(win_main, LINES-2,0, 0,COLS-50);
	wrefresh(win_regex);
	//
	init_pair(regex, COLOR_RED, COLOR_BLACK);
	init_pair(regex_bg, COLOR_WHITE, COLOR_BLACK);
	//
	update_regex_box();
}

void destroy_regex_box()
{
	if(win_regex)
		delwin(win_regex);
}

void update_regex_box()
{
	wclear(win_regex);
	int line=0;
	wmove(win_regex, line,0);
	wprintw(win_regex, "Regex: ");
	//
	wmove(win_regex, line++,7);
	wprintw(win_regex, "%d", regex_ptr);
	//hline
	wmove(win_regex, line++,0);
	whline(win_regex, '-', 50);
	//
	if(regex_ptr)
	{	
		//exp
		wmove(win_regex,line++,0);
		wprintw(win_regex, "Expression: %s",regex_ptr->string);
		//base
		wmove(win_regex,line++,0);
		wprintw(win_regex, "Base: %s",regex_ptr->base);
		//incod
		wmove(win_regex, line++,0);
		wprintw(win_regex, "Total inconditionals: %d",regex_ptr->incond);
		//cond_count
		wmove(win_regex, line++,0);
		wprintw(win_regex, "Total conditionals: %d", regex_ptr->cond_count);
		//cond_list
		int i;
		for(i=0;i<regex_ptr->cond_count;i++)
		{
			wmove(win_regex,line++,0);
			wprintw(win_regex,"Contitional #%d",i);
			//simbolos_count
			wmove(win_regex,line++,0);
			wprintw(win_regex,"\tTotal simbols: %d",regex_ptr->cond_list[i]->simbolos_count);
			//
			//simbolos
			wmove(win_regex,line++,0);
			wprintw(win_regex,"\tSimbols: %s",regex_ptr->cond_list[i]->simbolos);
			//
			//operador
			wmove(win_regex,line++,0);
			wprintw(win_regex,"\tOperator: %c",regex_ptr->cond_list[i]->operador);
			//
			//base_index
			wmove(win_regex,line++,0);
			wprintw(win_regex,"\tBase index: %d",regex_ptr->cond_list[i]->base_index);
			//case_value
			wmove(win_regex,line++,0);
			wprintw(win_regex,"\tWeight: %d", regex_ptr->case_list[i]);
		}
		wmove(win_regex,line++,0);
		wprintw(win_regex,"Attempts for the last word: %d",regex_ptr->tentativas);

	}
	//
	wrefresh(win_regex);	
}

void create_input_box()
{
	win_input = subwin(win_main, 1,0, LINES-1, 0);
	//init_pair(word, COLOR_BLACK, COLOR_WHITE);
	//
	update_input_box();
}
void destroy_input_box()
{
	if(win_input)
		delwin(win_input);
}
void update_input_box()
{
	wclear(win_input);
	if(reading_state)
	{
		wmove(win_input,0,0);
		wprintw(win_input, (reading_type==WORD) ? "w: " : "r: " );
		//
		read_buff[read_buff_pos]='\0';
		wmove(win_input,0,3);
		wprintw(win_input, read_buff);
	}
	//
	wrefresh(win_input);
}

void read_buff_clear()
{
	read_buff_pos=0;
}

void read_buff_process()
{
	if(reading_type==WORD)
		process_buff_word();
	else if(reading_type==REGEX)
		process_buff_regex();
}

void process_buff_word()
{
	if(!regex_ptr)
	{
		log_clear();
		log_msg("You must define a regex!\n");
		return;
	}
	log_msg("Checking the word: ");
	read_buff[read_buff_pos]='\0';
	log_msg(read_buff);
	int res = check_re(regex_ptr,read_buff);
	if(res)
		log_msg("\tMATCH!\n");
	else
		log_msg("\tNOT MATCH!\n");
}

void process_buff_regex()
{
	free_regex_ptr();
	read_buff[read_buff_pos]='\0';
	regex_ptr = process_regex(read_buff);
	log_clear();
	if(regex_ptr)
		log_msg("Regex process: Sucess!\n");
	else
		log_msg("Regex process: Fail!\n");
}

void free_regex_ptr()
{
	if(regex_ptr)
	{
		regex_destroy(regex_ptr);
		regex_ptr=NULL;
	}
}
