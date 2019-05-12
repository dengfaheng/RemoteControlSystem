#include <stdio.h>
#include <winsock2.h>
#include <STDIO.H>

#include "CommonServer.h"
#include "MySocketServer.h"
#include "HostInfo.h"
#include "SystemCmd.h"
#pragma  comment(lib,"ws2_32.lib")

char revData[10240];
MSGINFO revMsgInfo;
MSGINFO sendMsgInfo;
SYSTEMINFO sendSysInfo;

CMySocketServer MySocket;
CHostInfo MyInfo;
CSystemCmd MyCmd;
