#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>   
#include <unistd.h>  
#include <iostream>
#include <fstream>
#include <errno.h>

using namespace std;

int send_image(int socket) {

    FILE *picture;
    int size, read_size, stat, packet_index;
    char send_buffer[10240], read_buffer[256];
    packet_index = 1;

    picture = fopen("vkohli.jpg", "rb");
    printf("Getting Picture Size\n");   

    if(picture == NULL) {
        printf("Error Opening Image File");
    } 

    fseek(picture, 0, SEEK_END);
    size = ftell(picture);
    fseek(picture, 0, SEEK_SET);
    printf("Total Picture size: %i\n",size);

    printf("Sending Picture Size\n");
    send(socket, (void *)&size, sizeof(int), 0);

    while(!feof(picture)) {
        read_size = fread(send_buffer, 1, sizeof(send_buffer)-1, picture);


        do {
            stat = write(socket, send_buffer, read_size);  
        } while (stat < 0);

        printf("Packet Number: %i\n",packet_index);
        printf("Packet Size Sent: %i\n",read_size);     
        printf(" \n");
        printf(" \n");


        packet_index++;
        
        bzero(send_buffer, sizeof(send_buffer));
    }
}

int main(int argc , char *argv[]) {

    int socket_desc , new_socket , c, read_size,buffer = 0;
    struct sockaddr_in server , client;
    char *readin;
    int sockenable = 1;
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1 || setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &sockenable, sizeof(int)) < 0) {
        printf("Could not create socket");
    }

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8889 );

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0) {
        puts("bind failed");
        return 1;
    }

    puts("bind done");

    //Listen
    listen(socket_desc , 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    if((new_socket = accept(socket_desc, (struct sockaddr *)&client,(socklen_t*)&c)))   {
        puts("Connection accepted");
    }

    fflush(stdout);

    if (new_socket<0) {
        perror("Accept Failed");
        return 1;
    }
    clock_t start = clock();
    send_image(new_socket);
    clock_t end = clock();
    cout<< "\nTime taken to read and transfer file " << static_cast<double>((end-start))/CLOCKS_PER_SEC << " seconds.\n";
    close(socket_desc);
    fflush(stdout);
    return 0;
}