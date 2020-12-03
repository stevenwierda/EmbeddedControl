/*

    Project: LED Lesson with 32 bit r_gbt timer with interrupt enabled.
    Name:    Michael Li
    Company: Consultant
    Web page: https://www.miketechuniverse.com/
    Date:    1/9/18

    SSP version: 1.30
    E2 Studio version: 5.4.0.023

    Description: Toggle LED1/2/3 (P1_2/3/13).  Set timer0 as a periodical timer.
                 Compare the actual timer0 value (depending on clock frequency).

                 2Hz or 0.500sec period (Toggle rate)

*/

/* HAL-only entry function */
#include "hal_data.h"

bool OnOff = true;
bool OffOn = false;

bool Aan = false;

void hal_entry(void)
{
    /* TODO: add your own code here */
    led_timer0.p_api->open(led_timer0.p_ctrl,led_timer0.p_cfg);

    while(1){
        R_BSP_SoftwareDelay(500, BSP_DELAY_UNITS_MILLISECONDS);
        g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, OnOff);   // GREEN LED
        g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_01, OffOn);   // Yellow LED
        g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_02, OnOff);   // Red LED

        OnOff = !OnOff;
        OffOn = !OffOn;
    }
}

void led_timer0_callback(timer_callback_args_t * p_args){
    g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_13, Aan);
    Aan = !Aan;
}
/*
IOPORT_PORT_06_PIN_00,  ///< LED1_GREEN
IOPORT_PORT_06_PIN_01,  ///< LED2_RED
IOPORT_PORT_06_PIN_02,  ///< LED3_YELLOW
*/
