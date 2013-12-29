#include <stdio.h>
#include <windows.h>
#include <winsock.h>



int main(int argc, char**argv){
const int iReqWinsockVer = 2;   // Minimum winsock version required

WSADATA wsaData;

if (WSAStartup(MAKEWORD(iReqWinsockVer,0), &wsaData)==0)
{
    // Check if major version is at least iReqWinsockVer
    if (LOBYTE(wsaData.wVersion) >= iReqWinsockVer)
    {
        printf("Launched\n");
    }
    else
    {
        printf("Required version not available");
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
