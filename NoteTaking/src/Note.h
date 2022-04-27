#ifndef NOTE____
#define NOTE____

#define True 1
#define False 0

#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif

int MainWindow(void);
char* CreateNote(char* temp);
int LookAtNote(char titles[][100]);
char* DeleteNote(char titles[][100]);
void SaveTitleFile(char titles[][100]);

void iflush(void);


#endif