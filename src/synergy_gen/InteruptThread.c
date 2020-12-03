/* generated thread source file - do not edit */
#include "InteruptThread.h"

TX_THREAD InteruptThread;
void InteruptThread_create(void);
static void InteruptThread_func(ULONG thread_input);
static uint8_t InteruptThread_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.InteruptThread") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
#if (1) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_LEDTimer) && !defined(SSP_SUPPRESS_ISR_GPT0)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 0);
#endif
#endif
static gpt_instance_ctrl_t LEDTimer_ctrl;
static const timer_on_gpt_cfg_t LEDTimer_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t LEDTimer_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 0, .autostart = true, .p_callback = LEDTimer1Callback, .p_context = &LEDTimer,
  .p_extend = &LEDTimer_extend, .irq_ipl = (1), };
/* Instance structure to use this module. */
const timer_instance_t LEDTimer =
{ .p_ctrl = &LEDTimer_ctrl, .p_cfg = &LEDTimer_cfg, .p_api = &g_timer_on_gpt };
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void InteruptThread_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */

    UINT err;
    err = tx_thread_create (&InteruptThread, (CHAR *) "interupt thread", InteruptThread_func, (ULONG) NULL,
                            &InteruptThread_stack, 1024, 2, 2, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&InteruptThread, 0);
    }
}

static void InteruptThread_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    InteruptThread_entry ();
}
