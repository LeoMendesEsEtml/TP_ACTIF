/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "Mc32DriverLcd.h"
#include "Mc32gest_SerComm.h"
#include "DefMenuGen.h"
#include "MenuGen.h"
#define SERVER_PORT 9760
IPV4_ADDR ipAddr;
bool saveRequested = false;
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
 */

APP_DATA appData;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

void APP_clearSaveRequested(void) {
    saveRequested = false;
}

bool APP_GetSaveRequested() {
    return saveRequested;
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

bool GetTcpState(void) {
    return appData.tcpState;
}

const char* APP_GetIPStringFormatted(void) {
    IPV4_ADDR ipAddr;
    static char ipStr[20]; // buffer local mais static (pour retour par pointeur)
    ipAddr.Val = TCPIP_STACK_NetAddress(TCPIP_STACK_IndexToNet(0));
    sprintf(ipStr, "%d.%d.%d.%d", ipAddr.v[0], ipAddr.v[1], ipAddr.v[2], ipAddr.v[3]);
    return ipStr;
}
// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize(void) {
    /* Place the App state machine in its initial state. */
    appData.state = APP_TCPIP_WAIT_INIT;
    DRV_TMR0_Start();
    DRV_TMR1_Start();
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks(void) {
    SYS_STATUS tcpipStat;
    const char *netName, *netBiosName;
    static IPV4_ADDR dwLastIP[2] = {
        {-1},
        {-1}
    };

    int i, nNets;
    TCPIP_NET_HANDLE netH;

    SYS_CMD_READY_TO_READ();
    switch (appData.state) {
        case APP_TCPIP_WAIT_INIT:
            tcpipStat = TCPIP_STACK_Status(sysObj.tcpip);
            if (tcpipStat < 0) { // some error occurred
                SYS_CONSOLE_MESSAGE(" APP: TCP/IP stack initialization failed!\r\n");
                appData.state = APP_TCPIP_ERROR;
            } else if (tcpipStat == SYS_STATUS_READY) {
                // now that the stack is ready we can check the
                // available interfaces
                nNets = TCPIP_STACK_NumberOfNetworksGet();
                for (i = 0; i < nNets; i++) {

                    netH = TCPIP_STACK_IndexToNet(i);
                    netName = TCPIP_STACK_NetNameGet(netH);
                    netBiosName = TCPIP_STACK_NetBIOSName(netH);

#if defined(TCPIP_STACK_USE_NBNS)
                    SYS_CONSOLE_PRINT("    Interface %s on host %s - NBNS enabled\r\n", netName, netBiosName);
#else
                    SYS_CONSOLE_PRINT("    Interface %s on host %s - NBNS disabled\r\n", netName, netBiosName);
#endif  // defined(TCPIP_STACK_USE_NBNS)

                }
                appData.state = APP_TCPIP_WAIT_FOR_IP;

            }
            break;

        case APP_TCPIP_WAIT_FOR_IP:

            nNets = TCPIP_STACK_NumberOfNetworksGet();

            for (i = 0; i < nNets; i++) {
                netH = TCPIP_STACK_IndexToNet(i);
                if (!TCPIP_STACK_NetIsReady(netH)) {
                    return; // interface not ready yet!
                }

                ipAddr.Val = TCPIP_STACK_NetAddress(netH);
                if (dwLastIP[i].Val != ipAddr.Val) {
                    dwLastIP[i].Val = ipAddr.Val;

                    SYS_CONSOLE_MESSAGE(TCPIP_STACK_NetNameGet(netH));
                    SYS_CONSOLE_MESSAGE(" IP Address: ");
                    SYS_CONSOLE_PRINT("%d.%d.%d.%d \r\n",
                            ipAddr.v[0], ipAddr.v[1], ipAddr.v[2], ipAddr.v[3]);

                    // Envoie � MenuGen pour affichage temporaire pendant 5 s
                    char ipBuf[20];
                    sprintf(ipBuf, "%d.%d.%d.%d", ipAddr.v[0], ipAddr.v[1], ipAddr.v[2], ipAddr.v[3]);
                    MENU_RequestIpDisplay(ipBuf);
                }

                appData.state = APP_TCPIP_OPENING_SERVER;
            }
            break;

        case APP_TCPIP_OPENING_SERVER:
        {
            SYS_CONSOLE_PRINT("Waiting for Client Connection on port: %d\r\n", SERVER_PORT);
            appData.socket = TCPIP_TCP_ServerOpen(IP_ADDRESS_TYPE_IPV4, SERVER_PORT, 0);
            if (appData.socket == INVALID_SOCKET) {
                SYS_CONSOLE_MESSAGE("Couldn't open server socket\r\n");
                break;
            }
            //SCA set keepalive
            // N�cessaire si on veut que TCPIP_TCP_IsConnected() d�tecte d�connexion du c�ble
            appData.keepAlive.keepAliveEnable = true;
            appData.keepAlive.keepAliveTmo = 1000;
            //[ms] / 0 => valeur par d�faut
            appData.keepAlive.keepAliveUnackLim = 2;
            //[nb de tentatives] / 0 => valeur par d�faut
            TCPIP_TCP_OptionsSet(appData.socket, TCP_OPTION_KEEP_ALIVE, &(appData.keepAlive));
            appData.state = APP_TCPIP_WAIT_FOR_CONNECTION;
        }
            break;

        case APP_TCPIP_WAIT_FOR_CONNECTION:
        {
            if (!TCPIP_TCP_IsConnected(appData.socket)) {
                return;
            } else {
                // We got a connection
                appData.state = APP_TCPIP_SERVING_CONNECTION;
                appData.tcpState = true;
                SYS_CONSOLE_MESSAGE("Received a connection\r\n");
            }
        }
            break;

        case APP_TCPIP_SERVING_CONNECTION:
        {
            // Tampons
            static uint8_t TCPRxBuffer[64]; // tampon r�ception (non sign� pour API TCP)
            static uint8_t TCPTxBuffer[64]; // tampon �mission

            // R�cup�re le pointeur vers la structure contenant les param�tres distants
            S_ParamGen* RemoteParamGen = APP_GEN_GetRemoteParam();

            if (!TCPIP_TCP_IsConnected(appData.socket)) {
                appData.state = APP_TCPIP_CLOSING_CONNECTION;
                SYS_CONSOLE_MESSAGE("Connection closed\r\n");
                break;
            }

            // V�rifie qu'il y a des donn�es � lire
            int16_t rxCount = TCPIP_TCP_GetIsReady(appData.socket);
            if (rxCount <= 0) {
                break;
            }

            // S�curise la taille lue
            if (rxCount > sizeof (TCPRxBuffer) - 1) {
                rxCount = sizeof (TCPRxBuffer) - 1;
            }

            // Lire la trame TCP dans le tampon de r�ception
            TCPIP_TCP_ArrayGet(appData.socket, TCPRxBuffer, rxCount);
            TCPRxBuffer[rxCount] = '\0'; // Terminaison
            // Traitement de la trame via GetMessage
            if (GetMessage((int8_t *) TCPRxBuffer, RemoteParamGen, &saveRequested)) {
                SendMessage((int8_t *) TCPTxBuffer, RemoteParamGen, saveRequested);
                TCPIP_TCP_ArrayPut(appData.socket, TCPTxBuffer, strlen((char *) TCPTxBuffer));
            } else {
                // Trame invalide ? renvoyer erreur
                const char *err = "!E=BAD#";
                TCPIP_TCP_ArrayPut(appData.socket, (const uint8_t *) err, strlen(err));
            }

            break;
        }


            break;
        case APP_TCPIP_CLOSING_CONNECTION:
        {
            // Close the socket connection.
            TCPIP_TCP_Close(appData.socket);
            appData.tcpState = false;
            appData.socket = INVALID_SOCKET;
            appData.state = APP_TCPIP_WAIT_FOR_IP;

        }
            break;
        default:
            break;
    }
}



/*******************************************************************************
 End of File
 */

