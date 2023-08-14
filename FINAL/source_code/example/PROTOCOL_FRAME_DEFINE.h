#pragma once

typedef unsigned char BYTE;
typedef void *LPVOID;
typedef unsigned int DWORD;
typedef BYTE *LPBYTE;
//------------------------------------------------------------------
//                 FRAME TYPE Defines.
//------------------------------------------------------------------
static const BYTE	FRAME_GETSLAVEINFO			= 0x01;
static const BYTE	FRAME_GETMOTORINFO			= 0x05;

static const BYTE	FRAME_GETSLAVEINFO_EX		= 0x09;

static const BYTE	FRAME_FAS_SAVEALLPARAM		= 0x10;
static const BYTE	FRAME_FAS_GETROMPARAM		= 0x11;
static const BYTE	FRAME_FAS_SETPARAMETER		= 0x12;
static const BYTE	FRAME_FAS_GETPARAMETER		= 0x13;

static const BYTE	FRAME_GET_ETHERNET_ADDR		= 0x14;
static const BYTE	FRAME_SET_ETHERNET_ADDR		= 0x15;

static const BYTE	FRAME_FAS_SETIO_OUTPUT		= 0x20;
static const BYTE	FRAME_FAS_SETIO_INPUT		= 0x21;
static const BYTE	FRAME_FAS_GETIO_INPUT		= 0x22;
static const BYTE	FRAME_FAS_GETIO_OUTPUT		= 0x23;

static const BYTE	FRAME_FAS_SET_IO_ASSGN_MAP	= 0x24;
static const BYTE	FRAME_FAS_GET_IO_ASSGN_MAP	= 0x25;
static const BYTE	FRAME_FAS_IO_ASSGN_MAP_READROM	= 0x26;

// Trigger commands.
static const BYTE	FRAME_FAS_TRIGGER_OUTPUT	= 0x27;
static const BYTE	FRAME_FAS_TRIGGER_STATUS	= 0x28;

static const BYTE	FRAME_FAS_SERVOENABLE		= 0x2A;
static const BYTE	FRAME_FAS_ALARMRESET		= 0x2B;
static const BYTE	FRAME_FAS_STEPALARMRESET	= 0x2C;	// Step Alarm Reset function.

static const BYTE	FRAME_FAS_BRAKESET			= 0x2D;
static const BYTE	FRAME_FAS_GETALARMTYPE		= 0x2E;	// Alarm Type

static const BYTE	FRAME_FAS_GETAXISSTATUS		= 0x40;
static const BYTE	FRAME_FAS_GETIOAXISSTATUS	= 0x41;
static const BYTE	FRAME_FAS_GETMOTIONSTATUS	= 0x42;
static const BYTE	FRAME_FAS_GETALLSTATUS		= 0x43;
static const BYTE	FRAME_FAS_GETALLSTATUSEX	= 0x4D;

static const BYTE	FRAME_FAS_GETALLTORQUESTATUS	= 0x45;
static const BYTE	FRAME_FAS_GETTORQUESTATUS		= 0x46;

static const BYTE	FRAME_FAS_SETCMDPOS			= 0x50;
static const BYTE	FRAME_FAS_GETCMDPOS			= 0x51;
static const BYTE	FRAME_FAS_SETACTPOS			= 0x52;
static const BYTE	FRAME_FAS_GETACTPOS			= 0x53;
static const BYTE	FRAME_FAS_GETPOSERR			= 0x54;
static const BYTE	FRAME_FAS_GETACTVEL			= 0x55;
static const BYTE	FRAME_FAS_CLEARPOS			= 0x56;

static const BYTE	FRAME_FAS_MOVEPAUSE			= 0x58;

static const BYTE	FRAME_FAS_MOVESTOP			= 0x31;
static const BYTE	FRAME_FAS_EMERGENCYSTOP		= 0x32;

static const BYTE	FRAME_FAS_MOVEORIGIN		= 0x33;
static const BYTE	FRAME_FAS_MOVESINGLEABS		= 0x34;
static const BYTE	FRAME_FAS_MOVESINGLEINC		= 0x35;
static const BYTE	FRAME_FAS_MOVETOLIMIT		= 0x36;
static const BYTE	FRAME_FAS_MOVEVELOCITY		= 0x37;

static const BYTE	FRAME_FAS_POSABSOVERRIDE	= 0x38;
static const BYTE	FRAME_FAS_POSINCOVERRIDE	= 0x39;
static const BYTE	FRAME_FAS_VELOVERRIDE		= 0x3A;

static const BYTE	FRAME_FAS_ALLMOVESTOP		= 0x3B;
static const BYTE	FRAME_FAS_ALLEMERGENCYSTOP	= 0x3C;
static const BYTE	FRAME_FAS_ALLMOVEORIGIN		= 0x3D;
static const BYTE	FRAME_FAS_ALLMOVESINGLEABS	= 0x3E;
static const BYTE	FRAME_FAS_ALLMOVESINGLEINC	= 0x3F;

// Position Table specific commands.
static const BYTE	FRAME_FAS_POSTAB_READ_ITEM		= 0x60;
static const BYTE	FRAME_FAS_POSTAB_WRITE_ITEM		= 0x61;
static const BYTE	FRAME_FAS_POSTAB_READ_ROM		= 0x62;
static const BYTE	FRAME_FAS_POSTAB_WRITE_ROM		= 0x63;
static const BYTE	FRAME_FAS_POSTAB_RUN_ITEM		= 0x64;
static const BYTE	FRAME_FAS_POSTAB_IS_DATA		= 0x65;

static const BYTE	FRAME_FAS_POSTAB_IS_DATA_EX		= 0x6C;

