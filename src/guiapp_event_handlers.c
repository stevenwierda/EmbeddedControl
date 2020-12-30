#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"
#include "main_thread.h"
#include "time.h"

static bool button_enabled = false;
bool onOff = false;
int daynr;
unsigned long int InteruptTimer = 250;
bsp_leds_t leds;

extern GX_WINDOW_ROOT * p_window_root;

static UINT show_window(GX_WINDOW * p_new, GX_WIDGET * p_widget, bool detach_old);
static void update_text_id(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT string_id);
static void update_button_text_id(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT string_id);
static void update_number_id(GX_WIDGET * p_widget, GX_RESOURCE_ID id, INT value);

UINT mainWindowHandler(GX_WINDOW *widget, GX_EVENT *event_ptr)
{
    UINT result = gx_window_event_process(widget, event_ptr);

    switch (event_ptr->gx_event_type)
    {
    case GX_SIGNAL(BUTSETTINGS, GX_EVENT_CLICKED):
        show_window((GX_WINDOW*)&Settings, (GX_WIDGET*)widget, true);
        break;
    case GX_SIGNAL(BUTTIME, GX_EVENT_CLICKED):
        show_window((GX_WINDOW*)&Time, (GX_WIDGET*)widget, true);
        break;
    case GX_SIGNAL(BUTLED, GX_EVENT_CLICKED):
        show_window((GX_WINDOW*)&LEDControle, (GX_WIDGET*)widget, true);
        break;
    default:
        gx_window_event_process(widget, event_ptr);
        break;
    }

    return result;
}

UINT timeWindowHandler(GX_WINDOW *widget, GX_EVENT *event_ptr)
{
    UINT result = gx_window_event_process(widget, event_ptr);
    update_number_id(widget->gx_widget_parent, PROMPTYEAR, getYear());
    update_number_id(widget->gx_widget_parent, PROMPTMONTH, getMonth());
    update_number_id(widget->gx_widget_parent, PROMPTDAY, getDay());
    update_number_id(widget->gx_widget_parent, PROMPTHOUR, getHour());
    update_number_id(widget->gx_widget_parent, PROMPTMINUTE, getMin());
    update_number_id(widget->gx_widget_parent, PROMPTSEC, getHour());
    update_number_id(widget->gx_widget_parent, PROMPTMSEC, getMin());
    daynr = getDaynr();
    if(daynr == 1){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_MONDAY);
    }
    else if(daynr == 2){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_THUSEDAY);
    }
    else if(daynr == 3){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_WEDNESDAY);
    }
    else if(daynr == 4){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_THURSTDAY);
    }
    else if(daynr == 5){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_FRIDAY);
    }
    else if(daynr == 6){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_SATERDAY);
    }
    else if(daynr == 7){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_SUNDAY);
    }

    if(TimeAdd_timer0_callback == true){
        daynr = getDaynr();
        if(daynr == 1){
            update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_MONDAY);
        }
        else if(daynr == 2){
            update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_THUSEDAY);
        }
        else if(daynr == 3){
            update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_WEDNESDAY);
        }
        else if(daynr == 4){
            update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_THURSTDAY);
        }
        else if(daynr == 5){
            update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_FRIDAY);
        }
        else if(daynr == 6){
            update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_SATERDAY);
        }
        else if(daynr == 7){
            update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_SUNDAY);
        }
        update_number_id(widget->gx_widget_parent, PROMPTYEAR, getYear());
        update_number_id(widget->gx_widget_parent, PROMPTMONTH, getMonth());
        update_number_id(widget->gx_widget_parent, PROMPTDAY, getDay());
        update_number_id(widget->gx_widget_parent, PROMPTHOUR, getHour());
        update_number_id(widget->gx_widget_parent, PROMPTMINUTE, getMin());
        update_number_id(widget->gx_widget_parent, PROMPTSEC, getSec());
        update_number_id(widget->gx_widget_parent, PROMPTMSEC, getMsec());
    }


    switch (event_ptr->gx_event_type){
        case GX_SIGNAL(BUTTERUGTIME, GX_EVENT_CLICKED):
                    show_window((GX_WINDOW*)&Main, (GX_WIDGET*)widget, true);
            break;
        default:
            result = gx_window_event_process(widget, event_ptr);
            break;
    }
    return result;
}

