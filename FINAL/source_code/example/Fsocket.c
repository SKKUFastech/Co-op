#include <stdio.h>     // 표준 입력/출력 기능을 사용하기 위한 라이브러리 포함
#include <stdlib.h>    // 일반적인 유틸리티 함수와 메모리 관리 함수를 사용하기 위한 라이브러리 포함
#include <string.h>    // 문자열 관련 함수를 사용하기 위한 라이브러리 포함
#include <arpa/inet.h> // 인터넷 주소 변환 및 관련 함수를 사용하기 위한 라이브러리 포함

#include "Fsocket.h"

typedef unsigned char BYTE; // 8비트 부호 없는 정수를 BYTE로 정의
typedef void *LPVOID;       // 포인터 형식을 LPVOID로 정의
typedef unsigned int DWORD; // 32비트 부호 없는 정수를 DWORD로 정의
typedef BYTE *LPBYTE;       // BYTE 형식의 포인터를 LPBYTE로 정의

extern BYTE m_BuffSend[MAX_BUFFER_SIZE]; // 보낼 데이터를 저장합니다.
extern BYTE m_BuffRecv[MAX_BUFFER_SIZE]; // 받은 데이터를 저장합니다.
extern int m_socket, m_nSyncNo, m_bTCP;
extern ssize_t received_bytes;         // 받은 데이터의 크기를 저장합니다.
extern struct sockaddr_in server_addr; // 서버 주소 정보를 외부에서 선언하여 사용합니다.

int SendTCPPacket(BYTE FrameType, LPBYTE lpData, DWORD dwLen)
{
    m_BuffSend[SENDOFFSET_HEADER] = 0xAA;
    m_BuffSend[SENDOFFSET_LENGTH] = (unsigned char)(dwLen + 3);
    m_BuffSend[SENDOFFSET_SYNC] = m_nSyncNo;
    m_BuffSend[SENDOFFSET_AXIS] = 0x00;
    m_BuffSend[SENDOFFSET_CMD] = FrameType;
    if (dwLen > 0)
        memcpy(&(m_BuffSend[SENDOFFSET_DATA]), lpData, dwLen);
    send(m_socket, m_BuffSend, dwLen + 5, 0);
    return 1;
}

int RecvTCPPacket(BYTE FrameType, LPBYTE lpData, DWORD dwLen)
{
    received_bytes = recv(m_socket, m_BuffRecv, MAX_BUFFER_SIZE, 0);
    if (received_bytes <= 0)
    {
        perror("recv 실패");
    }
    m_BuffRecv[received_bytes] = '\0';
}

int SendUDPPacket(BYTE FrameType, LPBYTE lpData, DWORD dwLen)
{
    m_BuffSend[SENDOFFSET_HEADER] = 0xAA;
    m_BuffSend[SENDOFFSET_LENGTH] = (unsigned char)(dwLen + 3);
    m_BuffSend[SENDOFFSET_SYNC] = m_nSyncNo;
    m_BuffSend[SENDOFFSET_AXIS] = 0x00;
    m_BuffSend[SENDOFFSET_CMD] = FrameType;
    if (dwLen > 0)
        memcpy(&(m_BuffSend[SENDOFFSET_DATA]), lpData, dwLen);

    int send_result = sendto(m_socket, (const char *)m_BuffSend, dwLen + 5, 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));
    if (send_result < 0)
    {
        perror("sendto 실패");
    }
    return 1;
}

int RecvUDPPacket(BYTE FrameType, LPBYTE lpData, DWORD dwLen)
{
    received_bytes = recvfrom(m_socket, m_BuffRecv, sizeof(m_BuffRecv), 0, NULL, NULL);
    if (received_bytes < 0)
    {
        perror("recvfrom 실패");
    }
}

int DoSendCommand(BYTE byCmd, LPVOID lpIN, DWORD dwINlen, LPVOID lpOUT, DWORD dwOUTlen)
{
    int nRtn = FMM_OK;
    m_nSyncNo++;
    if (m_bTCP)
    {
        if (SendTCPPacket(byCmd, (BYTE *)lpIN, dwINlen))
        {
            // Recv
            nRtn = RecvTCPPacket(byCmd, (BYTE *)lpOUT, dwOUTlen);
        }
        else
        {
            nRtn = FMC_DISCONNECTED;
        }
    }
    else // UDP
    {
        if (SendUDPPacket(byCmd, (BYTE *)lpIN, dwINlen))
        {
            // Recv
            nRtn = RecvUDPPacket(byCmd, (BYTE *)lpOUT, dwOUTlen);
        }
        else
        {
            nRtn = FMC_DISCONNECTED;
        }
    }
    return nRtn;
}
