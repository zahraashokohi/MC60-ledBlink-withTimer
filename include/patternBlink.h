#ifndef PATTERN_BLINK_H_INCLUDED
#define PATTERN_BLINK_H_INCLUDED



#include <stdint.h>
#include <stddef.h>

typedef enum{
    PATTERN_UNKNOWN,
    PATTERN_OK,
    PATTERN_DISABLE,

}Pattern_Error_Status;

typedef enum{
	  Pattern_Off = 0,
    Pttern_On = 1,
    
}Pattern_State;

typedef enum{
    Pttern_Enable = 1,
    Pattern_Disable = 0,
}Active_Pattern;

typedef enum{
    ALWAYS_ACTIVE = 1,
    LIMIT_TIME_ACTIVE = 2,
}Repeat_Pattern;


typedef enum{

    Timer_On_Start = 0,
    Timer_Off_Start = 1,
    Timer_Stop = 2,
    Timer_Reset = 3,
}Timer_State;

typedef struct{
    uint8_t             Pattern_State;
    uint32_t            System_Time_Interval;
    uint32_t            Pattern_TimeOn;
    uint32_t            Pattern_TimeOff;
	uint32_t            CounterDelay;
	uint8_t             Repeat_Count;
	uint8_t             template_pattern;
	uint8_t             ChangeState;
}Pattern_t;

Pattern_Error_Status Init_Pattern (Pattern_t* pattern, Active_Pattern  active_pattern, uint32_t timer_interval);

Pattern_Error_Status  Set_Pattern(Pattern_t* pattern, uint32_t pattern_timeOn, uint32_t pattern_timeOff);
uint8_t  Pattern_Process (Pattern_t* pattern, uint8_t pattern_num_repeat, Repeat_Pattern repeat);


#endif

