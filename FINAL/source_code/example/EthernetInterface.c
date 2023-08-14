#include <stdio.h>          // 표준 입력/출력 기능을 사용하기 위한 라이브러리 포함
#include <stdbool.h>        // C99 표준에 도입된 불리언 자료형과 관련된 라이브러리 포함

#include "Fsocket.h"
#include "EthernetInterface.h"

typedef unsigned char BYTE; // 8비트 부호 없는 정수를 BYTE로 정의
typedef void *LPVOID;       // 포인터 형식을 LPVOID로 정의
typedef unsigned int DWORD; // 32비트 부호 없는 정수를 DWORD로 정의
typedef BYTE *LPBYTE;       // BYTE 형식의 포인터를 LPBYTE로 정의



//------------------------------------------------------------------
//                Motion Functions.
//------------------------------------------------------------------
// 서보 활성화/비활성화 명령을 수행하는 함수
int DoCmdServoEnable(bool bOnOff)
{
    BYTE byValue = (BYTE)(bOnOff) ? 0x01 : 0x00;  // bOnOff 값에 따라 byValue 설정

    return DoSendCommand(FRAME_FAS_SERVOENABLE, &byValue, 1, NULL, 0);  // 명령 전송 함수 호출
}

// 서보 알람 리셋 명령을 수행하는 함수
int DoCmdServoAlarmReset()
{
    return DoSendCommand(FRAME_FAS_ALARMRESET, NULL, 0, NULL, 0);  // 명령 전송 함수 호출
}

// 서보 모터 정지 명령을 수행하는 함수
int DoCmdMoveStop()
{
    return DoSendCommand(FRAME_FAS_MOVESTOP, NULL, 0, NULL, 0);  // 명령 전송 함수 호출
}

// 속도와 방향으로 서보 모터 이동 명령을 수행하는 함수
int DoCmdMoveVelocity(DWORD lVelocity, int iVelDir)
{
    BYTE byValue[5];
    UNION_4DATA data;

    data.lValue = lVelocity;  // 속도 값 설정
    byValue[0] = data.byValue[0];
    byValue[1] = data.byValue[1];
    byValue[2] = data.byValue[2];
    byValue[3] = data.byValue[3];
    byValue[4] = (BYTE)iVelDir;  // 방향 값 설정

    return DoSendCommand(FRAME_FAS_MOVEVELOCITY, byValue, 5, NULL, 0);  // 명령 전송 함수 호출
}

// 모든 상태 정보를 가져오는 명령을 수행하는 함수
int DoCmdGetAllStatus()
{
    return DoSendCommand(FRAME_FAS_GETALLSTATUS, NULL, 0, NULL, 0);  // 명령 전송 함수 호출
}
