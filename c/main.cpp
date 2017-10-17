#include <stdio.h>  
#include <winsock2.h>  
#include <Windows.h>  

#pragma comment(lib,"ws2_32.lib")  
#define  PORT 6000  
int main(int argc, char* argv[])  
{  
	//��ʼ�����绷��  
	WSADATA wsa;  
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)  
	{  
		printf("WSAStartup failed\n");  
		return -1;  
	}  
	//����һ��UDP��socket  
	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);  
	if (sockClient == INVALID_SOCKET)  
	{  
		printf("create socket failed\n");  
		return -1;  
	}  
	// ����һ�������ַ��Ϣ�Ľṹ�壬����������ĵ�ַ��Ϣ  
	sockaddr_in addr = { 0 };  
	addr.sin_family = AF_INET;  
	addr.sin_port = htons(PORT);  
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");  

	while(1){
		char buf[] = "client test!";  
		//��������  
		int dwSent = sendto(sockClient, buf, strlen(buf), 0, (SOCKADDR *)&addr, sizeof(SOCKADDR));  
		if (dwSent == 0)  
		{  
			printf("send %s failed\n", buf);  
			return -1;  
		}  
		printf("send msg:%s\n", buf);  

		char recvBuf[512];  
		memset(recvBuf, 0, 512);  

		sockaddr_in addrSever = { 0 };  
		int nServerAddrLen=sizeof(sockaddr_in);  
		// ��������  
		int dwRecv = recvfrom(sockClient, recvBuf, 512, 0, (SOCKADDR *)&addrSever,&nServerAddrLen);  
		printf("Recv msg from server : %s\n", recvBuf);  
	}

	//�ر�SOCKET����  
	closesocket(sockClient);  
	//�������绷��  
	WSACleanup();  
	system("pause");  
	return 0;  
}  