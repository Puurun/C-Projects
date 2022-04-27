#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Note.h"


int MainWindow(void){
	int c, t=0;
	char pre_message[200] = {0};
	char warning[200];
	int running=1;
	char titles[999][100] = {0};
	char* buffer = (char*)malloc(sizeof(char) * 100);
	warning[0] = 0;
	FILE* titles_read;
	
	// read from ALL_NOTE_TITLES
	titles_read = fopen("ALL_NOTE_TITLES", "r");
	if(!titles_read){
		strcpy(pre_message, "No save file detected\n");
		titles_read = fopen("ALL_NOTE_TITLES", "w");
	}
	else{
		while(fgets(titles[t], sizeof(titles[t]), titles_read) != NULL)
		{
			titles[t][strlen(titles[t])-1] = 0;
			t++;
		}
	}
	fclose(titles_read);
	
	while(running){
		clrscr();
		printf("%s", pre_message);
		printf("%s", warning);
		warning[0] = 0;
		
		pre_message[0] = 0;
		warning[0] = 0;
		
		puts("################");
		puts("Take - a - Note!");
		puts("1. Create Note");
		puts("2. Look at Note");
		puts("3. Delete Note");
		puts("4. Options");
		puts("5. Exit");
		
		c = getchar();
		iflush();
		switch(c){
			case '1':
				buffer = CreateNote(buffer);
				strcpy(titles[t], buffer);
				t++;
				SaveTitleFile(titles);
				break;
			case '2':
				if(t == 0){
					strcpy(pre_message, "No notes available yet!\n");
					break;
				}
				LookAtNote(titles);
				break;
			case '3':
				if(t == 0){
					strcpy(pre_message, "No notes available yet!\n");
					break;
				}
				strcpy(pre_message, DeleteNote(titles));
				t--;
				SaveTitleFile(titles);
				break;
			case '4':
				strcpy(pre_message, "No options currently");
				break;
			// Exit
			case '5':
				running=0;
				
			// Error
			default:
				strcpy(warning, "Invalid Input!\n");
		}
		
	}
}

char* CreateNote(char* temp){
	char directory[200] = "notes/";
	char content[9999];
	char c;
	int cur=1;
	
	content[0] = '\n';	
	clrscr();
	puts("Enter Title of Note:");
	fgets(temp, 100, stdin);
	temp[strlen(temp)-1] = 0;
	strcat(directory, temp);
	strcat(directory, ".note");
	FILE* note = fopen(directory, "w");
	fputs(temp, note);
	
	puts("Enter Contents:");
	while(True){
		c = getchar();
		content[cur] = c;
		
		if(c == '\\'){
			content[cur] = 0;
			fputs(content, note);
			break;
		}
		cur++;
	}
	iflush();
	fclose(note);
	
	return temp;
}


int LookAtNote(char titles[][100]){
	int num;
	int c;
	char* buffer = (char*)malloc(sizeof(char) * 9999);
	char directory[200] = "notes/";
	FILE* note;
	
	clrscr();
	
	puts("Select a Note to View: ");
	for(num=0; titles[num][0] != 0; num++){
		printf("%d. %s\n", num+1, titles[num]);
	}
	c = getchar();
	c = c - '0';

	iflush();
	clrscr();
	strcat(directory, titles[c-1]);
	strcat(directory, ".note");
	note = fopen(directory, "r");
	//print title
	fgets(buffer, 9998, note);
	printf("%s", buffer);
	puts("");
	
	//print content
	while(fgets(buffer, 9998, note) != NULL){
		printf("%s", buffer);
	}
	
	puts("\n");
	puts("press enter to continue");
	iflush();
	free(buffer);
}


char* DeleteNote(char titles[][100]){
	char directory[200] = "notes/";
	int num, c;
	clrscr();
	
	puts("Select a Note to Delete: ");
	for(num=0; titles[num][0] != 0; num++){
		printf("%d. %s\n", num+1, titles[num]);
	}
	c = getchar();
	c = c - '0';

	iflush();
	clrscr();
	strcat(directory, titles[c-1]);
	strcat(directory, ".note");
	if(remove(directory) == 0){
		for(; titles[c-1][0] != 0; c++){
			strcpy(titles[c-1], titles[c]);
		}
		return "File Deleted!\n";
	}
	else{
		return "File not Deleted?\n";
	}
}

// flush input
void iflush(void){
	char c;
	while(c != '\n'){
		c = getchar();
	}
}

// save ALL_NOTE_TITLES
void SaveTitleFile(char titles[][100]){
	int i;
	FILE* all_note_titles = fopen("ALL_NOTE_TITLES", "w");
	for(i=0; titles[i][0] != 0; i++){
		fputs(titles[i], all_note_titles);
		fputs("\n", all_note_titles);
	}
	fclose(all_note_titles);
}

