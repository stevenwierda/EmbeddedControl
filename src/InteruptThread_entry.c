#include "InteruptThread.h"

/* interupt thread entry function */
void InteruptThread_entry(void)
{
    /* TODO: add your own code here */
    while (1)
    {
        tx_thread_sleep (1);
    }
}

void ledtimer1callback(timer_callback_args_t * p_args){
    if (g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_01, IOPORT_LEVEL_LOW)){
        g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_01, IOPORT_LEVEL_HIGH);
    }
    else{
        g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_01, IOPORT_LEVEL_LOW);
    }
}