UINT settingsWindowHandler(GX_WINDOW *widget, GX_EVENT *event_ptr)
{
    UINT result = gx_window_event_process(widget, event_ptr);
    switch (event_ptr->gx_event_type){
        case GX_SIGNAL(BUTTERUGSETTINGS, GX_EVENT_CLICKED):
            show_window((GX_WINDOW*)&Main, (GX_WIDGET*)widget, true);
        break;
        case GX_SIGNAL(BUTLEDINTERUPT, GX_EVENT_CLICKED):
                show_window((GX_WINDOW*)&setLedOneInterupt, (GX_WIDGET*)widget, true);
                break;
        case GX_SIGNAL(BUTSETTIME, GX_EVENT_CLICKED):
                show_window((GX_WINDOW*)&setTime, (GX_WIDGET*)widget, true);
                break;
        default:
            result = gx_window_event_process(widget, event_ptr);
            break;
    }
    return result;
}

UINT LEDWindowHandler(GX_WINDOW *widget, GX_EVENT *event_ptr)
{
    UINT result = gx_window_event_process(widget, event_ptr);

    switch (event_ptr->gx_event_type){
        case GX_SIGNAL(butterugLED, GX_EVENT_CLICKED):
            show_window((GX_WINDOW*)&Main, (GX_WIDGET*)widget, true);
            break;
        case GX_SIGNAL(LEDSWITCH, GX_EVENT_TOGGLE_ON):
                button_enabled = true;
                update_text_id(widget->gx_widget_parent, LEDSTATUS, GX_STRING_ID_LED_ON);
                g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_LOW);
                break;
        case GX_SIGNAL(LEDSWITCH, GX_EVENT_TOGGLE_OFF):
                button_enabled = false;
                update_text_id(widget->gx_widget_parent, LEDSTATUS, GX_STRING_ID_LED_OFF);
                g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_HIGH);
                break;
        default:
            result = gx_window_event_process(widget, event_ptr);
            break;
    }
    return result;
}

UINT timeSetHandler(GX_WINDOW *widget, GX_EVENT *event_ptr){
    UINT result = gx_window_event_process(widget, event_ptr);
    daynr = getDaynr();
    if(daynr == 1){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_MONDAY);
    }
    else if(daynr == 2){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_THUSEDAY);
    }
    else if(daynr == 3){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_WEDNESDAY);
    }
    else if(daynr == 4){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_THURSTDAY);
    }
    else if(daynr == 5){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_FRIDAY);
    }
    else if(daynr == 6){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_SATERDAY);
    }
    else if(daynr == 7){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_SUNDAY);
    }
    update_number_id(widget->gx_widget_parent, PROMPTYEAR, getYear());
    update_number_id(widget->gx_widget_parent, PROMPTMONTH, getMonth());
    update_number_id(widget->gx_widget_parent, PROMPTDAY, getDay());
    update_number_id(widget->gx_widget_parent, PROMPTHOUR, getHour());
    update_number_id(widget->gx_widget_parent, PROMPTMINUTE, getMin());


    switch (event_ptr->gx_event_type){
        case GX_SIGNAL(BUTTERUGTIMESET, GX_EVENT_CLICKED):
            show_window((GX_WINDOW*)&Settings, (GX_WIDGET*)widget, true);
        break;
        case GX_SIGNAL(BUTYEARPLUS, GX_EVENT_CLICKED):
            changeYearUp();
            update_number_id(widget->gx_widget_parent, PROMPTYEAR, getYear());
            break;
        case GX_SIGNAL(BUTYEARMIN, GX_EVENT_CLICKED):
            changeYearDown();
            update_number_id(widget->gx_widget_parent, PROMPTYEAR, getYear());
            break;
        case GX_SIGNAL(BUTMONTHPLUS, GX_EVENT_CLICKED):
            changeMonthUp();
            update_number_id(widget->gx_widget_parent, PROMPTMONTH, getMonth());
            break;
        case GX_SIGNAL(BUTMONTHMIN, GX_EVENT_CLICKED):
            changeMonthDown();
            update_number_id(widget->gx_widget_parent, PROMPTMONTH, getMonth());
            break;
        case GX_SIGNAL(BUTDAYPLUS, GX_EVENT_CLICKED):
            changeDayUp();
            update_number_id(widget->gx_widget_parent, PROMPTDAY, getDay());
            break;
        case GX_SIGNAL(BUTDAYMIN, GX_EVENT_CLICKED):
            changeDayDown();
            update_number_id(widget->gx_widget_parent, PROMPTDAY, getDay());
            break;
        case GX_SIGNAL(BUTHOURPLUS, GX_EVENT_CLICKED):
            changeHourUp();
            update_number_id(widget->gx_widget_parent, PROMPTHOUR, getHour());
            break;
        case GX_SIGNAL(BUTHOURMIN, GX_EVENT_CLICKED):
            changeHourDown();
            update_number_id(widget->gx_widget_parent, PROMPTHOUR, getHour());
            break;
        case GX_SIGNAL(BUTMINUTEPLUS, GX_EVENT_CLICKED):
            changeMinUp();
            update_number_id(widget->gx_widget_parent, PROMPTMINUTE, getMin());
            break;
        case GX_SIGNAL(BUTMINUTEMIN, GX_EVENT_CLICKED):
            changeMinDown();
            update_number_id(widget->gx_widget_parent, PROMPTMINUTE, getMin());
            break;
        case GX_SIGNAL(BUTNAMEDAYPLUS, GX_EVENT_CLICKED):
            changeDaynrUp();
            daynr = getDaynr();
            if(daynr == 1){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_MONDAY);
            }
            else if(daynr == 2){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_THUSEDAY);
            }
            else if(daynr == 3){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_WEDNESDAY);
            }
            else if(daynr == 4){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_THURSTDAY);
            }
            else if(daynr == 5){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_FRIDAY);
            }
            else if(daynr == 6){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_SATERDAY);
            }
            else if(daynr == 7){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_SUNDAY);
            }
            break;
        case GX_SIGNAL(BUTNAMEDAYMIN, GX_EVENT_CLICKED):
            changeDaynrDown();
            daynr = getDaynr();
            if(daynr == 1){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_MONDAY);
            }
            else if(daynr == 2){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_THUSEDAY);
            }
            else if(daynr == 3){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_WEDNESDAY);
            }
            else if(daynr == 4){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_THURSTDAY);
            }
            else if(daynr == 5){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_FRIDAY);
            }
            else if(daynr == 6){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_SATERDAY);
            }
            else if(daynr == 7){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_SUNDAY);
            }
            break;
        default:
            result = gx_window_event_process(widget, event_ptr);
        break;
    }
    return result;
}

