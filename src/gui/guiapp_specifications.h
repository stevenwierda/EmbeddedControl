/*******************************************************************************/
/*  This file is auto-generated by GUIX Studio. Do not edit this file by hand. */
/*  Modifications to this file should only be made by running the GUIX Studio  */
/*  application and re-generating the application. For more information please */
/*  refer to the GUIX Studio user's guide, or visit our web site at            */
/*  www.expresslogic.com.                                                      */
/*                                                                             */
/*  GUIX Studio Revision 5.6.1.0                                               */
/*  Date (dd.mm.yyyy): 25. 4.2021   Time (hh:mm): 16:14                        */
/*******************************************************************************/


#ifndef _GUIAPP_SPECIFICATIONS_H_
#define _GUIAPP_SPECIFICATIONS_H_

#include "gx_api.h"

/* Determine if C++ compiler is being used, if so use standard C.              */
#ifdef __cplusplus
extern   "C" {
#endif

/* Define widget ids                                                           */

#define SETONTIME 1
#define chkMonday1 2
#define chkthuesday1 3
#define CHWEDNESDAY1 4
#define CHTHURSDAY1 5
#define CHFRIDAY1 6
#define CHSUNDAY1 7
#define CHSATERDAY1 8
#define BUTAHOURPLUS1 9
#define BUTAHOURMIN1 10
#define BUTAMINPLUS1 11
#define BUTAMINMIN1 12
#define PRMPTHOUR1 13
#define PRMPTMIN1 14
#define BUTPREVIOUSNTERUPTSET 15
#define BUTTERUGINTERUPTSET1 16
#define SETOFFTIME 17
#define chkMonday 18
#define chkthuesday 19
#define CHWEDNESDAY 20
#define CHTHURSDAY 21
#define CHFRIDAY 22
#define CHSUNDAY 23
#define CHSATERDAY 24
#define BUTAHOURPLUS 25
#define BUTAHOURMIN 26
#define BUTAMINPLUS 27
#define BUTAMINMIN 28
#define PRMPTHOUR 29
#define PRMPTMIN 30
#define BUTTERUGINTERUPTSET 31
#define BUTNEXTINTERUPTSET 32
#define BUTBACKALSEL 33
#define ALARM4 34
#define ALARM3 35
#define ALARM2 36
#define ALARM1 37
#define BUTBACKALARMSEL 38
#define BUTALARM 39
#define BUTPWM 40
#define SETPWM 41
#define ACTIVEALARM 42
#define PRMPTSEC 43
#define PRMPTMSEC 44
#define BUTHOURUP 45
#define BUTHOURDOWN 46
#define BUTMINMIN 47
#define BUTMINUP 48
#define BUTSECUP 49
#define BUTSECMIN 50
#define BUTMSECUP 51
#define BUTMSECMIN 52
#define BUTTERUGTIMESET 53
#define BUTYEARPLUS 54
#define BUTHOURMIN 55
#define BUTHOURPLUS 56
#define BUTMINUTEMIN 57
#define BUTMINUTEPLUS 58
#define BUTDATEMIN 59
#define BUTDATEPLUS 60
#define BUTMONTHMIN 61
#define BUTMONTHPLUS 62
#define BUTYEARMIN 63
#define BUTNAMEDAYPLUS 64
#define BUTNAMEDAYMIN 65
#define PRMPTDAYNAME 66
#define PROMPTHOUR 67
#define PROMPTMINUTE 68
#define PROMPTYEAR 69
#define PROMPTMONTH 70
#define PROMPTDATE 71
#define PROMPTSEC 72
#define WINDOW_LED1 73
#define BUTDECREASE 74
#define BUTINCREASE 75
#define TIME 76
#define windowLED 77
#define butterugLED 78
#define LEDSTATUS 79
#define LEDSWITCH 80
#define WINDOWTIME 81
#define BUTTERUGTIME 82
#define PROMPTMSEC 83
#define WINDOW_SETTINGS 84
#define BUTTERUGSETTINGS 85
#define BUTSETTIME 86
#define BUTLEDINTERUPT 87
#define WINDOW_MAIN 88
#define BUTSETTINGS 89
#define BUTTIME 90
#define BUTLED 91
#define BUTSETALARM 92


/* Define animation ids                                                        */

#define GX_NEXT_ANIMATION_ID 1


/* Define user event ids                                                       */

#define GX_NEXT_USER_EVENT_ID GX_FIRST_USER_EVENT


/* Declare properties structures for each utilized widget type                 */

typedef struct GX_STUDIO_WIDGET_STRUCT
{
   GX_CHAR *widget_name;
   USHORT  widget_type;
   USHORT  widget_id;
   #if defined(GX_WIDGET_USER_DATA)
   INT   user_data;
   #endif
   ULONG style;
   ULONG status;
   ULONG control_block_size;
   GX_RESOURCE_ID normal_fill_color_id;
   GX_RESOURCE_ID selected_fill_color_id;
   GX_RESOURCE_ID disabled_fill_color_id;
   UINT (*create_function) (GX_CONST struct GX_STUDIO_WIDGET_STRUCT *, GX_WIDGET *, GX_WIDGET *);
   void (*draw_function) (GX_WIDGET *);
   UINT (*event_function) (GX_WIDGET *, GX_EVENT *);
   GX_RECTANGLE size;
   GX_CONST struct GX_STUDIO_WIDGET_STRUCT *next_widget;
   GX_CONST struct GX_STUDIO_WIDGET_STRUCT *child_widget;
   ULONG control_block_offset;
   GX_CONST void *properties;
} GX_STUDIO_WIDGET;

typedef struct
{
    GX_CONST GX_STUDIO_WIDGET *widget_information;
    GX_WIDGET        *widget;
} GX_STUDIO_WIDGET_ENTRY;

typedef struct
{
    GX_RESOURCE_ID string_id; 
    GX_RESOURCE_ID font_id;
    GX_RESOURCE_ID normal_text_color_id;
    GX_RESOURCE_ID selected_text_color_id;
    GX_RESOURCE_ID disabled_text_color_id;
} GX_TEXT_BUTTON_PROPERTIES;

typedef struct
{
    GX_RESOURCE_ID string_id; 
    GX_RESOURCE_ID font_id;
    GX_RESOURCE_ID normal_text_color_id;
    GX_RESOURCE_ID selected_text_color_id;
    GX_RESOURCE_ID disabled_text_color_id;
    GX_RESOURCE_ID unchecked_pixelmap_id;
    GX_RESOURCE_ID checked_pixelmap_id;
    GX_RESOURCE_ID unchecked_disabled_pixelmap_id;
    GX_RESOURCE_ID checked_disabled_pixelmap_id;
} GX_CHECKBOX_PROPERTIES;

typedef struct
{
    GX_RESOURCE_ID string_id;
    GX_RESOURCE_ID font_id;
    GX_RESOURCE_ID normal_text_color_id;
    GX_RESOURCE_ID selected_text_color_id;
    GX_RESOURCE_ID disabled_text_color_id;
} GX_PROMPT_PROPERTIES;

typedef struct
{
    GX_RESOURCE_ID string_id;
    GX_RESOURCE_ID font_id;
    GX_RESOURCE_ID normal_text_color_id;
    GX_RESOURCE_ID selected_text_color_id;
    GX_RESOURCE_ID disabled_text_color_id;
    VOID (*format_func)(GX_NUMERIC_PROMPT *, INT);
    INT            numeric_prompt_value;
} GX_NUMERIC_PROMPT_PROPERTIES;

typedef struct
{
    GX_RESOURCE_ID wallpaper_id;
} GX_WINDOW_PROPERTIES;


/* Declare top-level control blocks                                            */

typedef struct SETALARMON_CONTROL_BLOCK_STRUCT
{
    GX_WINDOW_MEMBERS_DECLARE
    GX_CHECKBOX setAlarmON_enableAlarm1;
    GX_CHECKBOX setAlarmON_alarmMonday1;
    GX_CHECKBOX setAlarmON_alarmThueseday1;
    GX_CHECKBOX setAlarmON_alarmWednesday1;
    GX_CHECKBOX setAlarmON_alarmThursday1;
    GX_CHECKBOX setAlarmON_alarmFriday1;
    GX_CHECKBOX setAlarmON_alarmSunday1;
    GX_CHECKBOX setAlarmON_alarmSaterday1;
    GX_TEXT_BUTTON setAlarmON_AHourPlus1;
    GX_TEXT_BUTTON setAlarmON_AHourMin1;
    GX_TEXT_BUTTON setAlarmON_AMinPlus1;
    GX_TEXT_BUTTON setAlarmON_AMinMin1;
    GX_NUMERIC_PROMPT setAlarmON_promptHour1;
    GX_NUMERIC_PROMPT setAlarmON_promptMin1;
    GX_TEXT_BUTTON setAlarmON_buttonPrevious;
    GX_PROMPT setAlarmON_PAGENOTE;
    GX_TEXT_BUTTON setAlarmON_buttonTerugSettings_1;
} SETALARMON_CONTROL_BLOCK;

typedef struct SETALARMOFF_CONTROL_BLOCK_STRUCT
{
    GX_WINDOW_MEMBERS_DECLARE
    GX_CHECKBOX setAlarmOFF_enableAlarm;
    GX_CHECKBOX setAlarmOFF_alarmMonday;
    GX_CHECKBOX setAlarmOFF_alarmThueseday;
    GX_CHECKBOX setAlarmOFF_alarmWednesday;
    GX_CHECKBOX setAlarmOFF_alarmThursday;
    GX_CHECKBOX setAlarmOFF_alarmFriday;
    GX_CHECKBOX setAlarmOFF_alarmSunday;
    GX_CHECKBOX setAlarmOFF_alarmSaterday;
    GX_TEXT_BUTTON setAlarmOFF_AHourPlus;
    GX_TEXT_BUTTON setAlarmOFF_AHourMin;
    GX_TEXT_BUTTON setAlarmOFF_AMinPlus;
    GX_TEXT_BUTTON setAlarmOFF_AMinMin;
    GX_NUMERIC_PROMPT setAlarmOFF_promptHour;
    GX_NUMERIC_PROMPT setAlarmOFF_promptMin;
    GX_TEXT_BUTTON setAlarmOFF_buttonTerugSettings;
    GX_TEXT_BUTTON setAlarmOFF_buttonNextSettings_1;
    GX_PROMPT setAlarmOFF_PAGENOTE;
} SETALARMOFF_CONTROL_BLOCK;

typedef struct SELECTALARM_CONTROL_BLOCK_STRUCT
{
    GX_WINDOW_MEMBERS_DECLARE
    GX_TEXT_BUTTON selectAlarm_buttonBack_1;
    GX_TEXT_BUTTON selectAlarm_alarm4;
    GX_TEXT_BUTTON selectAlarm_alarm3;
    GX_TEXT_BUTTON selectAlarm_alarm2;
    GX_TEXT_BUTTON selectAlarm_alarm1;
} SELECTALARM_CONTROL_BLOCK;

typedef struct ALARMSWITCH_CONTROL_BLOCK_STRUCT
{
    GX_WINDOW_MEMBERS_DECLARE
    GX_TEXT_BUTTON AlarmSwitch_buttonBack;
    GX_TEXT_BUTTON AlarmSwitch_buttonAlarm;
    GX_TEXT_BUTTON AlarmSwitch_buttonPWM;
} ALARMSWITCH_CONTROL_BLOCK;

typedef struct SETPWM_CONTROL_BLOCK_STRUCT
{
    GX_WINDOW_MEMBERS_DECLARE
    GX_CHECKBOX SetPWM_activateAlarm;
    GX_NUMERIC_PROMPT SetPWM_promptMin;
    GX_NUMERIC_PROMPT SetPWM_promptHour;
    GX_NUMERIC_PROMPT SetPWM_promptSec;
    GX_NUMERIC_PROMPT SetPWM_promptMsec;
    GX_TEXT_BUTTON SetPWM_buttonHourUp;
    GX_TEXT_BUTTON SetPWM_buttonHourDown;
    GX_TEXT_BUTTON SetPWM_buttonMinMin;
    GX_TEXT_BUTTON SetPWM_buttonMinUp;
    GX_TEXT_BUTTON SetPWM_buttonSecPlus;
    GX_TEXT_BUTTON SetPWM_buttonSecMin;
    GX_TEXT_BUTTON SetPWM_buttonMsecUp;
    GX_TEXT_BUTTON SetPWM_buttonMsecDown;
    GX_TEXT_BUTTON SetPWM_buttonTerugSettings;
} SETPWM_CONTROL_BLOCK;

typedef struct SETTIME_CONTROL_BLOCK_STRUCT
{
    GX_WINDOW_MEMBERS_DECLARE
    GX_TEXT_BUTTON setTime_buttonTerugTimeSet;
    GX_TEXT_BUTTON setTime_buttonYearPlus;
    GX_TEXT_BUTTON setTime_buttonHourMin;
    GX_TEXT_BUTTON setTime_buttonHourPlus;
    GX_TEXT_BUTTON setTime_buttonMinuteMin;
    GX_TEXT_BUTTON setTime_buttonMinutePlus;
    GX_TEXT_BUTTON setTime_buttonDateMin;
    GX_TEXT_BUTTON setTime_buttonDatePlus;
    GX_TEXT_BUTTON setTime_buttonMonthMin;
    GX_TEXT_BUTTON setTime_buttonMonthPlus;
    GX_TEXT_BUTTON setTime_buttonYearMin;
    GX_TEXT_BUTTON setTime_buttonDayNamePlus;
    GX_TEXT_BUTTON setTime_buttonDayNameMin;
    GX_PROMPT setTime_DayPrompt;
    GX_NUMERIC_PROMPT setTime_promptHour;
    GX_NUMERIC_PROMPT setTime_promptMinute;
    GX_NUMERIC_PROMPT setTime_promptYear;
    GX_NUMERIC_PROMPT setTime_promptMonth;
    GX_NUMERIC_PROMPT setTime_promptDate;
    GX_NUMERIC_PROMPT setTime_promptSec;
} SETTIME_CONTROL_BLOCK;

typedef struct SETLEDONEINTERUPT_CONTROL_BLOCK_STRUCT
{
    GX_WINDOW_MEMBERS_DECLARE
    GX_TEXT_BUTTON setLedOneInterupt_buttonDecrease;
    GX_TEXT_BUTTON setLedOneInterupt_buttonIncrease;
    GX_NUMERIC_PROMPT setLedOneInterupt_Time;
    GX_TEXT_BUTTON setLedOneInterupt_buttonTerugSettings;
} SETLEDONEINTERUPT_CONTROL_BLOCK;

typedef struct LEDCONTROLE_CONTROL_BLOCK_STRUCT
{
    GX_WINDOW_MEMBERS_DECLARE
    GX_TEXT_BUTTON LEDControle_buttonTerugLed;
    GX_PROMPT LEDControle_LEDStatus;
    GX_CHECKBOX LEDControle_LEDSwitch;
} LEDCONTROLE_CONTROL_BLOCK;

typedef struct TIME_CONTROL_BLOCK_STRUCT
{
    GX_WINDOW_MEMBERS_DECLARE
    GX_TEXT_BUTTON Time_buttonTerugTime;
    GX_PROMPT Time_prompt_1;
    GX_NUMERIC_PROMPT Time_promptDate;
    GX_NUMERIC_PROMPT Time_promptHour;
    GX_NUMERIC_PROMPT Time_promptMinute;
    GX_NUMERIC_PROMPT Time_promptMonth;
    GX_NUMERIC_PROMPT Time_promptYear;
    GX_NUMERIC_PROMPT Time_promptSec;
    GX_NUMERIC_PROMPT Time_promptMsec;
    GX_PROMPT Time_promptDay2;
} TIME_CONTROL_BLOCK;

typedef struct SETTINGS_CONTROL_BLOCK_STRUCT
{
    GX_WINDOW_MEMBERS_DECLARE
    GX_TEXT_BUTTON Settings_buttonTerugSettings;
    GX_PROMPT Settings_prompt;
    GX_TEXT_BUTTON Settings_buttonSetTime;
    GX_TEXT_BUTTON Settings_buttonInteruptLed;
} SETTINGS_CONTROL_BLOCK;

typedef struct MAIN_CONTROL_BLOCK_STRUCT
{
    GX_WINDOW_MEMBERS_DECLARE
    GX_TEXT_BUTTON Main_ButtonSettings;
    GX_PROMPT Main_WelkomNotiification;
    GX_TEXT_BUTTON Main_ButtonViewTime;
    GX_TEXT_BUTTON Main_ButtonLEDControl;
    GX_TEXT_BUTTON Main_buttonSetAlarm;
} MAIN_CONTROL_BLOCK;


/* extern statically defined control blocks                                    */

#ifndef GUIX_STUDIO_GENERATED_FILE
extern SETALARMON_CONTROL_BLOCK setAlarmON;
extern SETALARMOFF_CONTROL_BLOCK setAlarmOFF;
extern SELECTALARM_CONTROL_BLOCK selectAlarm;
extern ALARMSWITCH_CONTROL_BLOCK AlarmSwitch;
extern SETPWM_CONTROL_BLOCK SetPWM;
extern SETTIME_CONTROL_BLOCK setTime;
extern SETLEDONEINTERUPT_CONTROL_BLOCK setLedOneInterupt;
extern LEDCONTROLE_CONTROL_BLOCK LEDControle;
extern TIME_CONTROL_BLOCK Time;
extern SETTINGS_CONTROL_BLOCK Settings;
extern MAIN_CONTROL_BLOCK Main;
#endif

/* Prototype Synergy display driver specific functions                         */

UINT _gx_synergy_display_driver_setup(GX_DISPLAY *display);
#if defined(GX_TARGET_WIN32) || defined(GX_TARGET_LINUX)
UINT win32_synergy_graphics_driver_setup_565rgb(GX_DISPLAY *display);
#else
VOID _gx_display_driver_565rgb_setup(GX_DISPLAY *display, VOID *aux_data,
                           VOID (*toggle_function)(struct GX_CANVAS_STRUCT *canvas,
                           GX_RECTANGLE *dirty_area));
VOID _gx_dave2d_horizontal_pattern_line_draw_565(GX_DRAW_CONTEXT *context, INT xstart, INT xend, INT ypos);
VOID _gx_dave2d_vertical_pattern_line_draw_565(GX_DRAW_CONTEXT *context, INT ystart, INT yend, INT xpos);
VOID _gx_dave2d_pixel_write_565(GX_DRAW_CONTEXT *context, INT x, INT y, GX_COLOR color);
VOID _gx_dave2d_pixel_blend_565(GX_DRAW_CONTEXT *context, INT x, INT y, GX_COLOR fcolor, GX_UBYTE alpha);
VOID _gx_dave2d_pixelmap_rotate_16bpp(GX_DRAW_CONTEXT *context, INT xpos, INT ypos, GX_PIXELMAP *pixelmap, INT angle, INT rot_cx, INT rot_cy);
VOID _gx_dave2d_drawing_initiate(GX_DISPLAY *display, GX_CANVAS *canvas);
VOID _gx_dave2d_drawing_complete(GX_DISPLAY *display, GX_CANVAS *canvas);
VOID _gx_dave2d_horizontal_line(GX_DRAW_CONTEXT *context,
                             INT xstart, INT xend, INT ypos, INT width, GX_COLOR color);
VOID _gx_dave2d_vertical_line(GX_DRAW_CONTEXT *context,
                             INT ystart, INT yend, INT xpos, INT width, GX_COLOR color);
VOID _gx_dave2d_canvas_copy(GX_CANVAS *canvas, GX_CANVAS *composite);
VOID _gx_dave2d_canvas_blend(GX_CANVAS *canvas, GX_CANVAS *composite);
VOID _gx_dave2d_simple_line_draw(GX_DRAW_CONTEXT *context, INT xstart, INT ystart, INT xend, INT yend);
VOID _gx_dave2d_simple_wide_line(GX_DRAW_CONTEXT *context, INT xstart, INT ystart,
                                INT xend, INT yend);
VOID _gx_dave2d_aliased_line(GX_DRAW_CONTEXT *context, INT xstart, INT ystart, INT xend, INT yend);
VOID _gx_dave2d_aliased_wide_line(GX_DRAW_CONTEXT *context, INT xstart,
                                        INT ystart, INT xend, INT yend);
VOID _gx_dave2d_pixelmap_draw(GX_DRAW_CONTEXT *context, INT xpos, INT ypos, GX_PIXELMAP *pixelmap);
VOID _gx_dave2d_horizontal_pixelmap_line_draw(GX_DRAW_CONTEXT *context, INT xstart, INT xend, INT y, GX_FILL_PIXELMAP_INFO *info);
VOID _gx_dave2d_pixelmap_blend(GX_DRAW_CONTEXT *context, INT xpos, INT ypos,
                                      GX_PIXELMAP *pixelmap, GX_UBYTE alpha);
VOID _gx_dave2d_polygon_draw(GX_DRAW_CONTEXT *context, GX_POINT *vertex, INT num);
VOID _gx_dave2d_polygon_fill(GX_DRAW_CONTEXT *context, GX_POINT *vertex, INT num);
VOID _gx_dave2d_block_move(GX_DRAW_CONTEXT *context,
                          GX_RECTANGLE *block, INT xshift, INT yshift);
VOID _gx_dave2d_alphamap_draw(GX_DRAW_CONTEXT *context, INT xpos, INT ypos, GX_PIXELMAP *pixelmap);
VOID _gx_dave2d_compressed_glyph_8bit_draw(GX_DRAW_CONTEXT *context, GX_RECTANGLE *draw_area, GX_POINT *map_offset, const GX_GLYPH *glyph);
VOID _gx_dave2d_raw_glyph_8bit_draw(GX_DRAW_CONTEXT *context, GX_RECTANGLE *draw_area, GX_POINT *map_offset, const GX_GLYPH *glyph);
VOID _gx_dave2d_compressed_glyph_4bit_draw(GX_DRAW_CONTEXT *context, GX_RECTANGLE *draw_area, GX_POINT *map_offset, const GX_GLYPH *glyph);
VOID _gx_dave2d_raw_glyph_4bit_draw(GX_DRAW_CONTEXT *context, GX_RECTANGLE *draw_area, GX_POINT *map_offset, const GX_GLYPH *glyph);
VOID _gx_dave2d_compressed_glyph_1bit_draw(GX_DRAW_CONTEXT *context, GX_RECTANGLE *draw_area, GX_POINT *map_offset, const GX_GLYPH *glyph);
VOID _gx_dave2d_raw_glyph_1bit_draw(GX_DRAW_CONTEXT *context, GX_RECTANGLE *draw_area, GX_POINT *map_offset, const GX_GLYPH *glyph);
VOID _gx_dave2d_buffer_toggle(GX_CANVAS *canvas, GX_RECTANGLE *dirty);
#if defined(GX_ARC_DRAWING_SUPPORT)
VOID _gx_dave2d_aliased_circle_draw(GX_DRAW_CONTEXT *context, INT xcenter, INT ycenter, UINT r);
VOID _gx_dave2d_circle_draw(GX_DRAW_CONTEXT *context, INT xcenter, INT ycenter, UINT r);
VOID _gx_dave2d_circle_fill(GX_DRAW_CONTEXT *context, INT xcenter, INT ycenter, UINT r);
VOID _gx_dave2d_pie_fill(GX_DRAW_CONTEXT *context, INT xcenter, INT ycenter, UINT r, INT start_angle, INT end_angle);
VOID _gx_dave2d_aliased_arc_draw(GX_DRAW_CONTEXT *context, INT xcenter, INT ycenter, UINT r, INT start_angle, INT end_angle);
VOID _gx_dave2d_arc_draw(GX_DRAW_CONTEXT *context, INT xcenter, INT ycenter, UINT r, INT start_angle, INT end_angle);
VOID _gx_dave2d_arc_fill(GX_DRAW_CONTEXT *context, INT xcenter, INT ycenter, UINT r, INT start_angle, INT end_angle);
VOID _gx_dave2d_aliased_ellipse_draw(GX_DRAW_CONTEXT *context, INT xcenter, INT ycenter, INT a, INT b);
VOID _gx_dave2d_ellipse_draw(GX_DRAW_CONTEXT *context, INT xcenter, INT ycenter, INT a, INT b);
VOID _gx_dave2d_ellipse_fill(GX_DRAW_CONTEXT *context, INT xcenter, INT ycenter, INT a, INT b);
#endif
VOID _gx_synergy_jpeg_draw (GX_DRAW_CONTEXT *p_context, INT x, INT y, GX_PIXELMAP *p_pixelmap);

#endif

/* Declare event process functions, draw functions, and callback functions     */

UINT SELALARM(GX_WINDOW *widget, GX_EVENT *event_ptr);
UINT SELALARMMODE(GX_WINDOW *widget, GX_EVENT *event_ptr);
UINT PWMHandler(GX_WINDOW *widget, GX_EVENT *event_ptr);
UINT timeSetHandler(GX_WINDOW *widget, GX_EVENT *event_ptr);
UINT setLedOneInteruptHandler(GX_WINDOW *widget, GX_EVENT *event_ptr);
UINT LEDWindowHandler(GX_WINDOW *widget, GX_EVENT *event_ptr);
UINT timeWindowHandler(GX_WINDOW *widget, GX_EVENT *event_ptr);
UINT settingsWindowHandler(GX_WINDOW *widget, GX_EVENT *event_ptr);
UINT mainWindowHandler(GX_WINDOW *widget, GX_EVENT *event_ptr);

/* Declare the GX_STUDIO_DISPLAY_INFO structure                                */


typedef struct GX_STUDIO_DISPLAY_INFO_STRUCT 
{
    GX_CONST GX_CHAR *name;
    GX_CONST GX_CHAR *canvas_name;
    GX_CONST GX_THEME **theme_table;
    GX_CONST GX_STRING **language_table;
    USHORT   theme_table_size;
    USHORT   language_table_size;
    UINT     string_table_size;
    UINT     x_resolution;
    UINT     y_resolution;
    GX_DISPLAY *display;
    GX_CANVAS  *canvas;
    GX_WINDOW_ROOT *root_window;
    GX_COLOR   *canvas_memory;
    ULONG      canvas_memory_size;
} GX_STUDIO_DISPLAY_INFO;


/* Declare Studio-generated functions for creating top-level widgets           */

UINT gx_studio_text_button_create(GX_CONST GX_STUDIO_WIDGET *info, GX_WIDGET *control_block, GX_WIDGET *parent);
UINT gx_studio_checkbox_create(GX_CONST GX_STUDIO_WIDGET *info, GX_WIDGET *control_block, GX_WIDGET *parent);
UINT gx_studio_prompt_create(GX_CONST GX_STUDIO_WIDGET *info, GX_WIDGET *control_block, GX_WIDGET *parent);
UINT gx_studio_numeric_prompt_create(GX_CONST GX_STUDIO_WIDGET *info, GX_WIDGET *control_block, GX_WIDGET *parent);
UINT gx_studio_window_create(GX_CONST GX_STUDIO_WIDGET *info, GX_WIDGET *control_block, GX_WIDGET *parent);
GX_WIDGET *gx_studio_widget_create(GX_BYTE *storage, GX_CONST GX_STUDIO_WIDGET *definition, GX_WIDGET *parent);
UINT gx_studio_named_widget_create(char *name, GX_WIDGET *parent, GX_WIDGET **new_widget);
UINT gx_studio_display_configure(USHORT display, UINT (*driver)(GX_DISPLAY *), GX_UBYTE language, USHORT theme, GX_WINDOW_ROOT **return_root);

/* Determine if a C++ compiler is being used.  If so, complete the standard
  C conditional started above.                                                 */
#ifdef __cplusplus
}
#endif

#endif                                       /* sentry                         */
