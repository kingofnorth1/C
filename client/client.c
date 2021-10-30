#include "../socket文件图片传输/tcpSocket/tcpSocket.h"
#include "../socket文件图片传输/tcpSocket/fileOperation.h"
int main() {
	init_Socket();

	SOCKET fd = create_clientSocket("127.0.0.1");
	printf("connet server successed..\n");

	recvFile(fd, "我的挚爱.png");



	//char recvBuf[1024] = "";
	//int ret = recv(fd, recvBuf, 1024, 0);
	//if (ret == 0) {
	//	printf("服务器正常下线...\n");
	//}
	//else if (ret < 0) {
	//	err("recv");
	//}
	//puts(recvBuf);

	//char sendBuf[1024] = "你今天出门没洗脸吧";
	//send(fd, sendBuf, strlen(sendBuf),0);

	closesocket(fd);
	close_Socket();
	getchar();
	return 0;
}