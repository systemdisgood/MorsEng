#include <stdlib.h>
#include <stdio.h>

#define MAX_STR_LEN 1023

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

int main(int argc, char* argv[])
{
	print_if_ok("ints", check_ints());
	
	return 0;
}
