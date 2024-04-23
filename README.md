# 学习PEAK

> 学习大佬开发过程，提升自己能力，充实自己。
>
> 填坑大佬的留下的任务。
>
> 通过学习后改造一款带闹钟的手表。

## 24-4-12 了解串口打印

移植程序，做成模版，进行串口打印，了解非阻塞式间隔指定时间执行一个函数__IntervalExecute(func, time)，利用的是系统自带的时钟计时做的。

## 24-4-13 焊接PEAK文件自带板子

* [X] 焊接遇到usb到cp2102N之间短路问题。排查后发现是cp2102N的3号和4号引脚粘连，其他引脚粘连。
  解决过程重新焊接。
* [X] 电脑不识别CP2102N芯片。排查后有两个问题

  * Type-C母卧贴里的USBD+不输出信号电压。
  * CP2102N是盗版，要按照特殊的驱动，ubuntu不识别。

  > **解决过程**：替换新的Type-C母卧贴和正版CP2102
  > **后续借鉴**：电脑不识别CP2102时，先判断是否短路，再判断cp2102是否上电，D+D-是否有信号电平。可以参考正常芯片电压。
  > 一般这个测试通过后，电脑->设备管理器->其他设备->识别状态。再安装完驱动就正常了，如果还是不行要考虑换方案了。
  >
* [X] ESP32-PICO-D4无法下载问题：

  > 排查后发现USB供电后通过红色LED贴片后再加上两个1k和10k电阻压降后，小于3.3V芯片无法启动。
  > 解决办法：将两个电阻驱动后测试压降为3.3V上电后正常下载了。
  > **后续发现：焊接电池后,通过长按编码器开关后可以正常下载，就恢复了两个电阻。**
  >

## 24-4-14 测试模块

* [X] 蜂鸣器模块

  > 使用的是无源电磁式侧发声蜂鸣器(韩国SMT-101-03)：有源蜂鸣器内部带震荡源，所以只要一通电就会叫，而无源内部不带震荡源，所以如果用直流信号无法令其鸣叫。用黑表笔接蜂鸣器正极的引脚，红表笔在另一引脚上来回碰触，如果触发出咔咔声的且电阻只有8欧姆或16欧姆的是无源蜂鸣器;如果能发出持续声音的，且电阻在几百欧以上的，是有源蜂鸣器。可以直接响的为有源电磁式蜂鸣器，不直接响的，需要方波来驱动才可以响的为无源电磁式蜂鸣器。
  > 在电路中是接通的电池供电，主控引脚通过三级管驱动进行蜂鸣器的开关的。通过产生PWM波信号，可以做出多来米发索拉西的效果。
  >
* [X] 程序控制测试

  * [X] IO口配置
    ```
    pinMode(CONFIG_BUZZ_PIN, OUTPUT); //配置CONFIG_BUZZ_PIN为输出状态
    digitalWrite(CONFIG_BUZZ_PIN, HIGH); // 设置高电平，蜂鸣器响
    vTaskDelay(500 / portTICK_PERIOD_MS); // 延迟一段时间
    digitalWrite(CONFIG_BUZZ_PIN, LOW); // 设置低电平，蜂鸣器停止响
    vTaskDelay(500 / portTICK_PERIOD_MS); // 再次延迟一段时间
    ```
  * [X] PWM配置
    ```
    ledcAttachPin(CONFIG_BUZZ_PIN, CONFIG_BUZZ_CHANNEL); //将一个特定的引脚与LED控制器（LEDC）的通道（channel）进行关联
    ledcSetup(CONFIG_BUZZ_CHANNEL, 0, 8); //配置LED控制器的通道
    ledcWriteTone(CONFIG_BUZZ_CHANNEL, 0); //设置LED控制器的通道输出的PWM占空比
    ```
* [X] 任务句柄区别：

```
xTaskCreate(BuzzerThread, "BuzzerThread", 800, nullptr, 1, &handleBuzzerThread);
xTaskCreate(http_get_task, "http_get_task", 4096, NULL, 5, NULL);
/*
区别在于：这两行代码的区别在于最后一个参数，即任务句柄的存储方式。第一行代码中，任务句柄被存储在了名为 handleBuzzerThread 的变量中，而在第二行代码中，则将任务句柄存储在了 NULL 中，即没有存储任务句柄的变量。
具体来说，第一行代码创建了一个任务并将其句柄存储在了 handleBuzzerThread 变量中，这样在后续的代码中可以使用这个变量来引用该任务，例如暂停、删除或查询任务状态等操作。
而第二行代码中，任务句柄被存储在了 NULL 中，这表示并不需要在后续的代码中引用该任务，因此如果不需要后续操作任务，可以选择不存储任务句柄，简化代码逻辑。
*/  
```

* [X] 了解蜂鸣器工作原理
  1.创建一个蜂鸣器任务进程。如果有函数需要运行蜂鸣器功能，则响应。
  2.在其他进程中，添加蜂鸣器状态功能，哪里需要就在哪里添加。

# 24-4-15 测试电源模块

长按上电，等程序跑起来时配置CONFIG_POWER_EN_PIN（21）引脚通过电路设计打开三极管，保持电池供电，这样就开机了，详细的电路图需要在详细学习。

电源进程检查的是电池电量，通过adc测量电压，用万用表测试是有分压的是2V,但是引脚没有读出数值。怀疑芯片的引脚没有焊好，虚焊了。

# 24-4-16 测试编码器模块

编码器模块按键按下通过bottonEvent判断是短按，长按，按键的判断。

编码器的ab播轮的工作模式时，顺时针旋转时，(b = 0  a = 1) (b = 0  a = 0) (b = 1  a = 0) (b = 1  a = 1)   (b = 0  a = 1) 逆时针反过来。初始化配置B进入中断判断。

# 24-4-17 测试LCD屏幕

搞懂原理图，屏幕背光是上电正常亮，电路图设计的是控制屏幕上电时的GND的电平变化改变背光亮度，程序上是通过pwm改变背光引脚。

使用的是st7789芯片通过spi驱动屏幕显示的，该程序用了TFT-eSPI库进行配置st7789芯片寄存器配置，在使用了lvgl框架显示屏幕不同的画面。（需要学习了解tft_espi和lvgl）

# 24-4-23 上传程序到git