#ifndef __HAL_H
#define __HAL_H

#include <stdint.h>
#include <Arduino.h>
#include "CommonMacro.h"
#include "App/Configs/Config.h"
#include "HAL_Def.h"

namespace HAL
{
    void Init();
    void Update();

/* Power */
    void Power_Init();
    void Power_HandleTimeUpdate();
    void Power_SetAutoLowPowerTimeout(uint16_t sec);
    uint16_t Power_GetAutoLowPowerTimeout();
    void Power_SetAutoLowPowerEnable(bool en);
    void Power_Shutdown();
    void Power_Update();
    void Power_EventMonitor();
    void Power_GetInfo(Power_Info_t* info);
    typedef void(* Power_CallbackFunction_t)(void);
    void Power_SetEventCallback(Power_CallbackFunction_t callback);


/* Buzzer */
    void Buzz_init();
    void Buzz_SetEnable(bool en);
    void Buzz_Tone(uint32_t freq, int32_t duration = 0);

/* Audio */
    void Audio_Init();
    void Audio_Update();
    bool Audio_PlayMusic(const char* name);
}

#endif
