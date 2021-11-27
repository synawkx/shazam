#include "common.h"
#include <windows.h>


typedef struct SESSION_CONTEXT
{

    DWORD pid;
    char filename[MAX_PATH];
    char workDir[MAX_PATH];

} SESSION_CONTEXT;


SESSION_CONTEXT *session;
