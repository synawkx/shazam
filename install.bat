@echo off
set CC=CL.exe
set CLINK=link.exe

set ENTRY_FILE=src/shazam.c
set DEPS=src/lib/*.c
set RELEASE_NAME=shazam
set SUBSYSTEM=windows
set COMMON_LIB=ws2_32.lib
set MACHINE=X86
set PROGRAM_FILES=%programfiles(x86)%

Rem clean all
echo [-] Clean data
DEL /F/Q/S "Release" > shazam.log


Rem ;;highestAvailable <- si solicita admin
set LEVEL=asInvoker

mkdir Release 2> NUL
echo [*] Folder Release created.

echo [*] Set Variables
set VISUAL_STUDIO=%PROGRAM_FILES%\Microsoft Visual Studio

if exist "%VISUAL_STUDIO%" (
    echo [*] Found Visual Studio!! 
    echo [*] VSPath : "%VISUAL_STUDIO%"
) else (
    echo [*] Not Found Visual Studio!! 
    set /p VISUAL_STUDIO="[>] Enter Microsoft Visual Studio Path: "
)
echo [!] Building... > shazam.log

set ENV=RELEASE

@call "%VISUAL_STUDIO%\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" %MACHINE% %*

echo [*] Compiling

%CC% /c /Zi /nologo /I src/ /I src/lib/includes /W3 /WX- /diagnostics:column /sdl /O2 /Oi /Oy- /D WIN32 /D %ENV% ^
	/D _CONSOLE /DDEBUG=1 /DAPPNAME=\"wps\" /DRELEASE_NAME=\"%RELEASE_NAME%\" /D _MBCS /D _MBCS /Gm- /EHsc /MT /GS /Gy /fp:precise /permissive- ^
    /Zc:wchar_t /Zc:forScope /Zc:inline /Fo"Release\\" /Fd"Release\%RELEASE_NAME%.pdb" /Gd /TC /analyze- ^
    /FC /errorReport:prompt /D _CRT_SECURE_NO_DEPRECATE   %ENTRY_FILE% %DEPS%  /D _WINSOCK_DEPRECATED_NO_WARNINGS

if exist "Release\%RELEASE_NAME%.obj" (
    echo [*] Compilation success!!
) else (
    echo [*] Compilation Failed!!
    Exit /B 5
)

echo [-] Linking

%CLINK% /ERRORREPORT:PROMPT /OUT:"Release\%RELEASE_NAME%.exe"  /subsystem:%SUBSYSTEM% /INCREMENTAL:NO /NOLOGO ^
    kernel32.lib user32.lib gdi32.lib %COMMON_LIB% winspool.lib comdlg32.lib advapi32.lib shell32.lib ^
    ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /MANIFEST /MANIFESTUAC:"level='%LEVEL%' uiAccess='false'" ^
    /manifest:embed /DEBUG:NONE   /PDB:"Release\%RELEASE_NAME%.pdb"  ^
    /DYNAMICBASE:NO /NXCOMPAT:NO /IMPLIB:"Release\%RELEASE_NAME%.lib" /MACHINE:%MACHINE% ^
     Release\*.obj

echo [-] Checking...
if exist "Release\%RELEASE_NAME%.exe" (
    echo [*] Success!!
    echo [*] Success!! time >> shazam.log
) else (
    echo [!] Failed!!
    echo [!] Failed!! > shazam.log
)
