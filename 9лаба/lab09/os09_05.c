#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

int getCountLines(char *filename);

void main(int argc, char *argv[])
{
  printf("LINES: %d\n", getCountLines("./OS09_05.txt"));
}


int getCountLines(char *filename)
{
    FILE *fp = fopen(filename,"r");
    int ch=0;
    int lines=1;

    if (fp == NULL) 
        return 0;

    while(!feof(fp))
    {
        ch = fgetc(fp);
        if(ch == '\n')
        {
          lines++;
        }
    }
    fclose(fp);
    return lines;
}