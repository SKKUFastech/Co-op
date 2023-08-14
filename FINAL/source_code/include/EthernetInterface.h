#ifndef ETHERNET_INTERFACE_H
#define ETHERNET_INTERFACE_H

#include <stdio.h>
#include <stdbool.h>

#include "ReturnCodes_Define.h"
#include "ETHERNET_DEFINE.h"
#include "INTERNAL_MOTION_DEFINE.h"
#include "PROTOCOL_FRAME_DEFINE.h"

typedef unsigned char BYTE;
typedef void *LPVOID;
typedef unsigned int DWORD;
typedef BYTE *LPBYTE;

//------------------------------------------------------------------
//                Motion Functions.
//------------------------------------------------------------------
int DoCmdServoEnable(bool bOnOff);
int DoCmdServoAlarmReset();
int DoCmdMoveStop();
int DoCmdMoveVelocity(DWORD lVelocity, int iVelDir);
int DoCmdGetAllStatus();

#endif // ETHERNET_INTERFACE_H
