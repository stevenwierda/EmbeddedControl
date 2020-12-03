

#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"

#include "main_thread.h"

static bool button_enabled = false;
bsp_leds_t leds;

extern GX_WINDOW_ROOT * p_window_root;

static UINT show_window(GX_WINDOW * p_new, GX_WIDGET * p_widget, bool detach_old);
static void update_prompt_text_id(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT string_id);
static void update_button_text_id(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT string_id);

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
                update_prompt_text_id(widget->gx_widget_parent, LEDSTATUS, GX_STRING_ID_LED_ON);
                g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_HIGH);
                break;
        case GX_SIGNAL(LEDSWITCH, GX_EVENT_TOGGLE_OFF):
                button_enabled = false;
                update_prompt_text_id(widget->gx_widget_parent, LEDSTATUS, GX_STRING_ID_LED_OFF);
                g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_LOW);
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

static void update_prompt_text_id(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT string_id)
{
    GX_PROMPT * p_prompt = NULL;

    ssp_err_t err = (ssp_err_t)gx_widget_find(p_widget, (USHORT)id, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET**)&p_prompt);
    if (TX_SUCCESS == err)
    {
        gx_prompt_text_id_set(p_prompt, string_id);
    }
}

static void update_button_text_id(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT string_id)
{
    GX_TEXT_BUTTON * p_button = NULL;

    ssp_err_t err = (ssp_err_t)gx_widget_find(p_widget, (USHORT)id, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET**)&p_button);
    if (TX_SUCCESS == err)
    {
        gx_text_button_text_id_set(p_button, string_id);
    }
}
