// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <assert.h> 
#include <sys/types.h>
#include <pwd.h>
#include <sys/wait.h>
#include <errno.h> 
#define PORT 80

int drop_privelege()
{
    struct passwd *pw;
    pw = getpwnam("nobody");
    assert(pw != NULL);
    if(pw == NULL)
    {
        printf("Could not find nobody user\n");
        return 0;
    }
    if (setgid(pw->pw_gid) != 0){
        printf("setgid failed with error no : %d\n", errno); 
        return 0;
    }
    if (setuid(pw->pw_uid) != 0){
        printf("setuid failed with error no : %d\n", errno); 
        return 0;
    }
    printf("Succesfully dropped privilege\n");
    return 1;
}

int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    // Socket is bound -- forking new process
    pid_t child, wpid;
    child = fork();

    if (child == 0) {
        //Drop privilege
        if (drop_privelege() == 0){
            perror("privilege drop failed");
            exit(EXIT_FAILURE);
        }
        if (listen(server_fd, 3) < 0) 
        { 
            perror("listen"); 
            exit(EXIT_FAILURE); 
        } 
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                        (socklen_t*)&addrlen))<0) 
        { 
            perror("accept"); 
            exit(EXIT_FAILURE); 
        } 
        valread = read( new_socket , buffer, 1024); 
        printf("%s\n",buffer ); 
        send(new_socket , hello , strlen(hello) , 0 ); 
        printf("Hello message sent\n"); 
        return 0; 
    } else {
        //Wait for child to finish
        int status = 0;
        while ((wpid = wait(&status)) > 0);
        printf("Child process done -- Parent Exiting\n");
    }
} 
