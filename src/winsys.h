#include <windows.h>

typedef NTSTATUS (__stdcall  * _RtlIpv4StringToAddressA)(
  PCSTR   S,
  BOOLEAN Strict,
  PCSTR   *Terminator,
  struct in_addr *Addr
);


typedef DWORD (WINAPI *_WSAStartup)(
  WORD      wVersionRequired,
  LPWSADATA lpWSAData
);

typedef SOCKET (WINAPI *_WSASocketA)(
  int                 af,
  int                 type,
  int                 protocol,
  LPWSAPROTOCOL_INFOA lpProtocolInfo,
  GROUP               g,
  DWORD               dwFlags
);

typedef DWORD (WINAPI *_send)(
  SOCKET     s,
  const char *buf,
  int        len,
  int        flags
);
typedef DWORD (WINAPI *_recv)(
  SOCKET     s,
  const char *buf,
  int        len,
  int        flags
);

typedef u_short (WINAPI *_htons)(
  u_short port
);

typedef struct pSocket {
    SOCKET s;
    _send send;
    _recv recv;
} PSOCKET;

typedef unsigned long (WINAPI *_inet_addr)(
  const char *cp
);
typedef DWORD (WINAPI *_closesocket)(
  SOCKET s
);
typedef DWORD (WINAPI *_connect)(
  SOCKET         s,
  struct sockaddr *name,
  int            namelen
);
typedef DWORD (WINAPI *_WSACleanup)();