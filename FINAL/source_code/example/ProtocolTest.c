#include <stdio.h>     // 표준 입력/출력 기능을 사용하기 위한 라이브러리 포함
#include <stdlib.h>    // 일반적인 유틸리티 함수와 메모리 관리 함수를 사용하기 위한 라이브러리 포함
#include <string.h>    // 문자열 관련 함수를 사용하기 위한 라이브러리 포함
#include <arpa/inet.h> // 인터넷 주소 변환 및 관련 함수를 사용하기 위한 라이브러리 포함
#include <stdbool.h>   // C99 표준에 도입된 불리언 자료형과 관련된 라이브러리 포함

typedef unsigned char BYTE; // 8비트 부호 없는 정수를 BYTE로 정의
typedef void *LPVOID;       // 포인터 형식을 LPVOID로 정의
typedef unsigned int DWORD; // 32비트 부호 없는 정수를 DWORD로 정의
typedef BYTE *LPBYTE;       // BYTE 형식의 포인터를 LPBYTE로 정의

#include "FAS_EziMOTIONPlusE.h"
#include "EthernetInterface.h"
#include "Fsocket.h"

#include "ReturnCodes_Define.h"
#include "ETHERNET_DEFINE.h"
#include "INTERNAL_MOTION_DEFINE.h"
#include "PROTOCOL_FRAME_DEFINE.h"

int m_socket, m_nSyncNo, m_bTCP;
struct sockaddr_in server_addr; // 서버 주소 정보를 외부에서 선언하여 사용합니다.
ssize_t received_bytes = 0;     //
BYTE m_BuffSend[MAX_BUFFER_SIZE];
BYTE m_BuffRecv[MAX_BUFFER_SIZE];

int main()
{
    char server_ip[SERVER_IP_SIZE] = "192.168.0.171";
    int menu, OnOff, speed, jog;

    // 서버에 UDP로 연결합니다.
    FAS_ConnectTCP(server_ip);

    while (1)
    {
        printf("\nCommand(ex. 2A): ");
        if (scanf("%x", &menu) != 1)
        {
            // 입력이 16진수가 아닌 경우 처리
            printf("Invalid input. Please enter a hexadecimal value.\n");

            // 입력 버퍼 비우기
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            continue;
        }
        printf("\n");

        switch (menu)
        {
        case 0x2a:
            printf("-Enable\nON(1), OFF(0): ");
            scanf("%d", &OnOff);

            // 서보 활성화/비활성화를 설정합니다.
            FAS_ServoEnable(OnOff);
            break;

        case 0x2b:
            // 서보 알람을 리셋합니다.
            FAS_ServoAlarmReset();
            break;

        case 0x31:
            // 서보 모터를 정지합니다.
            FAS_MoveStop();
            break;

        case 0x37:
            printf("-Speed: ");
            scanf("%d", &speed);

            printf("\n-Direction\n");
            printf("+Jog(1), -Jog(0): ");
            scanf("%x", &jog);

            // 지정한 속도와 방향으로 서보 모터를 조종합니다.
            FAS_MoveVelocity(speed, jog);
            break;

        case 0x43:
            // 모든 상태 정보를 가져옵니다.
            FAS_GetAllStatus();
            // 입력상태[0] 6-9, 출력상태[1] 10-13, 상태 Flag[2] 14-17, command pos[3] 18-21, actual pos[4] 22-25, pos차이[5] 26-29, 운전속도[6] 30-33, 현재 pt번호[7] 34-37
            uint32_t m_status[8];
            for (int i = 6; i < 35; i += 4)
            {
                m_status[(i - 6) / 4] = (m_BuffRecv[i] | (m_BuffRecv[i + 1] << 8) | (m_BuffRecv[i + 2] << 16) | (m_BuffRecv[i + 3] << 24));
            }
            printf("\ncommand pos: %d\n", m_status[3]);
            printf("actual pos: %d\n", m_status[4]);
            printf("pos: %d\n", m_status[5]);
            printf("velocity: %d\n", m_status[6]);
            break;

        default:
            printf("Invalid menu option.\n");
        }

        printf("\nRaspberrypi: ");
        for (ssize_t i = 0; i < m_BuffSend[1] + 2; i++)
        {
            // 보낼 데이터를 16진수 형식으로 출력합니다.
            printf("%02X ", (unsigned char)m_BuffSend[i]);
        }

        printf("\nServer: ");
        for (ssize_t i = 0; i < received_bytes; i++)
        {
            // 받은 데이터를 16진수 형식으로 출력합니다.
            printf("%02X ", (unsigned char)m_BuffRecv[i]);
        }
        printf("\n");
    }
}