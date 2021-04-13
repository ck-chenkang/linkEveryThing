#include "setexAPI.h"

int initialize(const char *deviceip)
{
    const char *ip = deviceip;

    struct sockaddr_in serverSockAddr;

    // int port = 50000;
    //定义sockfd
    sockHandle = socket(AF_INET, SOCK_STREAM, 0);
    if (sockHandle < 0)
    {
        return -1;
    }

    ///定义sockaddr_in
    memset(&serverSockAddr, 0, sizeof(serverSockAddr));
    serverSockAddr.sin_family = AF_INET;
    serverSockAddr.sin_port = htons(SETEXPORT);     //服务器端口
    serverSockAddr.sin_addr.s_addr = inet_addr(ip); //服务器ip，inet_addr用于IPv4的IP转换（十进制转换为二进制）

    //连接服务器，成功返回0，错误返回-1
    int rc = connect(sockHandle, (struct sockaddr *)&serverSockAddr, sizeof(serverSockAddr));

    if (rc < 0)
    {
        
        if (sockHandle >= 0)
        {
            close(sockHandle);
        }
        return -1;
    }
    

    return 0;
}

int getPictureLayers(int *ch)
{
    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x14;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x0b;
    buffS[16] = 0x37;
    buffS[17] = 0x04;
    buffS[18] = 0x04;
    buffS[19] = 0x00;
    buffS[20] = 0x8d;
    buffS[21] = 0x00;
    buffS[22] = 0x0a;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);

    usleep(10);
    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);

    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        for (int i = 20; i < 30; i++)
        {
            ch[i - 20] = buffR[i];
        }
        return 0;
    }
}

int setPictureLayers(int *ch)
{
    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0xf4;
    buffS[3] = 0x01;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x0c;
    buffS[16] = 0x37;
    buffS[17] = 0x04;
    buffS[18] = 0xe4;
    buffS[19] = 0x01;
    buffS[20] = 0x8d;
    buffS[21] = 0x00;
    buffS[22] = 0x0a;
    buffS[23] = 0x00;

    for (int i = 24; i < 34; i++)
    {
        buffS[i] = ch[i - 24];
    }

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);
    // usleep(); linux 1 means 1 second
    // cout << "bytesRecv: " << bytesRecv << endl;
    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    // cout << "received: " << bytesRecv;
    if (bytesRecv < 0)
    {
        return -1;
    }

    return 0;
}

int getInfoWord(int index, int* value)
{
    if (index < 1 || index > 200)
        return -1;

    int bytesRecv;

    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x12;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x01;
    buffS[16] = 0x01;
    buffS[17] = 0x04;
    buffS[18] = 0x02;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = 0x00;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        int value1 = (unsigned char)buffR[20];
        int value2 = (unsigned char)buffR[21];
        *value = value2 * 256 + value1;
        return 0;
    }
}

int setInfoWord(int index, int value)
{
    if (index < 1 || index > 200)
        return -1;
    if (value < 0 || value > 32767)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int value1 = value % 256;
    int value2 = value / 256;
    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x14;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x02;
    buffS[16] = 0x01;
    buffS[17] = 0x04;
    buffS[18] = 0x04;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = value1;
    buffS[23] = value2;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int getInfoDoubleWord(int index, unsigned *value)
{
    if (index < 1 || index > 500)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x12;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x01;
    buffS[16] = 0x39;
    buffS[17] = 0x04;
    buffS[18] = 0x02;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = 0x00;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        int value1 = (unsigned char)buffR[20];
        int value2 = (unsigned char)buffR[21];
        int value3 = (unsigned char)buffR[22];
        int value4 = (unsigned char)buffR[23];
        *value = value1 + value2 * 256 + value3 * 256 * 256 + value4 * 256 * 256 * 256;
        return 0;
    }
}

int setInfoDoubleWord(int index, unsigned value)
{
    if (index < 1 || index > 500)
        return -1;
    if (value < 0 || value > 256 * 256 * 256 * 256 - 1)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int value1 = value % 256;
    int value2 = value / 256 % 256;
    int value3 = value / 256 / 256 % 256;
    int value4 = value / 256 / 256 / 256;

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x16;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x02;
    buffS[16] = 0x39;
    buffS[17] = 0x04;
    buffS[18] = 0x06;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = value1;
    buffS[23] = value2;
    buffS[23] = value3;
    buffS[24] = value4;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int getInfoBit(int index, int *value)
{
    if (index < 1 || index > 500)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x12;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x01;
    buffS[16] = 0x02;
    buffS[17] = 0x04;
    buffS[18] = 0x02;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = 0x00;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        int data = buffR[20];
        *value = data;
        return 0;
    }
}

