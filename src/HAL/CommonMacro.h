#ifndef __COMMONMACRO_H
#define __COMMONMACRO_H



/**
  * @brief  ������ʽ���ָ��ʱ��ִ��һ������
  * @param  func:��ִ�к���(�����Ǹ�ֵ���������)
  * @param  time:�趨���ʱ��(ms)
  * @retval ��
  */
#define __IntervalExecute(func, time) \
do{\
    static unsigned long lasttime=0;\
    if(millis()-lasttime>=(time))func,lasttime=millis();\
}while(0)


#endif