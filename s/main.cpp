#include <stdio.h>  
#include <winsock2.h>  
#include <Windows.h>  

#pragma comment(lib,"ws2_32.lib")  
#define  PORT 6000  

int main(int argc, char* argv[])  
{  
	//初始化网络环境  
	WSADATA wsa;  
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)  
	{  
		printf("WSAStartup failed\n");  
		return -1;  
	}  

	//建立一个UDP的socket  
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);  
	if (sock == SOCKET_ERROR)  
	{  
		printf("create socket failed\n");  
		return -1;  
	}  

	//绑定地址信息  
	sockaddr_in serverAddr;  
	serverAddr.sin_family = AF_INET;  
	serverAddr.sin_port = htons(PORT);  
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);  

	bind(sock, (sockaddr*)&serverAddr, sizeof(sockaddr));  

	char buf[512];  
	while (TRUE)  
	{  
		memset(buf, 0, 512);  
		// 网络节点的信息，用来保存客户端的网络信息  
		sockaddr_in clientAddr;  
		memset(&clientAddr, 0, sizeof(sockaddr_in));  

		int clientAddrLen = sizeof(sockaddr);  
		//接收客户端发来的数据  
		int ret = recvfrom(sock, buf, 512, 0,(sockaddr*) &clientAddr,&clientAddrLen );  

		printf("Recv msg:%s from IP:[%s] Port:[%d]\n", buf,inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port));  
		// 发一个数据包返回给客户  
		sendto(sock, "Hello World!", strlen("Hello World!"), 0, (sockaddr*)&clientAddr, clientAddrLen);  
		printf("Send msg back to IP:[%s] Port:[%d]\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));  
	}  
	return 0;  
}  