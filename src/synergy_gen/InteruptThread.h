/* generated thread header file - do not edit */
#ifndef INTERUPTTHREAD_H_
#define INTERUPTTHREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
extern "C" void InteruptThread_entry(void);
#else
extern void InteruptThread_entry(void);
#endif
#include "r_gpt.h"
#include "r_timer_api.h"
#ifdef __cplusplus
extern "C"
{
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t LEDTimer;
#ifndef LEDTimer1Callback
void LEDTimer1Callback(timer_callback_args_t *p_args);
#endif
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* INTERUPTTHREAD_H_ */
