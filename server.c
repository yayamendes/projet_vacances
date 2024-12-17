#include "global.h"

int main () {

    int serv_fd = socket (AF_INET, SOCK_STREAM, 0); perror ("socket");
    if (serv_fd == -1) return EXIT_FAILURE;

    struct sockaddr_in serv = {
        .sin_family = AF_INET,
        .sin_port = htons (SERV_PORT),
        .sin_addr.s_addr = INADDR_ANY
    };

    int error = bind (serv_fd, (struct sockaddr *) &serv, sizeof serv); perror ("bind");
    if (error == -1) return EXIT_FAILURE;

    error = listen (serv_fd, BUFSIZ); perror ("listen");
    if (error == -1) return EXIT_FAILURE;

    struct sockaddr_in client;
    socklen_t len;

    int client_fd = accept (serv_fd, (struct sockaddr * ) &client, &len); perror ("accept");
    if (client_fd == -1) return EXIT_FAILURE;
    
    error = send (client_fd, "moshi", 6, 0); perror ("send");
    if (error == -1) return EXIT_FAILURE;

    char buf [255]; memset (buf, 255, 0); 

    recv (client_fd, buf, 255, 0) ; perror ("recv");
    printf ("%s\n",buf);

    close (client_fd);
    close (serv_fd);

    return 0;
}