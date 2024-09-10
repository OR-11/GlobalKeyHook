/*
* https://tm-b.hatenablog.com/entry/2023/02/23/%E3%80%90C%23%E3%80%91%E5%B7%A6CapsLock%E3%82%92%E7%84%A1%E5%8A%B9%E3%81%AB%E3%81%97%E3%81%A6%E5%B7%A6Ctrl%E3%82%AD%E3%83%BC%E3%81%AB%E5%81%BD%E8%A3%85%E3%81%97%E3%81%A6%E3%81%BF%E3%81%9F
    C#のコードをChatGPTに投げていらないところを消したら動いた！奇跡！
*/

#include <windows.h>
#include <iostream>
#include <vector>
#include<fstream>

using namespace std;

//struct KBDLLHOOKSTRUCT {
//    DWORD vkCode;
//    DWORD scanCode;
//    DWORD flags;
//    DWORD time;
//    ULONG_PTR dwExtraInfo;
//};

//struct KEYBDINPUT {
//    WORD wVk;
//    WORD wScan;
//    DWORD dwFlags;
//    DWORD time;
//    ULONG_PTR dwExtraInfo;
//    int dummy1;
//    int dummy2;
//};

//struct INPUT {
//    DWORD type;
//    KEYBDINPUT ki;
//};

HHOOK sHookId = NULL;
bool sHoldCtrl = false;

//const int WH_KEYBOARD_LL = 13;
//const WPARAM WM_KEYDOWN = 0x0100;
//const WPARAM WM_KEYUP = 0x0101;
//const WPARAM WM_SYSKEYDOWN = 0x0104;
//const WPARAM WM_SYSKEYUP = 0x0105;

//std::vector<INPUT> CTRL_D = { {1, {162, 0, 0, 0, 0, 0, 0}} };
//std::vector<INPUT> CTRL_U = { {1, {162, 0, 2, 0, 0, 0, 0}} };

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode < 0) {
        return CallNextHookEx(sHookId, nCode, wParam, lParam);
    }

    if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        KBDLLHOOKSTRUCT* kb = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        DWORD vkCode = kb->vkCode;
        if (vkCode == 115) {//F4
            //SendInput(static_cast<UINT>(CTRL_D.size()), CTRL_D.data(), sizeof(INPUT));
            sHoldCtrl = true;
            ofstream outputfile("F4.ysfjk");
            outputfile << "";
            outputfile.close();
            return TRUE;
        }
        else if (vkCode == 91 || vkCode == 92) {//Windowsキー
            if (sHoldCtrl) {
                //SendInput(static_cast<UINT>(CTRL_U.size()), CTRL_U.data(), sizeof(INPUT));
            }
            return TRUE;
        }
        else if (vkCode == 240 || vkCode == 242) {//CapsLockキー
            if (sHoldCtrl) {
                //SendInput(static_cast<UINT>(CTRL_U.size()), CTRL_U.data(), sizeof(INPUT));
            }
            return TRUE;
        }
        else if (vkCode == 164 || vkCode == 165) {//Alt
            ofstream outputfile("Alt.ysfjk");
            outputfile << "";
            outputfile.close();
            if (sHoldCtrl) {
                //SendInput(static_cast<UINT>(CTRL_U.size()), CTRL_U.data(), sizeof(INPUT));
            }
        }
    }
    else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
        KBDLLHOOKSTRUCT* kb = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        DWORD vkCode = kb->vkCode;
        if (vkCode == 115 || vkCode == 91 || vkCode == 92 || vkCode == 240 || vkCode == 242) {
            if (vkCode == 115) remove("F4.ysfjk");
            if (sHoldCtrl) {
                //SendInput(static_cast<UINT>(CTRL_U.size()), CTRL_U.data(), sizeof(INPUT));
            }
            return TRUE;
        }
        else if (vkCode == 164 || vkCode == 165) {//Alt
            remove("Alt.ysfjk");
            sHoldCtrl = false;
        }
    }
    return CallNextHookEx(sHookId, nCode, wParam, lParam);
}

void Start() {
    if (sHookId != NULL)
        return;

    HMODULE hMod = GetModuleHandle(NULL);
    sHookId = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, hMod, 0);
}

void Stop() {
    if (sHookId != NULL) {
        UnhookWindowsHookEx(sHookId);
        sHookId = NULL;
        if (sHoldCtrl) {
            //SendInput(static_cast<UINT>(CTRL_U.size()), CTRL_U.data(), sizeof(INPUT));
        }
    }
}
//
//int main() {
//    Start();
//    MSG msg;
//    while (GetMessage(&msg, NULL, 0, 0)) {
//        TranslateMessage(&msg);
//        DispatchMessage(&msg);
//    }
//    Stop();
//    return 0;
//}
