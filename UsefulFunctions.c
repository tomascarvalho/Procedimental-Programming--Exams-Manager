#include "header.h"

/* Removes the new line char \n from the end of a string */
void removes_newLine(char *str)
{
    if (str[strlen(str)-1] == '\n')
        str[strlen(str)-1] = '\0';
}
