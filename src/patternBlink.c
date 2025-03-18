#include "patternBlink.h"

Pattern_Error_Status Init_Pattern (Pattern_t* pattern, Active_Pattern  active_pattern, uint32_t timer_interval)
{
    pattern->Pattern_State =    active_pattern;
    pattern->System_Time_Interval = timer_interval;
    return PATTERN_OK;
}

Pattern_Error_Status  Set_Pattern(Pattern_t* pattern, uint32_t pattern_timeOn, uint32_t pattern_timeOff)
{
    if(pattern->Pattern_State == Pttern_Enable)
    {
        pattern->Pattern_TimeOn = pattern_timeOn * pattern->System_Time_Interval;//1 ms
        pattern->Pattern_TimeOff = pattern_timeOff * pattern->System_Time_Interval;//1ms
        return PATTERN_OK;
    }
    else{
        return PATTERN_DISABLE;
    }
}


uint8_t  Pattern_Process (Pattern_t* pattern, uint8_t pattern_num_repeat, Repeat_Pattern repeat)
{
    if(pattern->Pattern_State == Pttern_Enable)
    {
            switch(pattern->ChangeState)
            {
                case Timer_On_Start:
                    if((pattern->CounterDelay += pattern->System_Time_Interval )>= (pattern->Pattern_TimeOn - pattern->System_Time_Interval))
                    {
                        pattern->ChangeState = Timer_Off_Start;
                        pattern->CounterDelay  = pattern->System_Time_Interval;
                        pattern->template_pattern = Pttern_On;
                    }
                    break;
                case  Timer_Off_Start:
                    if((pattern->CounterDelay += pattern->System_Time_Interval )>= (pattern->Pattern_TimeOff - pattern->System_Time_Interval))
                    {
                        pattern->ChangeState = Timer_On_Start;
                        pattern->CounterDelay  = pattern->System_Time_Interval;
                        pattern->template_pattern = Pattern_Off;
                        if(repeat == LIMIT_TIME_ACTIVE)
                        {
                            pattern->Repeat_Count++;
                            if(pattern->Repeat_Count >= pattern_num_repeat)
                            {
                                pattern->Repeat_Count = 0;
                                pattern->ChangeState = Timer_Stop;
                                pattern->template_pattern = Pattern_Off;
                            }
                        }
                    }
                    break;
                default :
                    break;
            }
            return pattern->template_pattern;
    }
    else{
        return PATTERN_DISABLE;
    }   

}
