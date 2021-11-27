#include "common.h"


HMODULE c_ws32(){
    char *ws2_text = "WS2_32.dll";
 	return LoadLibrary(ws2_text); 
}

FARPROC c_gProc(HMODULE lib, char *name){
	return GetProcAddress(lib, name);
}

    //defino una función para poder hacer logs
#ifdef DEBUG
void fdebug(const char *szFormat, ...)
{
    if (!szFormat)
        return;
    va_list va_alist;
    char formatbuf[8192];
    va_start(va_alist, szFormat);
    vsnprintf(formatbuf, sizeof(formatbuf), szFormat, va_alist);
    va_end(va_alist);
    FILE *fp = fopen("shazam.log", "a");
    if (!fp)
        return;
    fprintf(fp, "[LOG] - %s\n", formatbuf);
    fclose(fp);
}
#else // DEBUG
void fdebug(const char *szFormat, ...){};
#endif // DEBUG