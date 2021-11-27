#ifndef HTTP_H
#define HTTP_H

#include "connection.h"

typedef struct HTTPCONNECTION {

	SZCONNECTION *szConnection;
	char *ip;
	int port;
	char *response;


} HTTPCONNECTION;

void szHttp_New(char *domain__ip, HTTPCONNECTION *http);
void szHttp_Instance(HTTPCONNECTION *handle);
void szHttp_MakePost(HTTPCONNECTION *handle, int action, char*data);

#endif HTTP_H