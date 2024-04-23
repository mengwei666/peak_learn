#include "HAL/HAL.h"

#define CONFIG_BUZZ_CHANNEL 25 // 设置蜂鸣器的引脚

// 定义生日快乐歌的音符频率
#define NOTE_C4  261
#define NOTE_D4  294
#define NOTE_E4  329
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5  988


// const int melody[] = {
//   NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_C5, NOTE_B4,
//   NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_D5, NOTE_C5,
//   NOTE_G4, NOTE_G4, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_B4, NOTE_A4,
//   NOTE_F5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_C5
// };

// const int noteDurations[] = {
//   4, 4, 8, 8, 8, 4,
//   4, 4, 8, 8, 8, 4,
//   4, 4, 8, 8, 8, 8, 4,
//   4, 4, 8, 8, 8, 4
// };


// // 定义“我爱你”的音符频率
// #define NOTE_I  261
// #define NOTE_LOVE  294
// #define NOTE_YOU  329

const int melody[] = {
  NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_E4, NOTE_C4
};

const int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 2
};

void my_test(void)
{
    static int  num = 0;
    Serial.print("Starting Peak num ");
    Serial.println(num++);

    // ledcWriteTone(CONFIG_BUZZ_CHANNEL, 659);

    // HAL::Audio_PlayMusic("Startup");
    // HAL::Audio_PlayMusic("Shutdown");

    // // 在这里控制蜂鸣器的高低电平
    // digitalWrite(CONFIG_BUZZ_PIN, HIGH); // 设置高电平，蜂鸣器响
    // vTaskDelay(500 / portTICK_PERIOD_MS); // 延迟一段时间
    // digitalWrite(CONFIG_BUZZ_PIN, LOW); // 设置低电平，蜂鸣器停止响
    // vTaskDelay(500 / portTICK_PERIOD_MS); // 再次延迟一段时间


  // 循环播放生日快乐歌
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    int noteDuration = 1000 / noteDurations[i];
    tone(CONFIG_BUZZ_CHANNEL, melody[i], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(CONFIG_BUZZ_CHANNEL);
  }
}


void HAL::Init()
{
    Serial.begin(115200);
    Serial.println("Version: " "v1.0");
    Serial.println("Author: " "MW");

    HAL::Buzz_init();
    HAL::Audio_Init();
}


void HAL::Update()
{
    // HAL::Audio_Update();
    
    __IntervalExecute(my_test(), 2000);
}