static const BYTE	FRAME_FAS_POSTAB_RUN_ONEITEM	= 0x68;
static const BYTE	FRAME_FAS_POSTAB_CHECK_STOPMODE	= 0x69;

static const BYTE	FRAME_FAS_POSTAB_READ_ONEITEM	= 0x6A;
static const BYTE	FRAME_FAS_POSTAB_WRITE_ONEITEM	= 0x6B;

// Linear Motion Commands
static const BYTE	FRAME_FAS_SETLINEARINFO			= 0x70;
static const BYTE	FRAME_FAS_MOVELINEARINC			= 0x71;
static const BYTE	FRAME_FAS_SETLINEARINFO2		= 0x72;

// Push Motion Commands
static const BYTE	FRAME_FAS_MOVEPUSH				= 0x78;
static const BYTE	FRAME_FAS_GETPUSHSTATUS			= 0x79;

// Circular Interpolation Motion Commands
static const BYTE	FRAME_SET_CIRCULAR_INFO			= 0x7A;
static const BYTE	FRAME_MOVE_CIRCULAR				= 0x7B;

// Trigger Ex Commands
static const BYTE	FRAME_SET_TRIGGEROUTPUT_EX		= 0x7E;
static const BYTE	FRAME_GET_TRIGGEROUTPUT_EX		= 0x7F;

// Ex-Motion Commands
static const BYTE	FRAME_FAS_MOVESINGLEABS_EX		= 0x80;
static const BYTE	FRAME_FAS_MOVESINGLEINC_EX		= 0x81;
static const BYTE	FRAME_FAS_MOVEVELOCITY_EX		= 0x82;

// Controlling GAP Commands
static const BYTE	FRAME_FAS_GAPCONTROL_ENABLE		= 0x94;
static const BYTE	FRAME_FAS_GAPCONTROL_DISABLE	= 0x95;
static const BYTE	FRAME_FAS_GAPCONTROL_ISENABLE	= 0x96;

static const BYTE	FRAME_FAS_GAPCONTROL_GETADCVALUE	= 0x97;
static const BYTE	FRAME_FAS_GAPONERESULT_MONITOR	= 0x98;

// Alarm Log Functions
static const BYTE	FRAME_ALARM_GETLOGS				= 0x9C;
static const BYTE	FRAME_ALARM_RESETLOGS			= 0x9D;

// I/O Module Functions.
static const BYTE	FRAME_IO_GET_INPUT				= 0xC0;
static const BYTE	FRAME_IO_CLEAR_LATCH			= 0xC1;
static const BYTE	FRAME_IO_GET_LATCH_COUNT		= 0xC2;
static const BYTE	FRAME_IO_GET_LATCH_COUNT_ALL16	= 0xC3;
static const BYTE	FRAME_IO_GET_LATCH_COUNT_ALL32	= 0xBD;
static const BYTE	FRAME_IO_CLEAR_LATCH_COUNT		= 0xC4;
static const BYTE	FRAME_IO_GET_OUTPUT				= 0xC5;
static const BYTE	FRAME_IO_SET_OUTPUT				= 0xC6;
static const BYTE	FRAME_IO_SET_TRIGGER			= 0xC7;
static const BYTE	FRAME_IO_SET_RUNSTOP			= 0xC8;
static const BYTE	FRAME_IO_GET_TRIGGER_COUNT		= 0xC9;
static const BYTE	FRAME_IO_GET_IO_LEVEL			= 0xCA;
static const BYTE	FRAME_IO_SET_IO_LEVEL			= 0xCB;
static const BYTE	FRAME_IO_LOAD_CONFIG			= 0xCC;
static const BYTE	FRAME_IO_SAVE_CONFIG			= 0xCD;

static const BYTE	FRAME_IO_GET_INPUTFINTER		= 0xCE;
static const BYTE	FRAME_IO_SET_INPUTFINTER		= 0xCF;

static const BYTE	FRAME_IO_GET_DIRECTION			= 0x99;
static const BYTE	FRAME_IO_SET_DIRECTION			= 0x9A;

// Ezi-IO AD Functions
static const BYTE	FRAME_AD_GET_CONFIG				= 0x5A;
static const BYTE	FRAME_AD_SET_CONFIG				= 0x5B;

static const BYTE	FRAME_AD_READ_ONE				= 0x5C;
static const BYTE	FRAME_AD_READ_EIGHT				= 0x5D;

static const BYTE	FRAME_GET_AD_RESULT				= 0x6E;
static const BYTE	FRAME_SET_AD_RANGE				= 0x6F;

// Ezi-IO DA Functions
static const BYTE	FRAME_DA_SET_CONFIG				= 0xA0;
static const BYTE	FRAME_DA_GET_CONFIG				= 0xA1;

static const BYTE	FRAME_DA_SET_VALUE				= 0xA2;
static const BYTE	FRAME_DA_GET_VALUE				= 0xA3;

// Ezi-IO Counter Functions
static const BYTE	FRAME_CNT_SET_TRIGGER			= 0x27;		// Same with FRAME_FAS_TRIGGER_OUTPUT
static const BYTE	FRAME_CNT_GET_STATUS			= 0x40;		// Same with FRAME_FAS_GETAXISSTATUS

static const BYTE	FRAME_CNT_SET_CONFIG			= 0xA0;		// Same with FRAME_DA_SET_CONFIG
static const BYTE	FRAME_CNT_GET_CONFIG			= 0xA1;		// Same with FRAME_DA_GET_CONFIG
static const BYTE	FRAME_CNT_COMMAND				= 0xA4;
static const BYTE	FRAME_CNT_GET_VALUE				= 0xA5;