UINT setLedOneInteruptHandler(GX_WINDOW *widget, GX_EVENT *event_ptr)
{
    UINT result = gx_window_event_process(widget, event_ptr);
    update_number_id(widget->gx_widget_parent, TIME, (int)InteruptTimer);
    switch (event_ptr->gx_event_type){
        case GX_SIGNAL(BUTTERUGINTERUPTSET, GX_EVENT_CLICKED):
            show_window((GX_WINDOW*)&Settings, (GX_WIDGET*)widget, true);
            break;
        case GX_SIGNAL(BUTDECREASE, GX_EVENT_CLICKED):
            if(InteruptTimer >> 0){
                InteruptTimer = InteruptTimer - 50;
                //led_timer0.p_api->periodSet(led_timer0.p_ctrl, InteruptTimer, TIMER_UNIT_PERIOD_MSEC);
                update_number_id(widget->gx_widget_parent, TIME, (int)InteruptTimer);
            }
        break;
        case GX_SIGNAL(BUTINCREASE, GX_EVENT_CLICKED):
            InteruptTimer = InteruptTimer + 50;
            //led_timer0.p_api->periodSet(led_timer0.p_ctrl, InteruptTimer, TIMER_UNIT_PERIOD_MSEC);
            update_number_id(widget->gx_widget_parent, TIME, (int)InteruptTimer);
        break;
        default:
            result = gx_window_event_process(widget, event_ptr);
            break;
    }
    return result;
}

static UINT show_window(GX_WINDOW * p_new, GX_WIDGET * p_widget, bool detach_old)
{
    UINT err = GX_SUCCESS;

    if (!p_new->gx_widget_parent)
    {
        err = gx_widget_attach(p_window_root, p_new);
    }
    else
    {
        err = gx_widget_show(p_new);
    }

    gx_system_focus_claim(p_new);

    GX_WIDGET * p_old = p_widget;
    if (p_old && detach_old)
    {
        if (p_old != (GX_WIDGET*)p_new)
        {
            gx_widget_detach(p_old);
        }
    }

    return err;
}

static void update_text_id(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT string_id)
{
    GX_PROMPT * p_prompt = NULL;

    ssp_err_t err = (ssp_err_t)gx_widget_find(p_widget, (USHORT)id, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET**)&p_prompt);
    if (TX_SUCCESS == err)
    {
        gx_prompt_text_id_set(p_prompt, string_id);
    }
}

static void update_number_id(GX_WIDGET * p_widget, GX_RESOURCE_ID id, INT value)
{
    GX_PROMPT * p_prompt = NULL;

    ssp_err_t err = (ssp_err_t)gx_widget_find(p_widget, (USHORT)id, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET**)&p_prompt);
    if (TX_SUCCESS == err)
    {
        gx_numeric_prompt_value_set(p_prompt, value);
    }
}

void TimeAdd_timer0_callback(timer_callback_args_t * p_args){
    addHunderdms();
    g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_02, onOff);
    onOff = !onOff;
}
