#include "HAL/HAL.h"

static bool IsEnable = true;
static int32_t duration = 0;
static uint32_t freq = 0;

static void BuzzerThread(void* argument)
{
    for (;;)
    {
        // Serial.println("#1");
        if (duration > 0)
        {        
            // Serial.print("freq: ");
            // Serial.println(freq);
            // Serial.print("duration: ");
            // Serial.println(duration);
            // Serial.println("------------------------------");

            ledcWriteTone(CONFIG_BUZZ_CHANNEL, freq);
            delay(duration);
            ledcWriteTone(CONFIG_BUZZ_CHANNEL, 0);

            duration = 0;
        }

        delay(50);
    }
}

void HAL::Buzz_init()
{
    pinMode(CONFIG_BUZZ_PIN, OUTPUT);
    ledcAttachPin(CONFIG_BUZZ_PIN, CONFIG_BUZZ_CHANNEL);
    ledcSetup(CONFIG_BUZZ_CHANNEL, 0, 8);
    ledcWriteTone(CONFIG_BUZZ_CHANNEL, 0);

    // // Create Buzzer thread
    // TaskHandle_t handleBuzzerThread;
    // xTaskCreate(BuzzerThread, "BuzzerThread", 800, nullptr, 1, &handleBuzzerThread);
}

void HAL::Buzz_SetEnable(bool en)
{
    IsEnable = en;
}

void HAL::Buzz_Tone(uint32_t _freq, int32_t _duration)
{
    if (!IsEnable)
        return;


    // Serial.print("_freq: ");
    // Serial.println(_freq);
    // Serial.print("_duration: ");
    // Serial.println(_duration);
    // Serial.println("----------------------");

    if (_duration == 0)
    {
        ledcWriteTone(CONFIG_BUZZ_CHANNEL, _freq);
    } else
    {
        freq = _freq;
        duration = _duration;
    }
}


