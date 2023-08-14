#ifndef FAS_EZIMOTIONPLUSE_H
#define FAS_EZIMOTIONPLUSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdbool.h>


typedef unsigned char BYTE;
typedef void *LPVOID;
typedef unsigned int DWORD;
typedef BYTE *LPBYTE;

#define BUFFER_SIZE 256

//------------------------------------------------------------------
//                FAS_EziMOTIONPlusE
//------------------------------------------------------------------
int FAS_ConnectUDP(char *server_ip);
int FAS_ConnectTCP(char *server_ip);
int FAS_ServoEnable(bool bOnOff);
int FAS_ServoAlarmReset();
int FAS_MoveStop();
int FAS_GetAllStatus();
int FAS_MoveVelocity(DWORD lVelocity, int iVelDir);

#endif // FAS_EZIMOTIONPLUSE_H
