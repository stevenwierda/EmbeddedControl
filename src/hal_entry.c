/* HAL-only entry function */
#include "hal_data.h"

onOff = true;
void hal_entry(void)
{
    led_timer0.p_api->open(led_timer0.p_ctrl,led_timer0.p_cfg);
}

void led_timer0_callback(timer_callback_args_t * p_args){
        g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_01, onOff);
        onOff = !onOff;
}
