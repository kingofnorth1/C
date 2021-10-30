#include <stdio.h>
#include <winsock.h>

int main() {
	
	char Sendbuf[100];
	char Receivebuf[100];
	int SendLen;
	int ReceiveLen;

	SOCKET socket_send;
	SOCKADDR_IN Server_add;

	WORD wVersionRequested;
	WSADATA wsaData;
	int  error;

	wVersionRequested = MAKEWORD(2, 2);
	error = WSAStartup(wVersionRequested, &wsaData);  //初始化套接字
	if (error != 0) {
		printf("加载套接字失败！");
		return 0;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		return 0;
	}

	Server_add.sin_family = AF_INET;
	Server_add.sin_addr.S_un.S_addr = inet_addr("172.24.174.120");
	Server_add.sin_port = htons(5000);

	socket_send = socket(AF_INET, SOCK_STREAM, 0);


	if (connect(socket_send, (SOCKADDR*)&Server_add, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		printf("连接失败！");
	}

	while (1) {
		printf("please enter message:");
		scanf("%s", Sendbuf);
		/*if (Sendbuf != 0) {

		}*/
		SendLen = send(socket_send, Sendbuf, 100, 0);  //发送数据
		if (SendLen < 0) {
			printf("发送失败");
		}

		ReceiveLen = recv(socket_send, Receivebuf, 100, 0);  //接受数据
		if (ReceiveLen < 0) {
			printf("接受失败\n");
			printf("程序退出\n");
			break;
		}
		else {
			printf("Server say: %s\n", Receivebuf);
		}
	}

	closesocket(socket_send);
	WSACleanup();
	return 0;
}