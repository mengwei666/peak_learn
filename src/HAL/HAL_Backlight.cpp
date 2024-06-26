// #include "Port/Display.h"
#include "HAL/HAL.h"

static uint32_t backlightValue = 0;
/**
  * @brief  �������Ƚ��䣬��lv_anim����
  * @param  obj:����
  * @param  brightness:����ֵ
  * @retval None
  */
static void Backlight_AnimCallback(void *obj, int32_t brightness)
{
    HAL::Backlight_SetValue(brightness);
}

/**
  * @brief  �����ʼ��
  * @param  ��
  * @retval ��
  */
void HAL::Backlight_Init()
{
    /*PWM��ʼ����1024����5KHzƵ��*/
    ledcSetup(0, 5000, 10);
    ledcAttachPin(CONFIG_SCREEN_BLK_PIN, 0);
    ledcWrite(0, 1024);
}

/**
  * @brief  �������ã�����Ч��
  * @param  target:Ŀ������(0~1000 -> 0~100%)
  * @retval ��
  */
void HAL::Backlight_SetGradual(uint32_t target, uint16_t time)
{
    // lv_anim_t a;
    // lv_anim_init(&a);
    // lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) Backlight_AnimCallback);
    // lv_anim_set_values(&a, Backlight_GetValue(), target);
    // lv_anim_set_time(&a, time);
    // lv_anim_set_path_cb(&a, lv_anim_path_ease_out);

    // lv_anim_start(&a);
}

/**
  * @brief  ��ȡ��������
  * @param  ��
  * @retval ��ǰ����(0~1000 -> 0~100%)
  */
uint32_t HAL::Backlight_GetValue()
{
    return backlightValue;
}

/**
  * @brief  ���ñ�������
  * @param  val: ����(0~1000 -> 0~100%)
  * @retval ��
  */
void HAL::Backlight_SetValue(int32_t val)
{
    val = constrain(val, 0, 1024);
    backlightValue = val;
    val =   backlightValue;
    ledcWrite(0, val);
}

/**
  * @brief  ����ǿ�Ƶ���
  * @param  en: ����ʹ��
  * @retval ��
  */
void HAL::Backlight_ForceLit(bool en)
{
    pinMode(CONFIG_SCREEN_BLK_PIN, OUTPUT);
    digitalWrite(CONFIG_SCREEN_BLK_PIN, en);
}
