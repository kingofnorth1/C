#include "../socket�ļ�ͼƬ����/tcpSocket/tcpSocket.h"
#include "../socket�ļ�ͼƬ����/tcpSocket/fileOperation.h"
int main() {
	init_Socket();

	SOCKET fd = create_clientSocket("127.0.0.1");
	printf("connet server successed..\n");

	recvFile(fd, "�ҵ�ֿ��.png");



	//char recvBuf[1024] = "";
	//int ret = recv(fd, recvBuf, 1024, 0);
	//if (ret == 0) {
	//	printf("��������������...\n");
	//}
	//else if (ret < 0) {
	//	err("recv");
	//}
	//puts(recvBuf);

	//char sendBuf[1024] = "��������ûϴ����";
	//send(fd, sendBuf, strlen(sendBuf),0);

	closesocket(fd);
	close_Socket();
	getchar();
	return 0;
}