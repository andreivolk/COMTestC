#include <stdio.h>
#include <stdlib.h>
#include <Serial.h>
#include <string.h>
#include <main.h>
#include <ctype.h>
#include <stdbool.h>

bool running = true;

char *INSTRUCTIONS[] = {"Enter commands prefixed by a switch eg. /s hello", "/l - gets a list of available COM ports", "/c <x> - connects to COM port x", "/x - closes the currently opened COM port", "/s <message> - sends a message over the open COM port", "/r <message> re-sends a message at 5 second intervals", "/h - list of commands", "/q - exits the program"};
int arrayLength = sizeof(INSTRUCTIONS) / sizeof(INSTRUCTIONS[0]); 
 
int main()
{
	ListCommands();
	while(running){
	char line[256];
	if (fgets(line, sizeof(line), stdin)) {    
		line[strcspn(line, "\n")] = 0;
		char command[3];
		strncpy(command,line,2);
		command[2] = 0;
		if (strcmp(command, "/l") == 0) 
		{
			GetPorts();
		}
		else if (strcmp(command, "/c") == 0) 
		{
			OpenPort(atoi(GetCommand(line)));
		}
		else if (strcmp(command, "/x") == 0) 
		{
			ClosePort();
		}
		else if (strcmp(command, "/s") == 0) 
		{
			Send((GetCommand(line)));
		}
		else if (strcmp(command, "/r") == 0) 
		{
			Repeat((GetCommand(line)));
		}
		else if (strcmp(command, "/h") == 0) 
		{
			ListCommands();
		}
		else if (strcmp(command, "/q") == 0) 
		{
			running = false;
		}
		else
		{
		printf("Invalid Command\n");  
		}        
	}
}
  return 0;
}
char * GetCommand(char line[])
{		
		if(strlen(line)>2)
		{
			char *comParameter = line + 2;
			char *trimmedCommand = trimwhitespace(comParameter);
			if(strcmp(trimmedCommand, "error") != 0)
			{
				return trimmedCommand;
			}
			else
			{
				printf("Invalid Command - no parameters\n");
			}
		}
}
char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
	return "error";

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}
int ListCommands()
{
	for(int i = 0;i<arrayLength;i++)
	{
		printf("%s \n",INSTRUCTIONS[i]);
	}
	return 0;
}
