#pragma once
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996) 
#pragma warning(disable:6386) 
#pragma warning(disable:4267) 

typedef UINT SOCK_PORT;
typedef LPCSTR SOCK_IP_ADDR;

namespace udp {
    namespace sock {
        static SOCKET u_sock_s{};
        static sockaddr_in sock_addr_s{};

        static bool startup_s() {
            WSAData version;
            WORD mkword = MAKEWORD(2, 2);
            int startup_success = WSAStartup(mkword, &version);
            if (startup_success != 0)
                return 0;

            u_sock_s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            if (u_sock_s == INVALID_SOCKET)
                return 0;

            return 1;
        }

        static bool address_s(SOCK_PORT port, SOCK_IP_ADDR address) {
            auto sock_addr = sockaddr_in();

            sock_addr_s.sin_family = AF_INET;
            sock_addr_s.sin_addr.s_addr = inet_addr(address);
            sock_addr_s.sin_port = htons(port);

            return 1;
        }

        static bool connect_s() {
            int conn = connect(u_sock_s, (SOCKADDR*)&sock_addr_s, sizeof(sock_addr_s));

            if (conn == SOCKET_ERROR) {
                closesocket(u_sock_s);
                WSACleanup();
                return 0;
            }

            return 1;
        }

        static bool send_s(const char* data) {
            if (sendto(u_sock_s, data, strlen(data), 0, (struct sockaddr*)&sock_addr_s, sizeof(struct sockaddr_in)) == SOCKET_ERROR)
                return 0;

            return 1;
        }

        static const char* recv_s() {
            int buffer_size = 1028;
            char* buffer = new char[buffer_size];
            int message_size = recv(u_sock_s, buffer, buffer_size, 0);

            if (message_size == SOCKET_ERROR)
                return 0;

            buffer[message_size] = '\0';

            return buffer;
        }

        static void cleanup_s() {
            closesocket(u_sock_s);
            WSACleanup();
        }
    }
}
