/*******************************************************************************/
/*  This file is auto-generated by GUIX Studio. Do not edit this file by hand. */
/*  Modifications to this file should only be made by running the GUIX Studio  */
/*  application and re-generating the application. For more information please */
/*  refer to the GUIX Studio user's guide, or visit our web site at            */
/*  www.expresslogic.com.                                                      */
/*                                                                             */
/*  GUIX Studio Revision 5.6.1.0                                               */
/*  Date (dd.mm.yyyy): 29.12.2020   Time (hh:mm): 19:19                        */
/*******************************************************************************/


#ifndef _GUIAPP_SPECIFICATIONS_H_
#define _GUIAPP_SPECIFICATIONS_H_

#include "gx_api.h"

/* Determine if C++ compiler is being used, if so use standard C.              */
#ifdef __cplusplus
extern   "C" {
#endif

/* Define widget ids                                                           */

#define BUTTERUGTIMESET 1
#define BUTYEARPLUS 2
#define BUTHOURMIN 3
#define BUTHOURPLUS 4
#define BUTMINUTEMIN 5
#define BUTMINUTEPLUS 6
#define BUTDAYMIN 7
#define BUTDAYPLUS 8
#define BUTMONTHMIN 9
#define BUTMONTHPLUS 10
#define BUTYEARMIN 11
#define BUTNAMEDAYPLUS 12
#define BUTNAMEDAYMIN 13
#define PRMPTDAYNAME 14
#define PROMPTHOUR 15
#define PROMPTMINUTE 16
#define PROMPTYEAR 17
#define PROMPTMONTH 18
#define PROMPTDAY 19
#define WINDOW_LED1 20
#define BUTDECREASE 21
#define BUTINCREASE 22
#define TIME 23
#define BUTTERUGINTERUPTSET 24
#define windowLED 25
#define butterugLED 26
#define LEDSTATUS 27
#define LEDSWITCH 28
#define WINDOWTIME 29
#define BUTTERUGTIME 30
#define WINDOW_SETTINGS 31
#define BUTTERUGSETTINGS 32
#define BUTSETTIME 33
#define BUTLEDINTERUPT 34
#define WINDOW_MAIN 35
#define BUTSETTINGS 36
#define BUTTIME 37
#define BUTLED 38


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

typedef struct SETTIME_CONTROL_BLOCK_STRUCT
{
    GX_WINDOW_MEMBERS_DECLARE
    GX_TEXT_BUTTON setTime_buttonTerugTimeSet;
    GX_TEXT_BUTTON setTime_buttonYearPlus;
    GX_TEXT_BUTTON setTime_buttonHourMin;
    GX_TEXT_BUTTON setTime_buttonHourPlus;
    GX_TEXT_BUTTON setTime_buttonMinuteMin;
    GX_TEXT_BUTTON setTime_buttonMinutePlus;
    GX_TEXT_BUTTON setTime_buttonDayMin;
    GX_TEXT_BUTTON setTime_buttonDayPlus;
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
    GX_NUMERIC_PROMPT setTime_promptDay;
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
} MAIN_CONTROL_BLOCK;


/* extern statically defined control blocks                                    */

#ifndef GUIX_STUDIO_GENERATED_FILE
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