int setInfoBit(int index, int value)
{
    if (index < 1 || index > 500)
        return -1;

    int data;
    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    if (value)
        data = 1;
    else
        data = 0;

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x13;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x02;
    buffS[16] = 0x02;
    buffS[17] = 0x04;
    buffS[18] = 0x03;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = data;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int getFunctionInitMarker(int index, int *value)
{
    if (index < 1 || index > 1000)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x12;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x01;
    buffS[16] = 0xf4;
    buffS[17] = 0x03;
    buffS[18] = 0x02;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = 0x00;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        int data = buffR[20];
        *value = data;
        return 0;
    }
}

int setFunctionInitMarker(int index, int value)
{
    if (index < 1 || index > 1000)
        return -1;

    int data;
    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    if (value)
        data = 1;
    else
        data = 0;

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x13;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x02;
    buffS[16] = 0xf4;
    buffS[17] = 0x03;
    buffS[18] = 0x03;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = data;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int getFunctionActivationMarker(int index, int *value)
{
    if (index < 1 || index > 1000)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x12;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x01;
    buffS[16] = 0xf3;
    buffS[17] = 0x03;
    buffS[18] = 0x02;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = 0x00;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        int data = buffR[20];
        *value = data;
        return 0;
    }
}

int setFunctionActivationMarker(int index, int value)
{
    if (index < 1 || index > 1000)
        return -1;

    int data;
    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    if (value)
        data = 1;
    else
        data = 0;

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x13;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x02;
    buffS[16] = 0xf3;
    buffS[17] = 0x03;
    buffS[18] = 0x03;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = data;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int getFunctionQuitMarker(int index, int *value)
{
    if (index < 1 || index > 1000)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x12;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x01;
    buffS[16] = 0xf5;
    buffS[17] = 0x03;
    buffS[18] = 0x02;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = 0x00;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        int data = buffR[20];
        *value = data;
        return 0;
    }
}

int setFunctionQuitMarker(int index, int value)
{
    if (index < 1 || index > 1000)
        return -1;

    int data;
    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    if (value)
        data = 1;
    else
        data = 0;

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x13;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x02;
    buffS[16] = 0xf5;
    buffS[17] = 0x03;
    buffS[18] = 0x03;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = data;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int getValueParameter(int index, int *value)
{
    if (index < 1 || index > 1000)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x12;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x01;
    buffS[16] = 0xf1;
    buffS[17] = 0x03;
    buffS[18] = 0x02;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = 0x00;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        int value1 = (unsigned char)buffR[20];
        int value2 = (unsigned char)buffR[21];
        *value = value2 * 256 + value1;
        return 0;
    }
}

int setValueParameter(int index, int value)
{
    if (index < 1 || index > 1000)
        return -1;
    if (value < 0 || value > 32767)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int value1 = value % 256;
    int value2 = value / 256;
    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x14;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x02;
    buffS[16] = 0xf1;
    buffS[17] = 0x03;
    buffS[18] = 0x04;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = value1;
    buffS[23] = value2;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int getActualValueParameter(int index, int *value)
{
    if (index < 1 || index > 1000)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x12;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x01;
    buffS[16] = 0xf2;
    buffS[17] = 0x03;
    buffS[18] = 0x02;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = 0x00;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        int value1 = (unsigned char)buffR[20];
        int value2 = (unsigned char)buffR[21];
        *value = value2 * 256 + value1;
        return 0;
    }
}

int setActualValueParameter(int index, int value)
{
    if (index < 1 || index > 1000)
        return -1;
    if (value < 0 || value > 32767)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int value1 = value % 256;
    int value2 = value / 256;
    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x14;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x02;
    buffS[16] = 0xf2;
    buffS[17] = 0x03;
    buffS[18] = 0x04;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = value1;
    buffS[23] = value2;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int getAlarms(int index, int *value)
{
    if (index < 1 || index > 500)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0xe2;
    buffS[3] = 0x01;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x80;
    buffS[16] = 0x20;
    buffS[17] = 0x04;
    buffS[18] = 0xd2;
    buffS[19] = 0x01;
    buffS[20] = 0x01;
    buffS[21] = 0x00;
    buffS[22] = 0xf6;
    buffS[23] = 0x03;
    buffS[24] = index1;
    buffS[24] = index2;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        int data = buffR[26];
        *value = data;
        return 0;
    }
}

