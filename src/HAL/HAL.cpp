#include "HAL/HAL.h"



void my_test(void)
{
    static int  num = 0;
    Serial.print("Starting Peak num ");
    Serial.println(num++);

    HAL::Audio_PlayMusic("Startup");
    // HAL::Audio_PlayMusic("Shutdown");

    // // 在这里控制蜂鸣器的高低电平
    // digitalWrite(CONFIG_BUZZ_PIN, HIGH); // 设置高电平，蜂鸣器响
    // vTaskDelay(500 / portTICK_PERIOD_MS); // 延迟一段时间
    // digitalWrite(CONFIG_BUZZ_PIN, LOW); // 设置低电平，蜂鸣器停止响
    // vTaskDelay(500 / portTICK_PERIOD_MS); // 再次延迟一段时间
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
    HAL::Audio_Update();
    
    __IntervalExecute(my_test(), 2000);
}