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

    // 現在のプロセスの情報を取得する
    PROCESS_BASIC_INFORMATION pbinfo;
    NTSTATUS status = NtQueryInformationProcess(GetCurrentProcess(), ProcessBasicInformation, &pbinfo, sizeof(pbinfo), NULL);

    // 取得できたとき
    if (NT_SUCCESS(status) && pbinfo.PebBaseAddress != NULL) {
        // 現在のプロセスの詳細情報を取得
        PPEB_1000 ppeb = (PPEB_1000)pbinfo.PebBaseAddress;
        PRTL_USER_PROCESS_PARAMETERS_1000 pparam = (PRTL_USER_PROCESS_PARAMETERS_1000)ppeb->ProcessParameters;

        // ウィンドウの表示/非表示の情報を取得
        DWORD* pflags = (DWORD*)&(pparam->dwFlags);
        WORD*  pshow  = (WORD*)&(pparam->wShowWindow);

        // プロセスの起動情報を取得
        STARTUPINFO si;
        GetStartupInfo(&si);

        // プロセスの起動情報とウィンドウの表示/非表示の情報を照合して、
        // 一致していれば、ウィンドウを非表示に設定する
        if (si.dwFlags == *pflags && si.wShowWindow == *pshow) {
            // ウィンドウの表示/非表示の情報を保存する
            DWORD tmp_flags = *pflags;
            WORD  tmp_show  = *pshow;

            // Windows7 64bit 対策
            if (*pflags & STARTF_TITLEISLINKNAME) {
                *pflags &= ~STARTF_TITLEISLINKNAME;
            }

            // ウィンドウを非表示に設定する
            *pflags |= STARTF_USESHOWWINDOW;
            //*pshow  = SW_HIDE;
            *pshow  = cmdshow;

            // コンソールの割り当て
            AllocConsole();

            // ウィンドウの表示/非表示の情報を元に戻す
            *pflags = tmp_flags;
            *pshow  = tmp_show;

            // 抜ける
            return;
        }
    }

    // 以下は、上記方法が使えなかった場合の処理となる
    // (一瞬ちらつきが発生する)

    // コンソールの割り当て
    int allocflag = AllocConsole();

    // 割り当てできたとき
    if (allocflag) {
        int count = 0;        // カウンタ
        int max_count = 1200; // カウンタ最大値
                              //   (1200 * 50 = 60000msec であきらめる)
        HWND hConWnd = NULL;  // コンソールのウィンドウハンドル

        // ウィンドウが生成されるまで待つ
        while (count++ < max_count) {
            if ((hConWnd = GetConsoleWindow()) != NULL) { break; }
            Sleep(50);
        }
        // 生成されたとき
        if (hConWnd != NULL) {
            // ウィンドウが表示されるまで待つ
            while (count++ < max_count) {
                if (IsWindowVisible(hConWnd)) { break; }
                Sleep(50);
            }
            // ウィンドウを非表示にする
            //ShowWindow(hConWnd, SW_HIDE);
            ShowWindow(hConWnd, cmdshow);
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
