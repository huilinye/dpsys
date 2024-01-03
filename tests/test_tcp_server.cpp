#include "dpsys/socket/socket.h"
#include "dpsys/socket/address.h"
#include <iostream>

int main(int argc, char** argv) {
    Address::AddressPtr serv_addr = std::make_shared<Address>("127.0.0.1", 8888);
    Socket::SocketPtr sock = std::make_shared<Socket>();

    sock->bind(serv_addr);
    sock->listen();

    Address::AddressPtr clnt_addr = std::make_shared<Address>();
    Socket::SocketPtr Clnt_sock = sock->accept(clnt_addr);

    while(true) {
        char buff[1024];
        memset(buff, 0, sizeof(buff));
        ssize_t bytes_read = sock->read(Clnt_sock, buff, sizeof(buff));
        //ssize_t bytes_read = ::read(Clnt_sock->getSock(), buff, sizeof(buff));
        if(bytes_read > 0) std::cout<<"The message from client process is: "<<buff<<std::endl;
        else ::close(Clnt_sock->getSock());

    }
    return 0;
}
