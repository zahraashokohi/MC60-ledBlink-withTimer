#include "custom_feature_def.h"
#include "ql_type.h"
#include "ql_stdlib.h"
#include "ql_uart.h"
#include "ril.h"
#include <stdint.h>
#include <stddef.h>

#include "ql_timer.h"
#include "patternBlink.h"

#define    LED_Timer_Id                       TIMER_ID_USER_START+29
#define    LED_Timer_Peride                   100// 5 * 60000
#define  LED_GREEN      PINNAME_GPIO3
#define  LED_BLUE       PINNAME_GPIO1
#define  LED_RED        PINNAME_NETLIGHT
Pattern_t pattern_200_1000;
Pattern_t pattern_200_400;

char DBG_BUFFER[256];
#define DBG_PORT UART_PORT1
#define DBG(FORMAT, ...)                                                  \
    {                                                                     \
        Ql_memset(DBG_BUFFER, 0, sizeof(DBG_BUFFER));                     \
        Ql_sprintf(DBG_BUFFER, FORMAT, ##__VA_ARGS__);                    \
        Ql_UART_Write(DBG_PORT, (u8 *)DBG_BUFFER, Ql_strlen(DBG_BUFFER)); \
    }

void uart_callback(Enum_SerialPort port, Enum_UARTEventType msg, bool level, void *customizedPara) {}
void blinkTimerCallback (u32 timerId);
void proc_main_task(s32 taskId)
{
    s32 ret;
    ST_MSG msg;
    Ql_UART_Register(DBG_PORT, uart_callback, NULL);
    Ql_UART_Open(DBG_PORT, 9600, FC_NONE);
    Init_Pattern(&pattern_200_1000, Pttern_Enable, 1);
    Set_Pattern(&pattern_200_1000, 0, 10);
    Init_Pattern(&pattern_200_400, Pttern_Enable, 1);
    Set_Pattern(&pattern_200_400, 9, 1);
    Ql_Timer_Register(LED_Timer_Id, blinkTimerCallback, NULL);
    Ql_Timer_Start(LED_Timer_Id, LED_Timer_Peride, TRUE);
    Ql_GPIO_Init(LED_RED, PINDIRECTION_OUT, PINLEVEL_LOW, PINPULLSEL_PULLUP);
    Ql_GPIO_SetLevel(LED_RED, PINLEVEL_LOW);
    DBG("BEGIN\n");
    while (1)
    {
        Ql_OS_GetMessage(&msg);
        switch (msg.message)
        {
        case MSG_ID_RIL_READY:
            Ql_RIL_Initialize();
            DBG("Ril Ready\n");
            break;
        }
    }
}

void blinkTimerCallback (u32 timerId)
{
    if(timerId == LED_Timer_Id)
    {
       // APP_DEBUG("LED_Timer_Id \r\n");
       // APP_DEBUG( "\r\n\r\n******variable.system.ledTimerCnt = %d ******************\r\n\r\n", variable.system.ledTimerCnt);
       /* if(variable.system.ledTimer == ACTIVE_ACTION)
        {
            if(variable.tcp1.m_tcp_state > 6 && variable.tcp1.m_tcp_state <13)
            {
                variable.system.ledTimerOn = 20;
                variable.system.ledTimerOff = 180;
                Ql_GPIO_SetLevel(LED_BLUE, Pattern_Process(&pattern_200_1000, 1, ALWAYS_ACTIVE));
            }
            else if (variable.tcp1.m_tcp_state > 12 && variable.tcp1.m_tcp_state < 16)
            {
                variable.system.ledTimerOn = 50;
                variable.system.ledTimerOff = 150;
                Ql_GPIO_SetLevel(LED_BLUE, Pattern_Process(&pattern_200_1000, 1, ALWAYS_ACTIVE));
            }
            else{
                variable.system.ledTimerOn = 0;
                variable.system.ledTimerOff = 200;
                Ql_GPIO_SetLevel(LED_BLUE, Pattern_Process(&pattern_200_1000, 1, ALWAYS_ACTIVE));
            }
        }*/
        Ql_GPIO_SetLevel(LED_RED, Pattern_Process(&pattern_200_400, 1, ALWAYS_ACTIVE));
        //Set_Pattern(&pattern_200_400, 20, 80);
      //  Set_Pattern(&pattern_200_1000, variable.system.ledTimerOff, variable.system.ledTimerOn);
    }
}