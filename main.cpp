#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;

int main( int argc, char ** argv)
{
    if(argc != 2){
        cout << "uso: " << argv[0] << " www.domain.com" << endl;
        return EXIT_FAILURE;
    }
    struct addrinfo data, *nodes, *p;
    int status;
    char IP[INET6_ADDRSTRLEN];

    memset(&data, 0, sizeof data);
    data.ai_family = AF_UNSPEC;             // For IPv4 and IPv6
    data.ai_socktype = SOCK_STREAM;         // only TCP

    status = getaddrinfo( argv[1] , NULL, &data, &nodes);
    if( status != 0 ){
        cout << "Error al resolver el dominio: "<< gai_strerror(status) << endl;
        return EXIT_FAILURE;
    }

    cout << "Direcciones IP para " << argv[1] << endl;

    for(p = nodes; p != NULL; p = p->ai_next){
        void *address;
        string IPversion;

        if(p->ai_family == AF_INET){        // Si es IPv4
            struct sockaddr_in * IPv4 = (struct sockaddr_in *)p->ai_addr;
            address = &(IPv4->sin_addr);
            IPversion = "IPv4";
        }else{
            struct sockaddr_in6 * IPv6 = (struct sockaddr_in6 *)p->ai_addr;
            address = &(IPv6->sin6_addr);
            IPversion = "IPv6";
        }
        inet_ntop(p->ai_family, address, IP, sizeof IP);
        cout << IPversion <<" : "<< IP << endl;
    }

    freeaddrinfo(nodes);
    return 0;
}
