The program begins with asking the user for input from the command line (“Your command > “). 
Then, the program takes user input commands which are expected to be separated by a pipe symbol ‘|’.
Once the input is taken, the program initializes the pipe and prepares for reading from and writing to the pipe. 
The program also forks into a parent process and child process. 
The parent process then executes the command before the pipe symbol ('|'), with its stdout redirected to the pipe input (writing to the pipe). 
The child process then redirects standard input to be taken from the pipe output, which then executes the command after the pipe symbol using this input. 
The program then prints the output of this command on the screen. 

Ex. if the user inputs 'ls | wc -w' in the command line, the parent process executes 'ls' and has the output of this command written to the pipe. 
Then the child process reads from the pipe and uses this as input for the command after the pipe symbol 'wc -w'. So if there were 3 files in the folder the 
user was in, this would output 3, since 'ls' returns the names of the files, and 'wc -w' will count the number of words, which will be 3. 
