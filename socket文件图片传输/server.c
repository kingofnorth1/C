#include "tcpSocket/tcpSocket.h"
#include "tcpSocket/fileOperation.h"
int main11() {
	readFile("./�ҵİ���");
	saveFile("�ҵ�ֿ��.png");
	return 0;
}

int main() {
	init_Socket();

	SOCKET serfd = create_serverSocket();
	printf("server create successed ,wait client connet...\n");
	//�ȴ��ͻ�������
	SOCKET clifd=accept(serfd, NULL, NULL);
	if (clifd == INVALID_SOCKET) {
		err("accept");
	}
	printf("�Ѻõ��ʺ�һ��\n");
	//���ԺͿͻ��˽���ͨ����

	sendFile(clifd,"./�ҵİ���.png");




	/*if (SOCKET_ERROR == send(clifd, "f**k", 4, 0)) {
		err("f**k send");
	}*/

	/*char recvBuf[1024] = "";
	int ret = recv(clifd, recvBuf, 1024, 0);
	if (ret == 0) {
		printf("�ͻ�����������...\n");
	}
	else if (ret < 0) {
		err("recv");
	}
	puts(recvBuf);
	*/ 


	closesocket(clifd);
	closesocket(serfd);
	close_Socket();
	getchar();
	return 0;
}