int setAlarms(int index, int value)
{
    if (index < 1 || index > 500)
        return -1;

    int data;
    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    if (value)
        data = 1;
    else
        data = 0;

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x13;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x02;
    buffS[16] = 0xf6;
    buffS[17] = 0x03;
    buffS[18] = 0x03;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = data;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int getAlarms2(int index, int *value)
{
    if (index < 1001 || index > 2000)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int index1 = (index - 1000) % 256;
    int index2 = (index - 1000) / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0xe2;
    buffS[3] = 0x01;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x80;
    buffS[16] = 0x20;
    buffS[17] = 0x04;
    buffS[18] = 0xd2;
    buffS[19] = 0x01;
    buffS[20] = 0x01;
    buffS[21] = 0x00;
    buffS[22] = 0x4f;
    buffS[23] = 0x04;
    buffS[24] = index1;
    buffS[25] = index2;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        int data = buffR[26];
        *value = data;
        return 0;
    }
}

int setAlarms2(int index, int value)
{
    if (index < 1001 || index > 2000)
        return -1;

    int data;
    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    if (value)
        data = 1;
    else
        data = 0;

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x13;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x02;
    buffS[16] = 0x4f;
    buffS[17] = 0x04;
    buffS[18] = 0x03;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = data;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int getControlMarker(int index, int *value)
{
    if (index < 1 || index > 1000)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x12;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x01;
    buffS[16] = 0x37;
    buffS[17] = 0x04;
    buffS[18] = 0x02;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = 0x00;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        int data = buffR[20];
        *value = data;
        return 0;
    }
}

int setControlMarker(int index, int value)
{
    if (index < 1 || index > 1000)
        return -1;

    int data;
    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    if (value)
        data = 1;
    else
        data = 0;

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x13;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x02;
    buffS[16] = 0x37;
    buffS[17] = 0x04;
    buffS[18] = 0x03;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = data;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int getControlWords(int index, int *value)
{
    if (index < 1 || index > 200)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x12;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x01;
    buffS[16] = 0x38;
    buffS[17] = 0x04;
    buffS[18] = 0x02;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = 0x00;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        int value1 = (unsigned char)buffR[20];
        int value2 = (unsigned char)buffR[21];
        *value = value2 * 256 + value1;
        return 0;
    }
}

int setControlWords(int index, int value)
{
    if (index < 1 || index > 200)
        return -1;
    if (value < 0 || value > 32767)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int value1 = value % 256;
    int value2 = value / 256;
    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x14;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x02;
    buffS[16] = 0x38;
    buffS[17] = 0x04;
    buffS[18] = 0x04;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = value1;
    buffS[23] = value2;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int getControllerParameter(int index, int *value)
{
    if (index < 1 || index > 4000)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x12;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x01;
    buffS[16] = 0x04;
    buffS[17] = 0x04;
    buffS[18] = 0x02;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = 0x00;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        int value1 = (unsigned char)buffR[20];
        int value2 = (unsigned char)buffR[21];
        *value = value2 * 256 + value1;
        return 0;
    }
}

int setControllerParameter(int index, int value)
{
    if (index < 1 || index > 4000)
        return -1;
    if (value < 0 || value > 32767)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int value1 = value % 256;
    int value2 = value / 256;
    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x14;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x02;
    buffS[16] = 0x04;
    buffS[17] = 0x04;
    buffS[18] = 0x04;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = value1;
    buffS[23] = value2;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int getTimers(int index, int *value)
{
    if (index < 1 || index > 500)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x12;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x01;
    buffS[16] = 0x03;
    buffS[17] = 0x04;
    buffS[18] = 0x02;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = 0x00;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        int value1 = (unsigned char)buffR[20];
        int value2 = (unsigned char)buffR[21];
        *value = value2 * 256 + value1;
        return 0;
    }
}

int setTimers(int index, int value)
{
    if (index < 1 || index > 500)
        return -1;
    if (value < 0 || value > 32767)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int value1 = value % 256;
    int value2 = value / 256;
    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x14;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x02;
    buffS[16] = 0x03;
    buffS[17] = 0x04;
    buffS[18] = 0x04;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = value1;
    buffS[23] = value2;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int getMachineConstant(int index, int *value)
{
    if (index < 1 || index > 500)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x12;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x01;
    buffS[16] = 0x05;
    buffS[17] = 0x04;
    buffS[18] = 0x02;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = 0x00;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        int value1 = (unsigned char)buffR[20];
        int value2 = (unsigned char)buffR[21];
        *value = value2 * 256 + value1;
        return 0;
    }
}

