#include <Arduino.h>
#include "HAL/CommonMacro.h"





void my_test(void)
{
    static int  num = 0;
    Serial.print("Starting Peak num ");
    Serial.println(num++);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting Peak");
}


void loop()
{
    __IntervalExecute(my_test(), 500);
}