#include<sys/types.h> 
#include<sys/wait.h> 
#include<unistd.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 

#define TRUE 1 
#define FALSE 0 

void type_prompt();
int read_command(char* command[], int* length);

int main() {
	char* command[100];
	int status_value;
	int length;
	int exit_flag = 1;
	pid_t pid;
	int i;


	while (TRUE) {
		for (i = 0; i < 100; i++) {
			command[i] = (char *)malloc(sizeof(char) * 100);
		}

		type_prompt();
		exit_flag = read_command(command, &length);

		pid = fork();

		if (pid != 0) {  //parent 
			if (exit_flag) {
				exit(1);
			}
			else {
				waitpid(-1, &status_value, 0);
			}

		}
		else if (pid < 0) {
			printf("Failed to open a shell\n");
			exit(1);

		}
		else {    //child 
			if (!exit_flag) {
				command[length] = NULL;
				execvp(command[0], command);
				return 0;
			}
			else {
				exit(1);
			}
		}

	}


	return 0;
}



void type_prompt() {
	printf("joonoh$ ");
}

int read_command(char* command[], int* length) {
	char str[1000];
	char* tmp_command[1000];
	int i = 0;
	char* tok;
	fgets(str, sizeof(str), stdin);
	str[strlen(str) - 1] = '\0';

	if (strcmp(str, "exit") == 0) {
		return TRUE;
	}

	tok = strtok(str, " ");

	while (tok != NULL) {
		tmp_command[i++] = tok;
		tok = strtok(NULL, " ");
	}
	*length = i;

	tmp_command[i] = '\0';


	int j = 0;
	for (j = 0; j < i; j++) {
		command[j] = tmp_command[j];
	}

	return FALSE;

}