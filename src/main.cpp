#include <Arduino.h>
#include "HAL/HAL.h"
#include "Port/Display.h"



void setup()
{
    HAL::Init();
    Port_Init();
}


void loop()
{
    HAL::Update();
}