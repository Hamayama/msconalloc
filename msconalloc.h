/*
 * msconalloc.h
 */

/* Prologue */
#ifndef GAUCHE_MSCONALLOC_H
#define GAUCHE_MSCONALLOC_H

#include <gauche.h>
#include <gauche/extend.h>


// Windows 内部情報の
// PEB (Process Environment Block) 構造体と、
// RTL_USER_PROCESS_PARAMETERS 構造体を、
// _1000 を付加した別名にして使用する (重複定義対策)

// MinGW-w64 のとき
#if defined(__MINGW64_VERSION_MAJOR)
#include <winternl.h>
// PEB (Process Environment Block)
typedef struct _PEB PEB_1000, *PPEB_1000;
// RTL_USER_PROCESS_PARAMETERS
// (MinGW (32bit) の include/ddk/ntapi.h より)
typedef struct _RTL_USER_PROCESS_PARAMETERS_1000 {

    // (MSDN を参考に一部修正 (8バイト境界ならサイズは一致しそうだけど))
    //ULONG          AllocationSize;
    //ULONG          Size;
    //ULONG          Flags;
    //ULONG          DebugFlags;
    //HANDLE         hConsole;
    //ULONG          ProcessGroup;
    //HANDLE         hStdInput;
    //HANDLE         hStdOutput;
    //HANDLE         hStdError;
    //UNICODE_STRING CurrentDirectoryName;
    //HANDLE         CurrentDirectoryHandle;
    //UNICODE_STRING DllPath;
    //UNICODE_STRING ImagePathName;
    //UNICODE_STRING CommandLine;
    BYTE           Reserved1[16];
    PVOID          Reserved2[10];
    UNICODE_STRING ImagePathName;
    UNICODE_STRING CommandLine;

    PWSTR          Environment;
    ULONG          dwX;
    ULONG          dwY;
    ULONG          dwXSize;
    ULONG          dwYSize;
    ULONG          dwXCountChars;
    ULONG          dwYCountChars;
    ULONG          dwFillAttribute;
    ULONG          dwFlags;
    ULONG          wShowWindow;
    UNICODE_STRING WindowTitle;
    UNICODE_STRING DesktopInfo;
    UNICODE_STRING ShellInfo;
    UNICODE_STRING RuntimeInfo;
} RTL_USER_PROCESS_PARAMETERS_1000, *PRTL_USER_PROCESS_PARAMETERS_1000;
// MinGW (32bit) のとき
#else
#define PEXECUTION_STATE PEXECUTION_STATE_1000 // (重複定義対策)
#include <ddk/ntapi.h>
// PEB (Process Environment Block)
// (MSDN より (ポインタはPVOIDに変更))
typedef struct _PEB_1000 {
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
} PEB_1000, *PPEB_1000;
// RTL_USER_PROCESS_PARAMETERS
typedef struct _RTL_USER_PROCESS_PARAMETERS RTL_USER_PROCESS_PARAMETERS_1000, *PRTL_USER_PROCESS_PARAMETERS_1000;
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
extern void free_console(void);
extern void alloc_console(void);
extern void alloc_and_hide_console(int cmdshow);

/* Epilogue */
SCM_DECL_END

#endif  /* GAUCHE_MSCONALLOC_H */
