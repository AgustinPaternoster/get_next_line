#include "get_next_line_bonus.h"
#include <stdio.h>


int main(void)
{
    char *lista = "XX";
    int i = 1;
 
 //tester parte obligatoria////////////////////////////////
 /* 
    int fd = open("./test2.txt",O_RDONLY);
     while (lista != NULL)
    {
        lista = get_next_line(fd);
        printf("-fd:%d line:%d:\n%s",fd,i,lista);
        free(lista);
        i++;
    }
*/

// tester bonus //////////////////////////////////
/*
    int fd = open("./test2.txt",O_RDONLY);
    int fd2 = open("./test.txt",O_RDONLY);
    while (lista != NULL)
    {
        lista = get_next_line(fd);
        printf("-fd:%d line:%d:\n%s",fd,i,lista);
        free(lista);
        lista = get_next_line(fd2);
        printf("fd:%d line:%d:\n%s",fd2,i,lista);
        free(lista);
        i++;
    }
*/
    return (0);
}