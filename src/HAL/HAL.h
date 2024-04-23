#ifndef __HAL_H
#define __HAL_H

#include <stdint.h>
#include <Arduino.h>
#include "CommonMacro.h"
#include "App/Configs/Config.h"

namespace HAL
{
    void Init();
    void Update();

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
