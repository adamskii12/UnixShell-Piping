/* 
 * File:   main.c
 * Author: Adam IW
 *
 * Created on February 14, 2022, 6:34 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv) {

    char ch1[100]; //used for input before pipe symbol 
    char ch2[100]; //used for input after pipe symbol 
    int i; //variable used in loops throughout the program
    char* args1[50]; //used to store strings of input before pipe symbol
    char* args2[50]; //used to store strings of input after pipe symbol
    int argNum1=0; //initialize both argument pointers to 0
    int argNum2=0; 
    int fd[2]; //used in the pipe() to distinguish between reading and writing from/to the pipe
    char spaces[2]={'\0', '\0'}; //used to check for spaces in input
    args1[0]=&ch1[0]; //set the first argument (string) to the first character in each input array
    args2[0]=&ch2[0];
    
    fprintf(stderr, "Your command >"); //asks user for their command
   
    //taking user's input BEFORE the pipe symbol, the loops will terminate once
    //the pipe symbol '|' is inputted
    for(i=0; (ch1[i] = getchar()) != '|' ; i++){
       
        if(isspace(ch1[i])){ //if character is a space, we replace that element with the null character
           ch1[i]= '\0';
        }
        
        char temp2[2]={ch1[i-1], '\0'};
        
        //if and only if there was a space, followed by a character which is not
        //the pipe symbol '|', we increase the argument pointer to take multiple arguments
        if(strcmp(spaces, temp2)==0 && i>0){
           argNum1++;
           args1[argNum1]=&ch1[i];
        }
    } 
    ch1[i]='\0'; //in case there was no ending null character 
    args1[argNum1+1]=NULL; //signify the end of the args array
    
    //collect user input AFTER the pipe symbol '|'
    for(i=0; (ch2[i] = getchar()) != '\n' ; i++){
       
        //if the first character is a space, we decrement the i variable 
        //so we take the input without the space
        if(isspace(ch2[0])){
            i--;
        }
        //once the user inputs characters (i.e. not a space), any subsequent spaces
        //will increase arg pointer #2 to separate the arguments into the string array
        else if(isspace(ch2[i])){
           ch2[i]= '\0';
           argNum2++;
           args2[argNum2]=&ch2[i+1];
        }
        
    }
    ch2[i]='\0';
    
    pipe(fd); //fd[0] and fd[1] will be the file descriptors for reading from and writing to the pipe
    int pId = fork(); //child process will return 0, parent will return 1
    
    //only parent process will run this statement 
    if(pId>0){
        dup2(fd[1], 1); //all standard output will be directed to the pipe input
        close(fd[0]); //closes reading pipe descriptor 
        close(fd[1]); //closes writing pipe descriptor 
        execvp(args1[0], args1); //executes command before pipe symbol 
        exit(1); 
    }
    else{
        dup2(fd[0], 0); //standard input will be taken from the pipe output
        close(fd[1]); //closes writing pipe descriptor 
        close(fd[0]); //closes reading pipe descriptor
        execvp(args2[0], args2); //executes command after pipe symbol
        exit(1);
    }

    return (EXIT_SUCCESS);
}

