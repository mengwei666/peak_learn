#include "HAL/HAL.h"
#include "App/Configs/Version.h"

#define DISP_HOR_RES         CONFIG_SCREEN_HOR_RES
#define DISP_VER_RES         CONFIG_SCREEN_VER_RES
#define DISP_BUF_SIZE        CONFIG_SCREEN_BUFFER_SIZE
extern lv_color_t* lv_disp_buf_p;

void my_test(void)
{
    static int  num = 0;
    Serial.print("Starting Peak num ");
    Serial.println(num++);

    // HAL::Power_Info_t power;
    // HAL::Power_GetInfo(&power);

    // HAL::Audio_PlayMusic("Startup");
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

    lv_disp_buf_p = static_cast<lv_color_t*>(malloc(DISP_BUF_SIZE * sizeof(lv_color_t)));
    if (lv_disp_buf_p == nullptr)
        LV_LOG_WARN("lv_port_disp_init malloc failed!\n");


    HAL::Power_Init();
    HAL::Backlight_Init();
    HAL::Encoder_Init();
    HAL::Buzz_init();
    HAL::Audio_Init();
    HAL::I2C_Init(true);
    HAL::IMU_Init();
    HAL::Audio_PlayMusic("Startup");
}


void HAL::Update()
{
    HAL::Power_Update();
    HAL::Encoder_Update();
    HAL::Audio_Update();
    HAL::IMU_Update();




    // HAL::Audio_PlayMusic("Startup");
    
    // __IntervalExecute(my_test(), 2000);


    // __IntervalExecute( HAL::Encoder_Update(), 200);
}