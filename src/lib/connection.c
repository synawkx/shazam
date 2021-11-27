#include "connection.h"

/*!
 * @function	init_conn
 * @abstract 	Starts new connection objects.
 * @param		szSocket	Pointer to SZSOCKET.
*/
void init_conn(SZSOCKET **szSocket){

    *szSocket = (SZSOCKET *)malloc(sizeof(SZSOCKET));

    //here all the modules
    HMODULE ws2 = c_ws32();
 	_WSAStartup pWSAStartup = (_WSAStartup)c_gProc(ws2, "WSAStartup");
	WSADATA wsaData;
	pWSAStartup((WORD)2.2, &wsaData);

    (*szSocket)->pWSASocketA = (_WSASocketA)c_gProc(ws2, "WSASocketA");
    (*szSocket)->pClosesocket = (_closesocket)c_gProc(ws2, "closesocket");
    (*szSocket)->pConnect = (_connect)c_gProc(ws2, "connect");
    (*szSocket)->pWSACleanup = (_WSACleanup)c_gProc(ws2, "WSACleanup");
    (*szSocket)->send= (_send)c_gProc(ws2, "send");
    (*szSocket)->recv = (_recv)c_gProc(ws2, "recv");

    //just checking 
    (*szSocket)->hash = malloc(21);
    memcpy((*szSocket)->hash,"justcheckavailability", 21);

}

/*!
 * @function	SzCreateConnection
 * @abstract 	Creates socket object
 * @param		connection	Pointer to SZCONNECTION
*/
void SzCreateConnection(SZCONNECTION **connection){

	struct sockaddr_in sa;
	sa.sin_family = AF_INET;

	SOCKET sock = (*connection)->szSocket->pWSASocketA(AF_INET, SOCK_STREAM, 6, NULL, 0, 0);
	(*connection)->szSocket->socket = sock;
    sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = mc_iaddr((*connection)->ip);
	sa.sin_port = mc_htons((*connection)->port);

	if ((*connection)->szSocket->pConnect(sock, (SOCKADDR*)&sa, sizeof(sa)) == SOCKET_ERROR)
    {
    	(*connection)->szSocket->pWSACleanup();
		fdebug("[ERROR]: %s:%d", (*connection)->ip, (*connection)->port);
    }
}