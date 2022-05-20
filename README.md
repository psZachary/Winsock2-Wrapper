### Usage Example
```c++
#include <iostream>
#include "udpsock.hpp"
#include <windows.h>  

int main() {
    if (!udp::sock::startup_s()) 
        return -1;
    
    
    if (!udp::sock::address_s(PORT, SOCKET_ADDRESS)) 
        return -1;
    
    
    if (!udp::sock::connect_s()) 
        return -1;
    
    
    if (!udp::sock::send_s("hello server!")) 
        return -1;
    
    const char* data = udp::sock::recv_s();
    if (!data) {
        std::cout << "server data: " << data << std::endl; 
    }
}
```
