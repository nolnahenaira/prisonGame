/* Assignment 5: CSCI 3171: Summer 2017
 *
 * Program for client to connect to the Prison Game server
 *
 * Initial connection setup was referenced from suggested resource
 * codeproject.com
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(void) {
  int listenfd = 0,connfd = 0;
  struct sockaddr_in serv_addr;
  char sendBuff[1025];
  char recvBuff[1025];
  int numrv;

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("socket retrieve success\n");
  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(sendBuff, '0', sizeof(sendBuff));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(5000);

  bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));

  if(listen(listenfd, 10) == -1) {
      printf("Failed to listen\n");
      return -1;
  }

  while(1) {
    connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request
    strcpy(sendBuff, "I am a guilty cat");
    printf("derp\n");
    write(connfd, sendBuff, strlen(sendBuff));
    int n;
    while((n = read(listenfd, recvBuff, sizeof(recvBuff)-1)) > 0) {
      recvBuff[n] = 0; //terminate message line at the end of the string
      if(fputs(recvBuff, stdout) == EOF) printf("\n Error : Fputs error");
      //write() to send buffer in order to transmit new message

     /* if (strcmp (recvBuff, "I am a guilty cat") == 0) {
        strcpy(sendBuff, "Prison sentence is nine consecutive life terms");
        write(sockfd, sendBuff, sizeof(sendBuff)-1);
      }
      printf("\n");
      */
    }
    close(connfd);
    sleep(1);
  }
  return 0;
}
