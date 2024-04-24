#include <Arduino.h>
#include "HAL/HAL.h"
#include "Port/Display.h"

#include "lv_examples.h"

// 定义图片索引
int currentImageIndex = 0;

// 图片数组
void (*imageFunctions[])() = {lv_example_img_6, lv_example_img_7, lv_example_img_9};

// 图片切换计时器
unsigned long lastImageChangeTime = 0;
const unsigned long imageChangeInterval = 2000; // 每秒切换一次图片



// 图片切换函数
void changeImage() 
{
    static SCREEN_CLASS screen;
    // 清除屏幕
    screen.fillScreen(TFT_BLACK);
    
    // 调用当前图片函数
    imageFunctions[currentImageIndex]();

    // 更新当前图片索引
    currentImageIndex = (currentImageIndex + 1) % 3; // 保证循环切换
}

void setup()
{
    HAL::Init();
    Port_Init();
}


void loop()
{
    HAL::Update();

    lv_tick_inc(5); 
 	lv_task_handler();

    // 检查是否到了切换图片的时间
    unsigned long currentTime = millis();
    if (currentTime - lastImageChangeTime >= imageChangeInterval) {
        // 更新上次切换图片的时间
        lastImageChangeTime = currentTime;

        // 切换图片
        changeImage();
    }

}