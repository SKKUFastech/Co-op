#include <stdio.h>     // 표준 입력/출력 기능을 사용하기 위한 라이브러리 포함
#include <stdlib.h>    // 일반적인 유틸리티 함수와 메모리 관리 함수를 사용하기 위한 라이브러리 포함
#include <string.h>    // 문자열 관련 함수를 사용하기 위한 라이브러리 포함
#include <arpa/inet.h> // 인터넷 주소 변환 및 관련 함수를 사용하기 위한 라이브러리 포함
#include <stdbool.h>   // C99 표준에 도입된 불리언 자료형과 관련된 라이브러리 포함

#include "FAS_EziMOTIONPlusE.h"
#include "EthernetInterface.h"

#include "ReturnCodes_Define.h"
#include "ETHERNET_DEFINE.h"
#include "INTERNAL_MOTION_DEFINE.h"
#include "PROTOCOL_FRAME_DEFINE.h"

typedef unsigned char BYTE; // 8비트 부호 없는 정수를 BYTE로 정의
typedef void *LPVOID;       // 포인터 형식을 LPVOID로 정의
typedef unsigned int DWORD; // 32비트 부호 없는 정수를 DWORD로 정의
typedef BYTE *LPBYTE;       // BYTE 형식의 포인터를 LPBYTE로 정의

extern int m_socket, m_nSyncNo, m_bTCP;  // 클라이언트 소켓 및 관련 변수들을 외부에서 참조하도록 선언
extern struct sockaddr_in server_addr;   // 서버 주소 정보를 외부에서 참조하도록 선언
extern BYTE m_BuffSend[MAX_BUFFER_SIZE]; // 보낼 데이터를 저장하는 배열을 외부에서 참조하도록 선언
extern BYTE m_BuffRecv[MAX_BUFFER_SIZE]; // 받은 데이터를 저장하는 배열을 외부에서 참조하도록 선언

//------------------------------------------------------------------
//                FAS_EziMOTIONPlusE
//------------------------------------------------------------------

// UDP 연결을 수행하는 함수
int FAS_ConnectUDP(char *server_ip)
{
    // 소켓 생성
    if ((m_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("소켓 생성 실패");
        exit(EXIT_FAILURE);
        return false;
    }

    memset(&server_addr, 0, sizeof(server_addr));

    // 서버 주소 설정
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(UDP_PORT_NO1);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0)
    {
        perror("inet_pton 실패");
        exit(EXIT_FAILURE);
        return false;
    }

    // close(client_socket); // 주석 처리된 부분은 소켓을 연결한 후에 연결을 종료하는 코드

    m_bTCP = 0; // TCP 연결 상태 변수 업데이트
    return true;
}

// TCP 연결을 수행하는 함수
int FAS_ConnectTCP(char *server_ip)
{
    // 소켓 생성
    if ((m_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("소켓 생성 실패");
        exit(EXIT_FAILURE);
        return false;
    }

    // sockaddr_in 구조체 초기화
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    server_addr.sin_port = htons(TCP_PORT_NO1);

    // 서버에 연결
    if (connect(m_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("연결 실패");
        exit(EXIT_FAILURE);
        return false;
    }

    m_bTCP = 1; // TCP 연결 상태 변수 업데이트
    return true;
}

// 서보 활성화/비활성화를 수행하는 함수
int FAS_ServoEnable(bool bOnOff)
{
    int nRtn = FMM_OK;
    if (m_socket == NULL)
        return FMM_NOT_OPEN;
    nRtn = DoCmdServoEnable(bOnOff);
    return nRtn;
}

// 서보 알람 리셋을 수행하는 함수
int FAS_ServoAlarmReset()
{
    int nRtn;
    if (m_socket == NULL)
        return FMM_NOT_OPEN;
    nRtn = DoCmdServoAlarmReset();
    return nRtn;
}

// 서보 모터 정지를 수행하는 함수
int FAS_MoveStop()
{
    int nRtn;
    if (m_socket == NULL)
        return FMM_NOT_OPEN;

    nRtn = DoCmdMoveStop();

    return nRtn;
}

// 서보 모터를 속도와 방향으로 이동시키는 함수
int FAS_MoveVelocity(DWORD lVelocity, int iVelDir)
{
    int nRtn;
    if (m_socket == NULL)
        return FMM_NOT_OPEN;
    nRtn = DoCmdMoveVelocity(lVelocity, iVelDir);
    return nRtn;
}

// 모든 상태 정보를 가져오는 함수
int FAS_GetAllStatus()
{
    int nRtn;
    if (m_socket == NULL)
        return FMM_NOT_OPEN;

    nRtn = DoCmdGetAllStatus();

    return nRtn;
}