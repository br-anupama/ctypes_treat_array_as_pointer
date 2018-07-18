#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "int_array_as_pointer.h"

#define PORT 8080


void display(struct student ex){
	printf("type: %d \n", ex.type);
	printf("length: %d \n", ex.length);
	struct place *p;
	p = (struct place*)(ex.buffer);

	printf("pos_n : %d \n", p->pos_n); 
	printf("pos_s : %d \n", p->pos_s); 

}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    struct student ex;
    struct place p;
  
	struct data{
		int type;
		int length;
	};
    struct data init_data;

  
    printf("server started listening ... \n");
    
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
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
   
    while(1){
    	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    	{
        	perror("accept");
        	exit(EXIT_FAILURE);
   	 }
    	valread = read( new_socket , (struct data *)&init_data, sizeof(struct data) );
	int bytes = init_data.length;
	printf("length: %d \n", bytes);

	printf("init_data type: %d \n", init_data.type);
	printf("init_data length: %d \n", init_data.length);
	read( new_socket, (struct place *)&p, sizeof(int)*bytes );
	
	printf("pos_n: %d \n", p.pos_n);
	printf("pos_s: %d \n", p.pos_s);

        //display(ex);
	printf("------------------------");
    }
    return 0;
}
