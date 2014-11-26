/*
 * msconalloc.c
 */

#include "msconalloc.h"

/*
 * The following function is a dummy one; replace it for
 * your C function definitions.
 */

ScmObj test_msconalloc(void)
{
    return SCM_MAKE_STR("msconalloc is working");
}


// コンソールの解放
void free_console() {
    FreeConsole();
}

// コンソールの割り当て
void alloc_console() {
    AllocConsole();
}

// コンソールの割り当てと非表示
void alloc_and_hide_console(int cmdshow) {
    HWND hConWnd   = NULL; // コンソールのウィンドウハンドル
    int  hideflag  = 0;    // 非表示フラグ

    // 現在のプロセスの情報を取得
    PROCESS_BASIC_INFORMATION pbinfo;
    NtQueryInformationProcess(GetCurrentProcess(), ProcessBasicInformation, &pbinfo, sizeof(pbinfo), NULL);
    PPEB ppeb = (PPEB)pbinfo.PebBaseAddress;
// MinGW-w64 のとき (動作未確認)
#if defined(__MINGW64_VERSION_MAJOR)
    PRTL_USER_PROCESS_PARAMETERS_1000 pparam = (PRTL_USER_PROCESS_PARAMETERS_1000)ppeb->ProcessParameters;
// MinGW のとき
#else
    PRTL_USER_PROCESS_PARAMETERS pparam = (PRTL_USER_PROCESS_PARAMETERS)ppeb->ProcessParameters;
#endif

    // ウィンドウの表示/非表示の情報を取得
    DWORD* pflags = (DWORD*)&(pparam->dwFlags);
    WORD*  pshow  = (WORD*)&(pparam->wShowWindow);

    // ウィンドウの表示/非表示の情報を保存
    DWORD tmp_flags = *pflags;
    WORD  tmp_show  = *pshow;

    // プロセスの起動情報を取得
    STARTUPINFO si;
    GetStartupInfo(&si);

    // プロセスの起動情報とウィンドウの表示/非表示の情報を照合して、
    // 一致していれば、ウィンドウを非表示に設定する
    if (si.dwFlags == tmp_flags && si.wShowWindow == tmp_show) {
        // Windows7 64bit 対策
        if (*pflags & STARTF_TITLEISLINKNAME) {
            *pflags &= ~STARTF_TITLEISLINKNAME;
        }
        // ウィンドウを非表示に設定する
        *pflags |= STARTF_USESHOWWINDOW;
        //*pshow  = SW_HIDE;
        *pshow  = cmdshow;
        hideflag = 1;
    }

    // コンソールの割り当て
    AllocConsole();

    // ウィンドウの表示/非表示の情報を復帰
    *pflags = tmp_flags;
    *pshow  = tmp_show;

    // ウィンドウが生成されるまで待つ
    while ((hConWnd = GetConsoleWindow()) == NULL) {
        Sleep(10);
    }

    // ウィンドウを非表示にできなかったとき
    if (!hideflag){
        // ウィンドウが表示されるまで待つ
        while (!IsWindowVisible(hConWnd)) {
            Sleep(10);
        }
        // ウィンドウが表示されたら非表示にする
        while (IsWindowVisible(hConWnd)) {
            //ShowWindow(hConWnd, SW_HIDE);
            ShowWindow(hConWnd, cmdshow);
            Sleep(10);
        }
    }
}


/*
 * Module initialization function.
 */
extern void Scm_Init_msconalloclib(ScmModule*);

void Scm_Init_msconalloc(void)
{
    ScmModule *mod;

    /* Register this DSO to Gauche */
    SCM_INIT_EXTENSION(msconalloc);

    /* Create the module if it doesn't exist yet. */
    mod = SCM_MODULE(SCM_FIND_MODULE("msconalloc", TRUE));

    /* Register stub-generated procedures */
    Scm_Init_msconalloclib(mod);
}
