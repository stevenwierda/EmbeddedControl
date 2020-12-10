/* generated HAL source file - do not edit */
#include "hal_data.h"
#if (3) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_led_timer0) && !defined(SSP_SUPPRESS_ISR_GPT0)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 0);
#endif
#endif
static gpt_instance_ctrl_t led_timer0_ctrl;
static const timer_on_gpt_cfg_t led_timer0_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t led_timer0_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 0, .autostart = true, .p_callback = led_timer0_callback, .p_context = &led_timer0, .p_extend =
          &led_timer0_extend,
  .irq_ipl = (3), };
/* Instance structure to use this module. */
const timer_instance_t led_timer0 =
{ .p_ctrl = &led_timer0_ctrl, .p_cfg = &led_timer0_cfg, .p_api = &g_timer_on_gpt };
void g_hal_init(void)
{
    g_common_init ();
}
