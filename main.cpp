#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <Windows.h>
#include <Shlwapi.h>

BOOL IsUserAnAdmin() {
    BOOL bAdmin = FALSE;
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    PSID AdministratorsGroup = NULL;

    if (AllocateAndInitializeSid(&NtAuthority, 2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0,
        &AdministratorsGroup)) {
        if (!CheckTokenMembership(NULL, AdministratorsGroup, &bAdmin)) {
            bAdmin = FALSE;
        }

        FreeSid(AdministratorsGroup);
    }

    return bAdmin;
}

int main(int argc, char *argv[])
{
    if (!IsUserAnAdmin()) {
        // 获取当前可执行文件的路径
        wchar_t szPath[MAX_PATH];
        GetModuleFileNameW(NULL, szPath, MAX_PATH);

        // 提升权限重新运行当前可执行文件
        if (ShellExecuteW(NULL, L"runas", szPath, NULL, NULL, SW_SHOWNORMAL) <= (HINSTANCE)32) {
            std::cout << "Error: Failed to elevate permissions." << std::endl;
            return 1;
        }
        ExitProcess(0);
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
