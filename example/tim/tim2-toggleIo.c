/*
 * @Author:
 *  #Jiabin Hsu | zsiothsu(at)zhishan-iot.tk
 * @Compiler:SDCC v3.6.0
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:show how to use firmware library to make an interruption by TIM2
 * @Test-board:TS51-V2.0
 * @Test-mcu:STC89C52RC
 * @Version:V1
 */

#include "conf.h"
 
/*
 * @Prototype:void sys_init(void)
 * @Parameter:None
 * @Ret-val:None
 * @Note:initial MCU
 */
void sys_init(void)
{
    TIM2_configTypeDef tc;
    
    tc.function          = TIM2_function_tim;
    tc.interruptState    = ENABLE;
    tc.interruptPriority = INTR_priority_0;
    tc.mode              = TIM2_mode_0;
    tc.value             = TIM2_calculateValue(50000);
    
    TIM2_config(&tc);
    TIM2_cmd(ENABLE);
    enableAllInterrupts();
}

void main(void)
{
    sys_init();
    while(true);
}

/*
 * @Prototype:void tim2_isr(void)
 * @Parameter:None
 * @Ret-val:None
 * @Note:interrupt service function for TIM2
 */
void tim2_isr(void) __interrupt TF2_VECTOR
{
    static u8 i = 0;
    TIM2_clearFlag();
    
    /* per 500ms */
    i++;
    if(i == 10)
    {
        GPIO_toggleBitValue(PERIPH_GPIO_1,PERIPH_GPIO_PIN_2);
        i = 0;
    }
}
