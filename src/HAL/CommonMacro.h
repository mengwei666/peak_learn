#ifndef __COMMONMACRO_H
#define __COMMONMACRO_H



/**
  * @brief  非阻塞式间隔指定时间执行一个函数
  * @param  func:被执行函数(可以是赋值等其他语句)
  * @param  time:设定间隔时间(ms)
  * @retval 无
  */
#define __IntervalExecute(func, time) \
do{\
    static unsigned long lasttime=0;\
    if(millis()-lasttime>=(time))func,lasttime=millis();\
}while(0)


#endif