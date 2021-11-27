#ifndef COMMON_H
#define COMMON_H

#include<stdio.h>
#include <winsock2.h>
#include "winsys.h"

#define SZAC_SEND 0xa

//socket objects
typedef struct SZSOCKET {
	char *hash;
	SOCKET socket;
	_WSAStartup pWSAStartup;
	_WSASocketA pWSASocketA;
	_htons pHtons;
	_inet_addr pInet_addr;
	_closesocket pClosesocket;
	_connect pConnect;
	_WSACleanup pWSACleanup;
	_send send;
	_recv recv; 
} SZSOCKET;

typedef struct SZCONNECTION{
	int instanced;
	char *ip;
	int port;

	SZSOCKET *szSocket;
} SZCONNECTION;


SZSOCKET *szSocket;

HMODULE ntWrapper;

inline HMODULE readNtdll(){
  return LoadLibrary("ntdll");
};


inline FARPROC ntFunction(char *name){
  return GetProcAddress(ntWrapper, name);
};


HMODULE c_ws32();
FARPROC c_gProc(HMODULE lib, char *name);


void fdebug(const char *szFormat, ...);

#endif