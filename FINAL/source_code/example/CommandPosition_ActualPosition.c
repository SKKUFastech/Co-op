#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

typedef unsigned char BYTE;
typedef void *LPVOID;
typedef unsigned int DWORD;
typedef BYTE *LPBYTE;

#include "FAS_EziMOTIONPlusE.h"
#include "EthernetInterface.h"
#include "Fsocket.h"

#include "ReturnCodes_Define.h"
#include "ETHERNET_DEFINE.h"
#include "INTERNAL_MOTION_DEFINE.h"
#include "PROTOCOL_FRAME_DEFINE.h"

int m_socket, m_nSyncNo, m_bTCP; // 클라이언트 소켓을 외부에서 선언하여 사용합니다.
struct sockaddr_in server_addr;  // 서버 주소 정보를 외부에서 선언하여 사용합니다.
ssize_t received_bytes = 0;
BYTE m_BuffSend[MAX_BUFFER_SIZE];
BYTE m_BuffRecv[MAX_BUFFER_SIZE];

void delay_ms(unsigned int milliseconds)
{
    struct timespec req;
    req.tv_sec = milliseconds / 1000;
    req.tv_nsec = (milliseconds % 1000) * 1000000;

    nanosleep(&req, (struct timespec *)NULL);
}

int main()
{
    char server_ip[SERVER_IP_SIZE] = "192.168.0.171";
    int menu, OnOff, speed, jog, cnt = 0;
    uint32_t m_status[8];

    // 터미널 설정 저장
    struct termios original;
    tcgetattr(STDIN_FILENO, &original);

    // 터미널을 비정규 모드로 설정
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    // CSV 파일 열기
    FILE *csvFileCommand = fopen("outputcommand.csv", "w");
    FILE *csvFileActual = fopen("outputactual.csv", "w");
    if (csvFileCommand == NULL || csvFileActual == NULL)
    {
        perror("Error opening CSV file");
        return 1;
    }

    FAS_ConnectTCP(server_ip);
    while (1)
    {
        //system("clear");
        FAS_GetAllStatus();
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

        // 입력상태[0] 6-9, 출력상태[1] 10-13, 상태 Flag[2] 14-17, command pos[3] 18-21, actual pos[4] 22-25, pos차이[5] 26-29, 운전속도[6] 30-33, 현재 pt번호[7] 34-37
        for (int i = 6; i < 35; i += 4)
        {
            m_status[(i - 6) / 4] = (m_BuffRecv[i] | (m_BuffRecv[i + 1] << 8) | (m_BuffRecv[i + 2] << 16) | (m_BuffRecv[i + 3] << 24));
        }
        fprintf(csvFileCommand, "%d\n", m_status[3]);
        fprintf(csvFileActual, "%d\n", m_status[4]);

        printf("\ncommand pos: %d\n", m_status[3]);
        printf("actual pos: %d\n", m_status[4]);
        printf("pos: %d\n", m_status[5]);
        printf("velocity: %d\n", m_status[6]);
        

        // cnt++;
        // if (cnt == 20)
        //     break;

        // 입력 대기 시간 설정
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 100000; // 100ms

        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);

        // 입력 대기 시간 내에 키 입력 감지
        int result = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);

        if (result == -1)
        {
            perror("select");
            break;
        }
        else if (result > 0 && FD_ISSET(STDIN_FILENO, &fds))
        {
            // 키 입력이 감지되면 루프 종료
            break;
        }

        delay_ms(90);
    }

    // CSV 파일 닫기
    fclose(csvFileCommand);
    fclose(csvFileActual);

    // 터미널 설정 복원
    tcsetattr(STDIN_FILENO, TCSANOW, &original);
}