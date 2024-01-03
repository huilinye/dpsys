#include "socket.h"


Socket::Socket() {
    m_sockfd = socket(AF_INET, SOCK_STREAM, 0); // IPv4 address
}

int Socket::getSock() const { return m_sockfd; }

void Socket::bind(Address::AddressPtr address) {
    socklen_t addrlen = sizeof(sockaddr_in);
    ::bind(m_sockfd, address->getAddress(), addrlen);
    
}

void Socket::listen() {
    ::listen(m_sockfd, SOMAXCONN);
}

typename Socket::SocketPtr Socket::accept(Address::AddressPtr address) {
    int clnt_fd = socket(AF_INET, SOCK_STREAM, 0);
    socklen_t clnt_len = sizeof(sockaddr_in);
    clnt_fd = ::accept(m_sockfd, address->getAddress(), &clnt_len);
    return std::make_shared<Socket>(clnt_fd);
}

ssize_t Socket::read(SocketPtr sock, char* buff, ssize_t size) {
    ssize_t read_bytes = ::read(sock->getSock(), buff, size);
    return read_bytes;
}

ssize_t Socket::write(SocketPtr sock, char* buff, ssize_t size) {
    ssize_t write_bytes = ::write(sock->getSock(), buff, size);
    return write_bytes;
}

void Socket::connect(Address::AddressPtr address) {
    ::connect(m_sockfd, address->getAddress(), sizeof(sockaddr_in));

}

