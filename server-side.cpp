//Server side socket program
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080

int main(int argc,char const *argv[])
{
    int server_fd,new_socket;
    long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello World!";

    //socket file descriptor
    if((server_fd = socket(AF_INET, SOCK_STREAM,0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET; //Address family used
    address.sin_addr.s_addr = INADDR_ANY; //The address for the socket
    address.sin_port = htons( PORT ); //htons converts a short integer to a network representation

    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    //Assigning transport address for the socket
    if(bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    //Listens for incoming connections
    if (listen(server_fd,10)<0)
    {
       perror("In listen");
       exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("\n++++++ Waiting for new connection +++++++\n\n");
        // Accepts established connection
        if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        char buffer[3000] = {0};
        valread = read(new_socket, buffer, 3000);
        printf("%s\n", buffer);
        write(new_socket, hello, strlen(hello));
        printf("---------------Hello message sent-----------------\n");
        close(new_socket);
    }
    return 0;    
}