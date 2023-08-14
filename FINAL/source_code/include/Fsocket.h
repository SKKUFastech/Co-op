#ifndef FSOCKET_H
#define FSOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "ReturnCodes_Define.h"
#include "ETHERNET_DEFINE.h"
#include "INTERNAL_MOTION_DEFINE.h"
#include "PROTOCOL_FRAME_DEFINE.h"

typedef unsigned char BYTE;
typedef void *LPVOID;
typedef unsigned int DWORD;
typedef BYTE *LPBYTE;

#define BUFFER_SIZE 256

extern BYTE m_BuffSend[BUFFER_SIZE];
extern BYTE m_BuffRecv[BUFFER_SIZE];
extern int m_nSyncNo, m_bTCP;
extern int m_socket;
extern struct sockaddr_in server_addr;

int DoSendCommand(BYTE byCmd, LPVOID lpIN, DWORD dwINlen, LPVOID lpOUT, DWORD dwOUTlen);
int SendTCPPacket(BYTE FrameType, LPBYTE lpData, DWORD dwLen);
int RecvTCPPacket(BYTE FrameType, LPBYTE lpData, DWORD dwLen);
int SendUDPPacket(BYTE FrameType, LPBYTE lpData, DWORD dwLen);
int RecvUDPPacket(BYTE FrameType, LPBYTE lpData, DWORD dwLen);

#endif // FSOCKET_H
