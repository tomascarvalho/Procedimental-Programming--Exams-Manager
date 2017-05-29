#include "header.h"

/* Removes the new line char \n from the end of a string */
void removes_newLine(char *str)
{
    if (str[strlen(str)-1] == '\n')
        str[strlen(str)-1] = '\0';
}


char* append_strings(char* str1, char* str2)
{
    char* new_str ;
    if((new_str = malloc(strlen(str1)+strlen(str2)+1)) != NULL)
    {
        new_str[0] = '\0';   // ensures the memory is an empty string
        strcat(new_str,str1);
        strcat(new_str,str2);
        return new_str;
    }

    printf("Impossivel alocar memoria\n");
    return NULL;

}
