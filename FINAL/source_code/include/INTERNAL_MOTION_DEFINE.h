#pragma once
typedef unsigned char BYTE;
typedef void* LPVOID;
typedef unsigned int DWORD;
typedef unsigned short WORD;
typedef BYTE* LPBYTE;

typedef union
{
	char	chValue[4];
	BYTE	byValue[4];
	long	lValue;
	DWORD	dwValue;
} UNION_4DATA;

typedef union
{
	char	chValue[2];
	BYTE	byValue[2];
	short	shValue;
	WORD	wValue;
} UNION_2DATA;