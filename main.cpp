#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <Windows.h>
#include <Shlwapi.h>
#include <qtextcodec.h>
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
    // 设置编码格式，在main()方法中
    QTextCodec* codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
    if (!IsUserAnAdmin()) {
        // ??è?μ±?°?é?′DD???tμ??·??
        wchar_t szPath[MAX_PATH];
        GetModuleFileNameW(NULL, szPath, MAX_PATH);

        // ìáéyè¨?T??D???DDμ±?°?é?′DD???t
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
