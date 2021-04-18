#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"
#include "main_thread.h"
#include "time.h"

static bool button_enabled = false;
bool onOff;
int weekday;
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
        sync_time();
        show_window((GX_WINDOW*)&Time, (GX_WIDGET*)widget, true);
        break;
    case GX_SIGNAL(BUTLED, GX_EVENT_CLICKED):
        show_window((GX_WINDOW*)&LEDControle, (GX_WIDGET*)widget, true);
        break;
    case GX_SIGNAL(BUTSETALARM, GX_EVENT_CLICKED):
        show_window((GX_WINDOW*)&AlarmSwitch, (GX_WIDGET*)widget, true);
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
    gx_system_timer_start(widget, 100, 10, 50);
    update_number_id(widget->gx_widget_parent, PROMPTYEAR, getYear());
    update_number_id(widget->gx_widget_parent, PROMPTMONTH, getMonth());
    update_number_id(widget->gx_widget_parent, PROMPTDATE, getDate());
    update_number_id(widget->gx_widget_parent, PROMPTHOUR, getHour());
    update_number_id(widget->gx_widget_parent, PROMPTMINUTE, getMin());
    update_number_id(widget->gx_widget_parent, PROMPTSEC, getSec());
    //update_number_id(widget->gx_widget_parent, PROMPTMSEC, getMsec());
    weekday = getWeekday();
    if(weekday == 1){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_MONDAY);
    }
    else if(weekday == 2){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_THUSEDAY);
    }
    else if(weekday == 3){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_WEDNESDAY);
    }
    else if(weekday == 4){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_THURSTDAY);
    }
    else if(weekday == 5){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_FRIDAY);
    }
    else if(weekday == 6){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_SATERDAY);
    }
    else if(weekday == 7){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_SUNDAY);
    }

    switch (event_ptr->gx_event_type){
        case GX_SIGNAL(BUTTERUGTIME, GX_EVENT_CLICKED):
            show_window((GX_WINDOW*)&Main, (GX_WIDGET*)widget, true);
            break;
        case GX_EVENT_TIMER:
            update_number_id(widget->gx_widget_parent, PROMPTYEAR, getYear());
            update_number_id(widget->gx_widget_parent, PROMPTMONTH, getMonth());
            update_number_id(widget->gx_widget_parent, PROMPTDATE, getDate());
            update_number_id(widget->gx_widget_parent, PROMPTHOUR, getHour());
            update_number_id(widget->gx_widget_parent, PROMPTMINUTE, getMin());
            update_number_id(widget->gx_widget_parent, PROMPTSEC, getSec());
            update_number_id(widget->gx_widget_parent, PROMPTMSEC, getMsec());
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
                sync_time();
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
    //gx_system_timer_start(widget, 100, 10, 50);
    weekday = getWeekday();
    if(weekday == 1){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_MONDAY);
    }
    else if(weekday == 2){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_THUSEDAY);
    }
    else if(weekday == 3){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_WEDNESDAY);
    }
    else if(weekday == 4){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_THURSTDAY);
    }
    else if(weekday == 5){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_FRIDAY);
    }
    else if(weekday == 6){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_SATERDAY);
    }
    else if(weekday == 7){
        update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_SUNDAY);
    }
    update_number_id(widget->gx_widget_parent, PROMPTYEAR, getYear());
    update_number_id(widget->gx_widget_parent, PROMPTMONTH, getMonth());
    update_number_id(widget->gx_widget_parent, PROMPTDATE, getDate());
    update_number_id(widget->gx_widget_parent, PROMPTHOUR, getHour());
    update_number_id(widget->gx_widget_parent, PROMPTMINUTE, getMin());
    update_number_id(widget->gx_widget_parent, PROMPTSEC, getSec());


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
        case GX_SIGNAL(BUTDATEPLUS, GX_EVENT_CLICKED):
            changeDayUp();
            update_number_id(widget->gx_widget_parent, PROMPTDATE, getDate());
            update_number_id(widget->gx_widget_parent, PROMPTMONTH, getMonth());    //also get the month so it displays it when the date changes
            break;
        case GX_SIGNAL(BUTDATEMIN, GX_EVENT_CLICKED):
            changeDayDown();
            update_number_id(widget->gx_widget_parent, PROMPTDATE, getDate());
            update_number_id(widget->gx_widget_parent, PROMPTMONTH, getMonth());    //also get the month so it displays it when the date changes
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
            changeWeekdayUp();
            weekday  = getWeekday();
            if(weekday  == 1){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_MONDAY);
            }
            else if(weekday  == 2){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_THUSEDAY);
            }
            else if(weekday  == 3){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_WEDNESDAY);
            }
            else if(weekday  == 4){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_THURSTDAY);
            }
            else if(weekday  == 5){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_FRIDAY);
            }
            else if(weekday  == 6){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_SATERDAY);
            }
            else if(weekday  == 7){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_SUNDAY);
            }
            break;
        case GX_SIGNAL(BUTNAMEDAYMIN, GX_EVENT_CLICKED):
            changeWeekdayDown();
            weekday  = getWeekday();
            if(weekday  == 1){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_MONDAY);
            }
            else if(weekday  == 2){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_THUSEDAY);
            }
            else if(weekday  == 3){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_WEDNESDAY);
            }
            else if(weekday  == 4){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_THURSTDAY);
            }
            else if(weekday  == 5){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_FRIDAY);
            }
            else if(weekday  == 6){
                update_text_id(widget->gx_widget_parent, PRMPTDAYNAME, GX_STRING_ID_SATERDAY);
            }
            else if(weekday  == 7){
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

UINT SELALARMMODE(GX_WINDOW *widget, GX_EVENT *event_ptr)
{
    UINT result = gx_window_event_process(widget, event_ptr);

    switch (event_ptr->gx_event_type){
        case GX_SIGNAL(BUTBACKALARMSEL, GX_EVENT_CLICKED):
            show_window((GX_WINDOW*)&Main, (GX_WIDGET*)widget, true);
            break;
        case GX_SIGNAL(BUTALARM, GX_EVENT_CLICKED):
            show_window((GX_WINDOW*)&setAlarm, (GX_WIDGET*)widget, true);
            break;
        case GX_SIGNAL(BUTPWM, GX_EVENT_CLICKED):
            show_window((GX_WINDOW*)&SetPWM, (GX_WIDGET*)widget, true);
            break;
        default:
            break;
    }

    return result;
}

UINT PWMHandler(GX_WINDOW *widget, GX_EVENT *event_ptr){
    UINT result = gx_window_event_process(widget, event_ptr);
    gx_system_timer_start(widget, 100, 10, 50);
    update_number_id(widget->gx_widget_parent, PRMPTHOUR, intervalHour());
    update_number_id(widget->gx_widget_parent, PRMPTMIN, intervalMin());
    update_number_id(widget->gx_widget_parent, PRMPTSEC, intervalSec());
    update_number_id(widget->gx_widget_parent, PRMPTMSEC, intervalMsec());

    switch (event_ptr->gx_event_type){
        case GX_SIGNAL(BUTTERUGINTERUPTSET, GX_EVENT_CLICKED):
            show_window((GX_WINDOW*)&AlarmSwitch, (GX_WIDGET*)widget, true);
            break;
        case GX_SIGNAL(BUTHOURUP, GX_EVENT_CLICKED):
            setIntervalHourPlus();
            break;
        case GX_SIGNAL(BUTHOURMIN, GX_EVENT_CLICKED):
            setIntervalHourMin();
            break;
        case GX_SIGNAL(BUTMINUP, GX_EVENT_CLICKED):
            setIntervalMinPlus();
            break;
        case GX_SIGNAL(BUTMINMIN, GX_EVENT_CLICKED):
            setIntervalMinMin();
            break;
        case GX_SIGNAL(BUTSECUP, GX_EVENT_CLICKED):
            setIntervalSecPlus();
            break;
        case GX_SIGNAL(BUTSECMIN, GX_EVENT_CLICKED):
            setIntervalSecMin();
            break;
        case GX_SIGNAL(BUTMSECUP, GX_EVENT_CLICKED):
            setIntervalMsecPlus();
            break;
        case GX_SIGNAL(BUTMSECMIN, GX_EVENT_CLICKED):
            setIntervalMsecMin();
            break;
        case GX_SIGNAL(ACTIVEALARM, GX_EVENT_TOGGLE_ON):
            activatePWM1();
            break;
        case GX_SIGNAL(ACTIVEALARM, GX_EVENT_TOGGLE_OFF):
            deactivatePWM();
            break;
        case GX_EVENT_TIMER:
            update_number_id(widget->gx_widget_parent, PRMPTHOUR, intervalHour());
            update_number_id(widget->gx_widget_parent, PRMPTMIN, intervalMin());
            update_number_id(widget->gx_widget_parent, PRMPTSEC, intervalSec());
            update_number_id(widget->gx_widget_parent, PRMPTMSEC, intervalMsec());
        break;
        default:
            result = gx_window_event_process(widget, event_ptr);
            break;
    }
    return result;

}

UINT SELALARM(GX_WINDOW *widget, GX_EVENT *event_ptr){
    UINT result = gx_window_event_process(widget, event_ptr);
    switch (event_ptr->gx_event_type){
        case GX_SIGNAL(BUTBACKALSEL, GX_EVENT_CLICKED):
            show_window((GX_WINDOW*)&Main, (GX_WIDGET*)widget, true);
            break;
        case GX_SIGNAL(ALARM1, GX_EVENT_CLICKED):
            setAlarmsel(1);
            show_window((GX_WINDOW*)&AlarmSwitch, (GX_WIDGET*)widget, true);
            break;
        case GX_SIGNAL(ALARM2, GX_EVENT_CLICKED):
            setAlarmsel(2);
            show_window((GX_WINDOW*)&AlarmSwitch, (GX_WIDGET*)widget, true);
            break;
        case GX_SIGNAL(ALARM3, GX_EVENT_CLICKED):
            setAlarmsel(3);
            show_window((GX_WINDOW*)&AlarmSwitch, (GX_WIDGET*)widget, true);
            break;
        case GX_SIGNAL(ALARM4, GX_EVENT_CLICKED):
            setAlarmsel(4);
            show_window((GX_WINDOW*)&AlarmSwitch, (GX_WIDGET*)widget, true);
            break;
        default:
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
