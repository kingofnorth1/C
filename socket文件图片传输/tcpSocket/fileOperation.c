#include "fileOperation.h"
long g_fileSzie = 682328;	//�����ļ���С
char* g_fileBuf;	//�����ļ�����

bool readFile(const char* fileName)
{
	FILE* read = fopen(fileName, "rb");
	if (!read) {
		perror("file open failed : \n");
		return false;
	}
	//��ȡ�ļ���С
	fseek(read, 0, SEEK_END);    //���ļ�λ��ָ���ƶ������
	g_fileSzie = ftell(read);
	fseek(read, 0, SEEK_SET);	//�ƶ�����ͷ
	printf("filesize :%d\n", g_fileSzie);

	//�����ڴ�
	g_fileBuf = calloc(g_fileSzie, sizeof(char));
	if (!g_fileBuf)
		return false;

	//���ļ������ڴ�����
	fread(g_fileBuf, sizeof(char), g_fileSzie, read);

	fclose(read);
	return false;
}

bool sendFile(SOCKET s, const char* fileName)
{
	readFile(fileName);
	int ret = send(s, g_fileBuf, g_fileSzie, 0);
	if (ret == SOCKET_ERROR) {
		err("sendFile");
		return false;
	}
	printf("���ͳɹ�(%d)Byte\n", ret);

	return false;
}

bool recvFile(SOCKET s, const char* fileName)
{
	if (g_fileBuf == NULL) {
		g_fileBuf = calloc(g_fileSzie, sizeof(char));
		if (!g_fileBuf)
			return false;
	}
	int ret = recv(s, g_fileBuf, g_fileSzie, 0);
	if (ret == 0) {
		printf("��������������...\n");
	}
	else if (ret < 0) {
		err("recv");
	}

	saveFile(fileName);

	return false;
}

bool saveFile(const char* fileName)
{
	//readFile(fileName);
	FILE* write = fopen(fileName, "wb");
	if (!write) {
		perror("file open failed : \n");
		return false;
	}

	fwrite(g_fileBuf, sizeof(char), g_fileSzie, write);

	fclose(write);
	return true;
}
