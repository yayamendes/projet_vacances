#include "global.h"

int main () {

    int client_fd = socket (AF_INET, SOCK_STREAM, 0); perror ("socket");
    if (client_fd == -1) return EXIT_FAILURE;

    struct sockaddr_in client = {
        .sin_family = AF_INET, 
        .sin_port = htons (CLIENT_PORT), 
        .sin_addr.s_addr = inet_addr ("127.0.0.1")
    };

    int error = bind (client_fd, (struct sockaddr *) &client, sizeof client); perror ("bind");
    if (error == -1) return EXIT_FAILURE;

    struct sockaddr_in serv = {
        .sin_family = AF_INET,
        .sin_port = htons (SERV_PORT),
        .sin_addr = INADDR_ANY
    };

    error = connect (client_fd, (struct sockaddr *) &serv, sizeof serv); perror ("connect");
    if (error == -1) return EXIT_FAILURE;

    char buf [255]; memset (buf, 0, 255);

    recv (client_fd, buf, 255, 0) ; perror ("recv");
    printf ("%s\n",buf);

    error = send (client_fd, "moshi", 6, 0); perror ("send");
    if (error == -1) return EXIT_FAILURE;

    close (client_fd);

    return 0;
}