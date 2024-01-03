#include "address.h"
#include <arpa/inet.h>
Address::Address() {
    memset(&m_sockaddr, 0, sizeof(m_sockaddr));
}

Address::Address( const char* address, uint32_t port) {
        memset(&m_sockaddr, 0, sizeof(sockaddr_in));
        m_sockaddr.sin_family = AF_INET;
        m_sockaddr.sin_addr.s_addr = inet_addr(address);
        m_sockaddr.sin_port = htons(port);
}

sockaddr* Address::getAddress() {
    return (sockaddr*)&m_sockaddr;
}
