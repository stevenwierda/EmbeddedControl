/* HAL-only entry function */
#include "hal_data.h"
#include "main_thread.h"
#include "time.h"


void hal_entry(void)
{

}

void TimeAdd_timer0_callback(timer_callback_args_t * p_args){
    addHunderdms();
}
