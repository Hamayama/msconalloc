/*
 * msconalloc.h
 */

/* Prologue */
#ifndef GAUCHE_MSCONALLOC_H
#define GAUCHE_MSCONALLOC_H

#include <gauche.h>
#include <gauche/extend.h>


// MinGW-w64 のとき (動作未確認)
#if defined(__MINGW64_VERSION_MAJOR)
#include <winternl.h>
typedef struct _RTL_USER_PROCESS_PARAMETERS_1000 {
    ULONG           AllocationSize;
    ULONG           Size;
    ULONG           Flags;
    ULONG           DebugFlags;
    HANDLE          hConsole;
    ULONG           ProcessGroup;
    HANDLE          hStdInput;
    HANDLE          hStdOutput;
    HANDLE          hStdError;
    UNICODE_STRING  CurrentDirectoryName;
    HANDLE          CurrentDirectoryHandle;
    UNICODE_STRING  DllPath;
    UNICODE_STRING  ImagePathName;
    UNICODE_STRING  CommandLine;
    PWSTR           Environment;
    ULONG           dwX;
    ULONG           dwY;
    ULONG           dwXSize;
    ULONG           dwYSize;
    ULONG           dwXCountChars;
    ULONG           dwYCountChars;
    ULONG           dwFillAttribute;
    ULONG           dwFlags;
    ULONG           wShowWindow;
    UNICODE_STRING  WindowTitle;
    UNICODE_STRING  DesktopInfo;
    UNICODE_STRING  ShellInfo;
    UNICODE_STRING  RuntimeInfo;
} RTL_USER_PROCESS_PARAMETERS_1000, *PRTL_USER_PROCESS_PARAMETERS_1000;
// MinGW のとき
#else
typedef struct _PEB {
    BYTE  Reserved1[2];
    BYTE  BeingDebugged;
    BYTE  Reserved2[1];
    PVOID Reserved3[2];
    PVOID Ldr;
    PVOID ProcessParameters;
    BYTE  Reserved4[104];
    PVOID Reserved5[52];
    PVOID PostProcessInitRoutine;
    BYTE  Reserved6[128];
    PVOID Reserved7[1];
    ULONG SessionId;
} PEB, *PPEB;
#define PEXECUTION_STATE PEXECUTION_STATE_DUMMY // 重複定義対策
#include <ddk/ntapi.h>
#endif

// Windows7 64bit 対策
#ifndef STARTF_TITLEISLINKNAME
#define STARTF_TITLEISLINKNAME 0x00000800
#endif


SCM_DECL_BEGIN

/*
 * The following entry is a dummy one.
 * Replace it for your declarations.
 */

extern ScmObj test_msconalloc(void);
extern void free_console();
extern void alloc_console();
extern void alloc_and_hide_console();

/* Epilogue */
SCM_DECL_END

#endif  /* GAUCHE_MSCONALLOC_H */
