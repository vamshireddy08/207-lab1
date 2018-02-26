#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
#define DELIM "."

 
/* return 1 if string contain only digits, else return 0 */
int valid_digit(char *ip_str)
{
    while (*ip_str) {
        if (*ip_str >= '0' && *ip_str <= '9')
            ++ip_str;
        else
            return 0;
    }
    return 1;
}
 
/* return 1 if IP string is valid, else return 0 */
int is_valid_ip(char *ip_str)
{
    int i, num, dots = 0;
    char *ptr;
 
    if (ip_str == NULL)
        return 0;
 
    
    ptr = strtok(ip_str, DELIM);
 
    if (ptr == NULL)
        return 0;
 
    while (ptr) {
 
        /* after parsing string, it must contain only digits */
        if (!valid_digit(ptr))
            return 0;
 
        num = atoi(ptr);
 
        /* check for valid IP */
        if (num >= 0 && num <= 255) {
            /* parse remaining string */
            ptr = strtok(NULL, DELIM);
            if (ptr != NULL)
                ++dots;
        } else
            return 0;
    }
 
    /* valid IP string must contain 3 dots */
    if (dots != 3)
        return 0;
    return 1;
}


int main()
{	int i;
    char ip1[] = "128.0.0.1";
    char ip2[] = "125.16.100.1";
    char ip3[] = "125.512.100.1";
    char ip4[] = "125.512.100.abc";
printf("string length %d\n",strlen(ip4));
for(i=0;i<strlen(ip4);i++)
{
	if(isalpha(ip4[i])){
	printf("Got a char at %d , not an ip address\n",i);
		break;	
 } }
  is_valid_ip(ip1)? printf("Valid\n"): printf("Not valid\n");
    is_valid_ip(ip2)? printf("Valid\n"): printf("Not valid\n");
    is_valid_ip(ip3)? printf("Valid\n"): printf("Not valid\n");
    is_valid_ip(ip4)? printf("Valid\n"): printf("Not valid\n");
    return 0;
}
