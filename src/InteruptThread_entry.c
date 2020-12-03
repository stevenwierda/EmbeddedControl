#include "InteruptThread.h"

/* Interupt Thread entry function */
void InteruptThread_entry(void)
{
    /* TODO: add your own code here */
    while (1)
    {
        tx_thread_sleep (1);
    }
}
