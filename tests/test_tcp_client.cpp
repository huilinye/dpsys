#include "dpsys/socket/socket.h"
#include "dpsys/socket/address.h"
#include <iostream>



int main(int argc, char** argv) {
    Address::AddressPtr serv_addr = std::make_shared<Address>("127.0.0.1", 8888);
    Socket::SocketPtr sock = std::make_shared<Socket>();

    sock->connect(serv_addr);
    while(true) {

        char buff[1024];
        memset(buff, 0, sizeof(buff));
        std::cin>>buff;
        ssize_t write_bytes = sock->write(sock, buff, sizeof(buff));
        
    }
    return 0;
}
