#include "HAL/HAL.h"


/* Buzzer */
#define CONFIG_BUZZ_PIN             25
#define CONFIG_BUZZ_CHANNEL         2
#define CONFIG_SOUND_ENABLE_DEFAULT false

static bool IsEnable = true;
static int32_t duration = 0;
static uint32_t freq = 0;

void HAL::Buzz_init()
{
    pinMode(CONFIG_BUZZ_PIN, OUTPUT);
    ledcAttachPin(CONFIG_BUZZ_PIN, CONFIG_BUZZ_CHANNEL);
    ledcSetup(CONFIG_BUZZ_CHANNEL, 0, 8);
    ledcWriteTone(CONFIG_BUZZ_CHANNEL, 0);
}

void HAL::Buzz_Tone(uint32_t _freq, int32_t _duration)
{
    if (!IsEnable)
        return;

    Serial.print("_freq: ");
    Serial.println(_freq);
    Serial.print("_duration: ");
    Serial.println(_duration);
    Serial.println("----------------------");

    if (_duration == 0)
    {
        ledcWriteTone(CONFIG_BUZZ_CHANNEL, _freq);
    } else
    {
        freq = _freq;
        duration = _duration;
    }
}


