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

/**
  * @brief  将一个值限制在一个范围内
  * @param  x:被限制的值(任意类型)
  * @param  min:最小值(任意类型)
  * @param  max:最大值(任意类型)
  * @retval 无
  */
#define __LimitValue(x, min, max) ((x)=constrain((x),(min),(max)))

#endif