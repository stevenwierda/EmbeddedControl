#include "InteruptThread.h"

/* interupt thread entry function */
void InteruptThread_entry(void)
{
    /* TODO: add your own code here */
    while (1)
    {
        if (LEDTimer1Callback){
            if (g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_01, IOPORT_LEVEL_LOW)){
                g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_01, IOPORT_LEVEL_HIGH);
            }
            else{
                g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_02, IOPORT_LEVEL_LOW);
            }
        tx_thread_sleep (1);
    }
}

