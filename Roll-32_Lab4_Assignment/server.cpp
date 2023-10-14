// // #pragma comment(lib, "Ws2_32.lib")
// // // STD console header files
// // #include <sdkddkver.h>
// // #include <conio.h>
// // #include <stdio.h>

// // //SOCKET header files
// // #include <WinSock2.h>
// // #include <Windows.h>
// // #include <iostream>
// // #define SCK_VERSION2 0x0202 // Winsock version 2 is defined

// // using namespace std;

// // int main()
// // {
// //     // main locals
// //     long SUCCESSFUL;
// //     WSAData WinSockData;
// //     WORD DLLVERSION;

// //     DLLVERSION = MAKEWORD(2, 1); // macro to create WORD value by concatenating its arguments

// //     // Start Winsock DLL
// //     SUCCESSFUL = WSAStartup(DLLVERSION, &WinSockData);

// //     // Create Socket Structure
// //     SOCKADDR_IN ADDRESS;
// //     int AddressSize = sizeof(ADDRESS);

// //     // Create Sockets
// //     SOCKET sock_LISTEN;
// //     SOCKET sock_CONNECTION;

// //     // socket Arguments: AF_INET = internet domain (not Unix domain),
// //     // SOCK_STREAM= connection oriented TCP (not SOCK_DGRAM)
// //     sock_CONNECTION = socket(AF_INET, SOCK_STREAM, NULL);
// //     ADDRESS.sin_addr.s_addr = inet_addr("127.0.0.1"); // set IP
// //     ADDRESS.sin_family = AF_INET;
// //     ADDRESS.sin_port = htons(444); // port

// //     sock_LISTEN = socket(AF_INET, SOCK_STREAM, NULL);
// //     bind(sock_LISTEN, (SOCKADDR *)&ADDRESS, sizeof(ADDRESS));
// //     listen(sock_LISTEN, SOMAXCONN); // listen without limits

// //     // if connection found
// //     for (;;)
// //     {
// //         cout << "\n\tSERVER: Waiting for incoming connection....";
// //         if (sock_CONNECTION = accept(sock_LISTEN, (SOCKADDR *)&ADDRESS, &AddressSize))
// //         {
// //             cout << "\n\t connection was found!" << endl;
// //             SUCCESSFUL = send(sock_CONNECTION, "Welcome! You have connected to the server.", 46, NULL);
// //         }
// //     }
// //     return 1;
// // }

// // // #include <stdio.h>
// // // #include <conio.h>
// // // #include <winsock2.h>
// // // #pragma comment(lib, "ws2_32.lib") //Winsock Library

// // // int main(int argc, char *argv[])
// // // {
// // //     WSADATA wsa;
// // //     SOCKET s;
// // //     struct sockaddr_in server;
// // //     char c = 0;

// // //     printf("\nInitialising Winsock...");
// // //     if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
// // //     {
// // //         printf("Failed. Error Code : %d.\nPress a key to exit...", WSAGetLastError());
// // //         c = getch();
// // //         return 1;
// // //     }

// // //     printf("Initialised.\n");

// // //     //Create a socket
// // //     if ((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
// // //     {
// // //         printf("Could not create socket : %d.\n", WSAGetLastError());
// // //         WSACleanup();
// // //         c = getch();
// // //         return 1;
// // //     }
// // //     printf("Socket created. Connecting...\n");
// // //     memset(&server, 0, sizeof server);
// // //     server.sin_addr.s_addr = inet_addr("74.125.224.72");
// // //     server.sin_family = AF_INET;
// // //     server.sin_port = htons(80);

// // //     //Connect to remote server
// // //     if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
// // //     {
// // //         printf("Connect error:%d.\nPress a key to exit...", WSAGetLastError());
// // //         closesocket(s);
// // //         WSACleanup();
// // //         c = getch();
// // //         return 1;
// // //     }
// // //     puts("Connected.\nPress a key to exit...");
// // //     closesocket(s);
// // //     WSACleanup();
// // //     c = getch();
// // //     return 0;
// // // }

// #include <stdio.h>
// #include <conio.h>
// #include <winsock2.h>
// #pragma comment(lib, "ws2_32.lib") //Winsock Library

// int main(int argc, char *argv[])
// {
//     WSADATA wsa;
//     SOCKET s;
//     struct sockaddr_in server;
//     char c = 0;

//     printf("\nInitialising Winsock...");
//     if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
//     {
//         printf("Failed. Error Code : %d.\nPress a key to exit...", WSAGetLastError());
//         c = getch();
//         return 1;
//     }

//     printf("Initialised.\n");

//     //Create a socket
//     if ((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
//     {
//         printf("Could not create socket : %d.\n", WSAGetLastError());
//         WSACleanup();
//         c = getch();
//         return 1;
//     }
//     printf("Socket created. Connecting...\n");
//     memset(&server, 0, sizeof server);
//     server.sin_addr.s_addr = inet_addr("74.125.224.72");
//     server.sin_family = AF_INET;
//     server.sin_port = htons(80);

//     //Connect to remote server
//     if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
//     {
//         printf("Connect error:%d.\nPress a key to exit...", WSAGetLastError());
//         closesocket(s);
//         WSACleanup();
//         c = getch();
//         return 1;
//     }
//     puts("Connected.\nPress a key to exit...");
//     closesocket(s);
//     WSACleanup();
//     c = getch();
//     return 0;
// }

#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
    string ipAddress = "127.0.0.1"; // IP Address of the server
    int port = 54000;               // Listening port # on the server

    // Initialize WinSock
    WSAData data;
    WORD ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &data);
    if (wsResult != 0)
    {
        cerr << "Can't start Winsock, Err #" << wsResult << endl;
        return 0;
    }

    // Create socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }

    // Fill in a hint structure
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    //inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
    hint.sin_addr.S_un.S_addr = INADDR_ANY;

    // Connect to server
    int connResult = connect(sock, (sockaddr *)&hint, sizeof(hint));
    if (connResult == SOCKET_ERROR)
    {
        cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
        closesocket(sock);
        WSACleanup();
        return 0;
    }

    // Do-while loop to send and receive data
    char buf[4096];
    string userInput;

    do
    {
        // Prompt the user for some text
        cout << "> ";
        getline(cin, userInput);

        if (userInput.size() > 0) // Make sure the user has typed in something
        {
            // Send the text
            int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
            if (sendResult != SOCKET_ERROR)
            {
                // Wait for response
                ZeroMemory(buf, 4096);
                int bytesReceived = recv(sock, buf, 4096, 0);
                if (bytesReceived > 0)
                {
                    // Echo response to console
                    cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
                }
            }
        }

    } while (userInput.size() > 0);

    // Gracefully close down everything
    closesocket(sock);
    WSACleanup();
    return 0;
}
