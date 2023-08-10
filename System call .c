#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

    int main(){
            int childStatus;
            
            //Fork a child process
            pid_t pid=fork();
            
            if(pid<0){
                // Forking Failed
                perror("fork failed");
                exit(EXIT_FAILURE);
            }else if(pid==0){
                 //Child Process
                // Print the child process Id and its parent's Id
                printf("child process ID: %d \n ",getpid());
                printf("parent process ID : %d \n", getpid());
                // Execute system calls to analyze process creation and termination
                execl("\bin\ls","is","-l",NULL);
                // If execl() RETURNS,it means the system call failed 
                perror("execl failed");
                exit(EXIT_FAILURE);
            }else{
                // Parent process
                // wait for the child process to terminate 
                wait(&childStatus);
                    if(WIFEXITED(childStatus)){
                int exitStatus = WEXITSTATUS(childStatus);
                printf("chid Process terminated with exit status : %d \n",exitStatus);
                }else if(WIFSIGNALED(childStatus)){
                    // Child Process terminated due to a signal
                    int termSignal = WTERMSIG(childStatus);
                    printf("child process terminated due to signal : %d \n",termSignal);
                } 
                
         }
            return 0;  
            }