int setMachineConstant(int index, int value)
{
    if (index < 1 || index > 500)
        return -1;
    if (value < 0 || value > 32767)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int value1 = value % 256;
    int value2 = value / 256;
    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x14;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x02;
    buffS[16] = 0x05;
    buffS[17] = 0x04;
    buffS[18] = 0x04;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = value1;
    buffS[23] = value2;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int getBatchParameter(int index, int *value)
{
    if (index < 1 || index > 50)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x12;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x01;
    buffS[16] = 0x34;
    buffS[17] = 0x04;
    buffS[18] = 0x02;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = 0x00;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        int value1 = (unsigned char)buffR[20];
        int value2 = (unsigned char)buffR[21];
        *value = value2 * 256 + value1;
        return 0;
    }
}

int setBatchParameter(int index, int value)
{
    if (index < 1 || index > 50)
        return -1;
    if (value < 0 || value > 32767)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int value1 = value % 256;
    int value2 = value / 256;
    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x14;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x02;
    buffS[16] = 0x34;
    buffS[17] = 0x04;
    buffS[18] = 0x04;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = value1;
    buffS[23] = value2;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int getBatchParameterDS737(int index, int *value)
{
    if (index < 1 || index > 50)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x12;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x01;
    buffS[16] = 0x36;
    buffS[17] = 0x04;
    buffS[18] = 0x02;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = 0x00;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        int value1 = (unsigned char)buffR[20];
        int value2 = (unsigned char)buffR[21];
        *value = value2 * 256 + value1;
        return 0;
    }
}

int setBatchParameterDS737(int index, int value)
{
    if (index < 1 || index > 50)
        return -1;
    if (value < 0 || value > 32767)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int value1 = value % 256;
    int value2 = value / 256;
    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x14;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x02;
    buffS[16] = 0x36;
    buffS[17] = 0x04;
    buffS[18] = 0x04;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = value1;
    buffS[23] = value2;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int getBatchParameterNextBatch(int index, int *value)
{
    if (index < 1 || index > 50)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x12;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x01;
    buffS[16] = 0x35;
    buffS[17] = 0x04;
    buffS[18] = 0x02;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = 0x00;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        int value1 = (unsigned char)buffR[20];
        int value2 = (unsigned char)buffR[21];
        *value = value2 * 256 + value1;
        return 0;
    }
}

int setBatchParameterNextBatch(int index, int value)
{
    if (index < 1 || index > 50)
        return -1;
    if (value < 0 || value > 32767)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int value1 = value % 256;
    int value2 = value / 256;
    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x14;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x02;
    buffS[16] = 0x35;
    buffS[17] = 0x04;
    buffS[18] = 0x04;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = value1;
    buffS[23] = value2;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int getMaintenanceCounter(int index, int *value)
{
    if (index < 1 || index > 200)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x12;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x01;
    buffS[16] = 0x53;
    buffS[17] = 0x04;
    buffS[18] = 0x02;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = 0x00;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        int value1 = (unsigned char)buffR[20];
        int value2 = (unsigned char)buffR[21];
        *value = value2 * 256 + value1;
        return 0;
    }
}

int setMaintenanceCounter(int index, int value)
{
    if (index < 1 || index > 200)
        return -1;
    if (value < 0 || value > 32767)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int value1 = value % 256;
    int value2 = value / 256;
    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x16;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x02;
    buffS[16] = 0x53;
    buffS[17] = 0x04;
    buffS[18] = 0x06;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = value1;
    buffS[23] = value2;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int getActionButtons(int index, int *value)
{
    if (index < 401 || index > 1000)
        return -1;

    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x12;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x01;
    buffS[16] = 0x37;
    buffS[17] = 0x04;
    buffS[18] = 0x02;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = 0x00;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        int data = buffR[20];
        *value = data;
        return 0;
    }
}

int setActionButtons(int index, int value)
{
    if (index < 401 || index > 1000)
        return -1;

    int data;
    int bytesRecv;
    char buffR[BUFFER_SIZE];
    char buffS[BUFFER_SIZE];

    memset(buffS, 0, sizeof(buffS));
    memset(buffR, 0, sizeof(buffR));

    if (value)
        data = 1;
    else
        data = 0;

    int index1 = index % 256;
    int index2 = index / 256;

    buffS[0] = 0x02;
    buffS[1] = 0x00;
    buffS[2] = 0x13;
    buffS[3] = 0x00;
    buffS[12] = 0x00;
    buffS[13] = 0x00;
    buffS[14] = 0x01;
    buffS[15] = 0x02;
    buffS[16] = 0x37;
    buffS[17] = 0x04;
    buffS[18] = 0x03;
    buffS[19] = 0x00;
    buffS[20] = index1;
    buffS[21] = index2;
    buffS[22] = data;
    buffS[23] = 0x00;

    send(sockHandle, buffS, BUFFER_SIZE, 0);
    usleep(10);

    bytesRecv = recv(sockHandle, buffR, BUFFER_SIZE, 0);
    if (bytesRecv < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
