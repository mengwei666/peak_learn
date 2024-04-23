#include "HAL/HAL.h"
#include "TonePlayer.h"
#include "MusicCode.h"
static TonePlayer player;

static void Tone_Callback(uint32_t freq, uint16_t volume)
{
    HAL::Buzz_Tone(freq);
}

void HAL::Audio_Init()
{
    player.SetCallback(Tone_Callback);
}

void HAL::Audio_Update()
{
    player.Update(millis());
}

bool HAL::Audio_PlayMusic(const char* name)
{
    bool retval = false;

    Serial.print("sizeof(MusicList): ");
    Serial.println(sizeof(MusicList));
    Serial.print("sizeof(MusicList[0]: ");
    Serial.println(sizeof(MusicList[0]));


    for (int i = 0; i < sizeof(MusicList) / sizeof(MusicList[0]); i++)
    {
        if (strcmp(name, MusicList[i].name) == 0)
        {
            Serial.print("MusicList[i].mc: ");
            Serial.println(i);
            player.Play(MusicList[i].mc, MusicList[i].length);
            retval = true;
            break;
        }
    }
    return retval;
}
