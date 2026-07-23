#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>     // fork, execvp, read, write
#include <sys/wait.h>   // waitpid

#define TOK_DELIM " \t\r\n"
#define RED "\033[0;31m"
#define RESET "\e[0m"
#define TK_BUFF_SIZE 1024

char *read_line();
char **split_line(char *);
int dash_exit(char **);
int dash_execute(char **);

int dash_execute(char * * args) {
  pid_t cpid;
  int status;

  if (strcmp(args[0], "exit") == 0){
  	return dash_exit(args);
  }

  cpid = fork(); //fork allows us to create a new process by duplicating the current process, referring it to as the child process
  //when we invoke the fork system call, it returns the process ID of the child in the parent process

  if (cpid == 0) {
    if (execvp(args[0], args) < 0) //if fork was successful, execvp executes the command
    //replaces the current process with a new process image which in this case is the command that needs to be executed
      perror("dash");
    exit(EXIT_FAILURE);

  } else if (cpid < 0) 
    printf(RED "Error forking"
      RESET "\n");
  else {
    waitpid(cpid, & status, WUNTRACED); //making sure the child process finishes successfully
  }

  return 1;
}

int dash_exit(char **args)
{
	return 0;
}

char * * split_line(char * line) {
  int buffsize = TK_BUFF_SIZE, position = 0;
  char * * tokens = malloc(buffsize * sizeof(char * ));
  char * token;

  if (!tokens) {
    fprintf(stderr, "%sdash: Allocation error%s\n", RED, RESET);
    exit(EXIT_FAILURE);
  }
  token = strtok(line, TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= buffsize) {
      buffsize += TK_BUFF_SIZE;
      tokens = realloc(tokens, buffsize * sizeof(char * ));

      if (!tokens) {
        fprintf(stderr, "%sdash: Allocation error%s\n", RED, RESET);
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, TOK_DELIM);
  }

  tokens[position] = NULL;

  return tokens;
}

char * read_line() {
  int buffsize = 1024;
  int position = 0;
  char * buffer = malloc(sizeof(char) * buffsize); //a char pointer buffer variable is allocated memory through malloc the size of buffsize
  //dynamic alloacation instead of static as you cannot determine the length of command entered by the user
  int c;

  if (!buffer) {
    fprintf(stderr, "%sdash: Allocation error%s\n", RED, RESET);
    exit(EXIT_FAILURE);
  }

  while (1) { //infinite while loop
    c = getchar(); //stores the character entered by the user
    if (c == EOF || c == '\n') {
      //printf("\n");
      buffer[position] = '\0';
      return buffer; //null terminator returned
    } else {
      buffer[position] = c; //character stored in the buffer char pointer
    }
    position++;

    if (position >= buffsize) { //if the current size is equal to or greater than the size we initialized it with, we need to allocate more memory so as to continue reading user input
      buffsize += 1024; //doubling the value
      buffer = realloc(buffer, buffsize); //passing to realloc(), which returns a variable with the new size passed as argument and all the data copied to the new variable

      if (!buffer) { //checks are for making sure memory was allocated to buffer successfully; otherwise malloc and realloc return null, and our function returns with an error
        fprintf(stderr, "dash: Allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

void loop() {
   char * line; //char pointer
   char * * args; //2d char pointer
   int status = 1;

   do {
      printf("> ");
      line = read_line(); //will hold the command(string) entered by the user
      args = split_line(line);
      status = dash_execute(args); //stores the return value of functions invoked during command execution
      //will determine the termination of the loop, i.e if the user enters the exit command
      free(line);
      free(args);
      //final two lines free the memory used by the pointer variables
   } while (status);
}

int main() {
  loop();
  return 0;
}

