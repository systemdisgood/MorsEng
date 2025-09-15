#include <stdlib.h>
#include <stdio.h>

#define MAX_STR_LEN 1023
#define PRINTABLE_CHARS_QUANTITY 75

#define WHWOQBQ 40

const char wav_heading_without_quantity[WHWOQBQ] = {82, 73, 70, 70, 36, 1, 0, 0, 87, 65, 86, 69, 102, 109, 116, 32, 16, 0, 0, 0, 1, 0, 1, 0, 68, 172, 0, 0, 68, 172, 0, 0, 1, 0, 8, 0, 100, 97, 116, 97};


char printable_chars[] = {'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E', 'f', 'F', 'g', 'G', 'e', 'E', 'f', 'F', 'g', 'G', 'h', 'H', 'i', 'I', 'j', 'J', 'k', 'K', 'l', 'L', 'm', 'M', 'n', 'N', 'o', 'O', 'p', 'P', 'q', 'Q', 'r', 'R', 's', 'S', 't', 'T', 'u', 'U', 'v', 'V', 'w', 'W', 'x', 'X', 'y', 'Y', 'z', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '@', '.', ',', ':', '?', '\'', '-', '/', '(', ')', '"', '=', '*'};

int check_ints(void)
{
	int is_not_ok = 0;
	unsigned a = 0;
	a -= 1;
	if(a < 0xFFFFFFFF) is_not_ok = 1;
	if(is_not_ok) return -1;
	return 0;
}

int print_if_ok(char* check_name, int error_code)
{
	if(error_code == 0) printf("%s OK\n", check_name);
	else printf("ERROR WITH %s ERROR CODE %d\n", check_name, error_code);
	return 0;
}

enum Mode {IDLE, STDOUT_OUTPUT, FILE_OUTPUT};
enum Mode mode = IDLE;

enum Dot_dash {DOT, DASH, PAUSE, SPACE, NEW_LINE};

void fprint_dot_dash(FILE* file, int dot_dash)
{
	switch(dot_dash)
	{
		case DOT:
			fprintf(file, ".");
			break;
		case DASH:
			fprintf(file, "-");
			break;
		case PAUSE:
			fprintf(file, " ");
			break;
		case SPACE:
			fprintf(file, "     ");
			break;
		case NEW_LINE:
			fprintf(file, "\n");
	}
}

int main(int argc, char* argv[])
{
	FILE* input_file = NULL;
	FILE* output_file = NULL;
	int input_character = 0;
	int in_printable = 0;
	int not_new_text = 0;
	int was_new_line = 0;
	int was_space = 0;
	print_if_ok("ints", check_ints());
	if(argc < 2)
	{
		printf("Too few arguments!\n");
		return -1;
	} else if(2 == argc)
	{
		mode = STDOUT_OUTPUT;
	}
	else if(3 == argc)
	{
		mode = FILE_OUTPUT;
	}
	else
	{
		printf("Too many arguments!\n");
		return -1;
	}
	if(NULL == (input_file = fopen(argv[1],"r")))
	{
		printf("Can not open input file\n");
		return -1;
	}
	if(FILE_OUTPUT == mode)
	{
		if(NULL == (output_file = fopen(argv[2],"w")))
		{
			printf("Can not open output file\n");
		}
	} else if(STDOUT_OUTPUT == mode)
	{
		output_file = stdout;
	}
	while((input_character = fgetc(input_file)) != EOF)
	{
		/*putchar(input_character);*/
		int i;
		in_printable = 0;
		for(i = 0; i < PRINTABLE_CHARS_QUANTITY; ++i)
		{
			if(input_character == printable_chars[i])
			{
				in_printable = 1;
				break;
			}
		}
		if(in_printable)
		{
			if(was_new_line)
			{
				fprint_dot_dash(output_file, NEW_LINE);
			}
			else if(was_space)
			{
				fprint_dot_dash(output_file, SPACE);
			} 
			else 
			{
				if(not_new_text) 
				{
					fprint_dot_dash(output_file, PAUSE);
				}
				else
				{
					not_new_text = 1;
				}
			}
			was_space = 0;
			was_new_line = 0;
			switch(input_character)
			{
				case ' ':
					in_printable = 0;
					was_space = 1;
					break;
				case '\n':
					in_printable = 0;
					was_new_line = 1;
					break;
				case 'a':
					fprint_dot_dash(output_file, DOT);
					fprint_dot_dash(output_file, DASH);
					break;
			}
		}
		else
		{
			if(' ' == input_character) was_space = 1;
			if('\n' == input_character) was_new_line = 1;
		}
	}
	fprintf(output_file, "\n");
	return 0;
}
