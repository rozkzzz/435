/*
   A simple TCP client and server program by chatgpt :) 
   Tharit Kaeothong 6309681804 And NAPHATSATWO THREE FOUR FIVE SIX SEVEN...
  */
  #include <stdlib.h>
  #include <stdio.h>

 #include <string.h>
 #include <errno.h>
 #include <unistd.h>
 #include <stdint.h>
 #include <inttypes.h>
 #include <fcntl.h>

 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <arpa/inet.h>

 #define SERV_IP     "127.0.0.1"
#define SERV_PORT   18800
 #define SERV_PORT2 18801

 #define MAXLINE 100

 int socket_fd;
 int socket_fd2;
 int new_socketfd;
 struct sockaddr_in serv_addr, serv_addr2;

 int main(int argc, char *argv[]){
     int m, n;
     char line[MAXLINE];

     socket_fd = socket(AF_INET, SOCK_STREAM, 0);

     memset(&serv_addr, 0, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(SERV_PORT);
     bind(socket_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
     listen(socket_fd, 5);

     if((new_socketfd = accept(socket_fd, NULL, NULL)) < 0){
         printf("Accept: Error occured\n");
         exit(1);
     }

     //while ((n = read(new_socketfd, line, MAXLINE)) != 0){
                 read(new_socketfd, line, MAXLINE);
                 printf("line = %s with n = %d characters\n", line, n);
                 printf("mid recv from client \n");
                 fflush(stdout);
     //    }
     printf("line %s \n",line);

     socket_fd2 = socket(AF_INET, SOCK_STREAM, 0);
     memset(&serv_addr2, 0, sizeof(serv_addr2));
     serv_addr2.sin_family = AF_INET;
     serv_addr2.sin_addr.s_addr = inet_addr(SERV_IP);
    serv_addr2.sin_port = htons(SERV_PORT2);

     if (connect(socket_fd2, (struct sockaddr *) &serv_addr2, sizeof(serv_addr))<0) {
             perror("Problem in connecting to the server");
             exit(3);
     }
             printf("midle process sending...");
             n = write(socket_fd2, line, MAXLINE);
             printf("send %s with n = %d characters\n", line, n);
             m = read(socket_fd2, line, MAXLINE);
             printf("receive %s from server 2 with m = %d characters\n", line, m);
             fputs(line, stdout);

             write(new_socketfd, line, MAXLINE);
             printf("midle process got %s from server.",line);
     close(socket_fd);
     close(socket_fd2);
     close(new_socketfd);
    }
 

