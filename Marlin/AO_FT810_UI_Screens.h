/****************************************************************************
 *   Written By Mark Pelletier  2018 - Aleph Objects, Inc.                  *
 *   Written By Marcio Teixeira 2018 - Aleph Objects, Inc.                  *
 *                                                                          *
 *   This program is free software: you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by   *
 *   the Free Software Foundation, either version 3 of the License, or      *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   This program is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU General Public License for more details.                           *
 *                                                                          *
 *   To view a copy of the GNU General Public License, go to the following  *
 *   location: <http://www.gnu.org/licenses/>.                              *
 ****************************************************************************/

#define STATUS_MESSAGE_BUFFER_LENGTH 32
char lcd_status_message[STATUS_MESSAGE_BUFFER_LENGTH] = WELCOME_MSG;

static float marlin_x_axis     = 100;
static float marlin_y_axis     = 50;
static float marlin_z_axis     = 170;
static int   marlin_e0_temp    = 25;
static int   marlin_e1_temp    = 25;
static int   marlin_bed_temp   = 25;
static int   marlin_fan_speed  = 25;
static float marlin_x_steps    = 100;
static float marlin_y_steps    = 100;
static float marlin_z_steps    = 100;
static float marlin_e0_steps   = 100;
static float marlin_z_offset   = 0.150;

/**************************** GRID LAYOUT MACROS **************************/

/* The grid layout macros allow buttons to be arranged on a grid so
 * that their locations become independent of the display size. The
 * layout model is similar to that of HTML TABLEs.
 *
 * These macros are meant to be evaluated into constants at compile
 * time, so resolution independence can be as efficient as using
 * hard-coded coordinates.
 */

// Margin defines the margin (in pixels) on each side of a button in
// the layout

#if defined(LCD_800x480)
#define MARGIN_L         5
#define MARGIN_R         5
#define MARGIN_T         5
#define MARGIN_B         5
#else
#define MARGIN_L         3
#define MARGIN_R         3
#define MARGIN_T         3
#define MARGIN_B         3
#endif

// EDGE_R adds some black space on the right edge of the display
// This shifts some of the screens left to visually center them.

#define EDGE_R           0

// GRID_X and GRID_Y computes the positions of the divisions on
// the layout grid.
#if defined(LCD_PORTRAIT)
#define GRID_X(x)        ((x)*(Vsize-EDGE_R)/GRID_COLS)
#define GRID_Y(y)        ((y)*Hsize/GRID_ROWS)
#else
#define GRID_X(x)        ((x)*(Hsize-EDGE_R)/GRID_COLS)
#define GRID_Y(y)        ((y)*Vsize/GRID_ROWS)
#endif

// BTN_X, BTN_Y, BTN_W and BTN_X returns the top-left and width
// and height of a button, taking into account the button margins.

#define BTN_X(x)         (GRID_X(x-1) + MARGIN_L)
#define BTN_Y(y)         (GRID_Y(y-1) + MARGIN_T)
#define BTN_W(w)         (GRID_X(w)   - MARGIN_L - MARGIN_R)
#define BTN_H(h)         (GRID_Y(h)   - MARGIN_T - MARGIN_B)

// Abbreviations for common phrases, to allow a button to be
// defined in one line of source.
#define BTN_POS(x,y)     BTN_X(x), BTN_Y(y)
#define BTN_SIZE(w,h)    BTN_W(w), BTN_H(h)
#define BTN              cmd.Cmd_Draw_Button
#define BTX              cmd.Cmd_Draw_Button_Text
#define BTI              cmd.Cmd_Draw_Button_Icon
#define BTN_TAG(t)       cmd.Cmd_Set_Tag(t);
#define RGB(rgb)         cmd.Cmd_Set_Foreground_Color(rgb);
#define THEME(color)     cmd.Cmd_Set_Foreground_Color(Theme::color);

#define FONT_SML         Theme::font_small
#define FONT_MED         Theme::font_medium
#define FONT_LRG         Theme::font_large

#define MENU_BTN_STYLE   Theme::font_medium, OPT_3D

/************************* MENU SCREEN DECLARATIONS *************************/

class BootScreen : public UIScreen {
  public:
    static void onRefresh();
    static void onIdle();
};

class AboutScreen : public UIScreen {
  private:
    static void playChime();
    static void draw(bool);
  public:
    static void onEntry();
    static void onRefresh();
    static void onTouchStart(uint8_t tag);
};

class StatusScreen : public UIScreen {
  private:
    static void static_axis_position();
    static void static_temperature();
    static void static_progress();
    static void static_interaction_buttons();

    static void dynamic_axis_position();
    static void dynamic_temperature();
    static void dynamic_progress();
    static void dynamic_status_message();

  public:
    static void onRefresh();
    static void onStartup();
    static void onEntry();
    static void onIdle();
    static void onTouchStart(uint8_t tag);
};

class MenuScreen : public UIScreen {
  public:
    static void onRefresh();
    static void onTouchStart(uint8_t tag);
};

class CalibrationScreen : public UIScreen {
  public:
    static void onRefresh();
    static void onIdle();
};

class CalibrationRegistersScreen : public UIScreen {
  public:
    static void onRefresh();
    static void onTouchStart(uint8_t tag);
};

class AdvancedSettingsScreen : public UIScreen {
  public:
    static void onRefresh();
    static void onTouchStart(uint8_t tag);
};

class ValueAdjusters : public UIScreen {
  private:
    static uint8_t increment;
    static void draw_increment_btn(const uint8_t tag, uint8_t decimals);
  protected:
    struct heading_t {
      const char    *label;
      uint8_t        decimals;

      void static_parts() const;
      void dynamic_parts() const;
    };

    struct adjuster_t {
      uint8_t        line;
      const char    *label;
      const char    *units;
      uint32_t       color;
      uint8_t        decimals;

      void static_parts() const;
      void dynamic_parts(float value) const;
    };

    static float getIncrement();
  public:
    static void onTouchStart(uint8_t tag);
};

class MoveAxisScreen : public ValueAdjusters {
  public:
    static void onRefresh();
    static void onTouchHeld(uint8_t tag);
};

class StepsScreen : public ValueAdjusters {
  public:
    static void onRefresh();
    static void onTouchHeld(uint8_t tag);
};

class ZOffsetScreen : public ValueAdjusters {
  public:
    static void onRefresh();
    static void onTouchHeld(uint8_t tag);
};

class TemperatureScreen : public ValueAdjusters {
  public:
    static void onRefresh();
    static void onTouchHeld(uint8_t tag);
};

/******************************* MENU SCREEN TABLE ******************************/

SCREEN_TABLE {
  DECL_SCREEN(BootScreen),
  DECL_SCREEN(AboutScreen),
  DECL_SCREEN(CalibrationScreen),
  DECL_SCREEN(StatusScreen),
  DECL_SCREEN(MenuScreen),
  DECL_SCREEN(MoveAxisScreen),
  DECL_SCREEN(AdvancedSettingsScreen),
  DECL_SCREEN(StepsScreen),
  DECL_SCREEN(ZOffsetScreen),
  DECL_SCREEN(TemperatureScreen),
  DECL_SCREEN(CalibrationRegistersScreen)
};

SCREEN_TABLE_POST

/************************************ MENU THEME ********************************/

namespace Theme {
  const uint32_t olive_darkest = 0x2A2F0A;
  const uint32_t olive_dark    = 0x495212;
  const uint32_t olive_light   = 0x8C9D22;

  const uint32_t background    = 0x707070;
  const uint32_t x_axis        = 0x500000;
  const uint32_t y_axis        = 0x005000;
  const uint32_t z_axis        = 0x000050;
  const uint32_t e_axis        = 0x000000;
  const uint32_t menu_btn      = olive_dark;
  const uint32_t navi_btn      = olive_light;

  const uint32_t toggle_on     = olive_light;
  const uint32_t toggle_off    = olive_darkest;
  const uint32_t disabled      = background;

  // About screen
  const uint32_t about_bg      = olive_dark;
  const uint32_t about_btn     = olive_darkest;

  // Adjustment Screens

  const uint32_t adjust_bg     = olive_dark;
  const uint32_t incr_btn      = olive_darkest;

  // Status screen
  const uint32_t stop_btn      = 0xF02020;
  const uint32_t prnt_btn      = 0x20D020;
  const uint32_t progress      = 0x404040;
  const uint32_t status_msg    = 0x404040;
  const uint32_t fan_speed     = 0x6060D0;
  const uint32_t temp          = 0xD04000;
  const uint32_t axis_label    = 0x404040;

  // Calibration Registers Screen
  const uint32_t transformA    = 0x3010D0;
  const uint32_t transformB    = 0x4010D0;
  const uint32_t transformC    = 0x5010D0;
  const uint32_t transformD    = 0x6010D0;
  const uint32_t transformE    = 0x7010D0;
  const uint32_t transformF    = 0x8010D0;
  const uint32_t transformVal  = 0x104010;

#if defined(LCD_800x480)
  #if defined(LCD_PORTRAIT)
    const int16_t  font_small    = 29;
    const int16_t  font_medium   = 30;
    const int16_t  font_large    = 30;
  #else
    const int16_t  font_small    = 30;
    const int16_t  font_medium   = 30;
    const int16_t  font_large    = 31;
  #endif
  const float      icon_scale    = 1.0;
#else
  #if defined(LCD_PORTRAIT)
  const int16_t  font_small    = 27;
  const int16_t  font_medium   = 28;
  const int16_t  font_large    = 28;
  const float    icon_scale    = 0.7;
  #else
  const int16_t  font_small    = 27;
  const int16_t  font_medium   = 28;
  const int16_t  font_large    = 30;
  const float    icon_scale    = 0.6;
  #endif
#endif
};

/******************************** BOOT SCREEN ****************************/

void BootScreen::onRefresh() {
  CLCD::CommandFifo cmd;
  cmd.Cmd(CMD_DLSTART);
  cmd.Cmd_Clear_Color(Theme::background);
  cmd.Cmd_Clear(1,1,1);
  cmd.Cmd(DL_DISPLAY);
  cmd.Cmd(CMD_SWAP);
  cmd.Cmd_Execute();
  cmd.Cmd_Wait_Until_Idle();

  CLCD::Turn_On_Backlight();
}

void BootScreen::onIdle() {
  GOTO_SCREEN(CalibrationScreen);
}

/******************************** ABOUT SCREEN ****************************/

void AboutScreen::onEntry() {
  draw(false);
  playChime();
  draw(true);
}

void AboutScreen::onRefresh() {
  draw(true);
}

void AboutScreen::draw(bool showOkay) {
  CLCD::CommandFifo cmd;
  cmd.Cmd(CMD_DLSTART);
  cmd.Cmd_Clear_Color(Theme::about_bg);
  cmd.Cmd_Clear(1,1,1);

  #define GRID_COLS 4
  #define GRID_ROWS 6

  BTX( BTN_POS(1,2), BTN_SIZE(4,1), F("Color LCD Interface"),          FONT_LRG);
  BTN_TAG(2)
  BTX( BTN_POS(1,3), BTN_SIZE(4,1), F("(c) 2018 Aleph Objects, Inc."), FONT_LRG);

  if(showOkay) {
    BTN_TAG(1) THEME(about_btn) BTN( BTN_POS(2,5), BTN_SIZE(2,1), F("Okay"), MENU_BTN_STYLE);
  }

  cmd.Cmd(DL_DISPLAY);
  cmd.Cmd(CMD_SWAP);
  cmd.Cmd_Execute();
}

void AboutScreen::onTouchStart(uint8_t tag) {
  switch(tag) {
    case 1:        GOTO_PREVIOUS();                         return;
    case 2:        GOTO_SCREEN(CalibrationRegistersScreen); return;
  }
}

void AboutScreen::playChime() {
  CLCD::Mem_Write8(REG_VOL_SOUND, 0xFF);
  CLCD::Mem_Write16(REG_SOUND, (0x37<< 8) | 0x47); // C8 MIDI note on xylophone 37
  CLCD::Mem_Write8(REG_PLAY, 1);

  delay(800);

  CLCD::Mem_Write16(REG_SOUND, (0x40<< 8) | 0x47); // C8 MIDI note on xylophone 40
  CLCD::Mem_Write8(REG_PLAY, 1);

  delay(800);

  CLCD::Mem_Write16(REG_SOUND, (0x3C<< 8) | 0x47); // C8 MIDI note on xylophone 3C
  CLCD::Mem_Write8(REG_PLAY, 1);

  delay(1200);

  CLCD::Mem_Write16(REG_SOUND, 0);
  CLCD::Mem_Write8(REG_PLAY, 1);
}

/*********************************** STATUS SCREEN ******************************/
#if defined(LCD_PORTRAIT)
  #define GRID_ROWS 9
  #define GRID_COLS 3
#else
  #define GRID_ROWS 8
  #define GRID_COLS 3
#endif

void StatusScreen::static_axis_position() {
  CLCD::CommandFifo cmd;

  #if defined(LCD_PORTRAIT)
    THEME(axis_label) BTN( BTN_POS(1,5), BTN_SIZE(2,1), F(""),  FONT_LRG, OPT_FLAT);
    THEME(axis_label) BTN( BTN_POS(1,6), BTN_SIZE(2,1), F(""),  FONT_LRG, OPT_FLAT);
    THEME(axis_label) BTN( BTN_POS(1,7), BTN_SIZE(2,1), F(""),  FONT_LRG, OPT_FLAT);
                      BTX( BTN_POS(1,5), BTN_SIZE(1,1), F("X"), FONT_SML);
                      BTX( BTN_POS(1,6), BTN_SIZE(1,1), F("Y"), FONT_SML);
                      BTX( BTN_POS(1,7), BTN_SIZE(1,1), F("Z"), FONT_SML);
    THEME(x_axis)     BTN( BTN_POS(2,5), BTN_SIZE(2,1), F(""),  FONT_MED, OPT_FLAT);
    THEME(y_axis)     BTN( BTN_POS(2,6), BTN_SIZE(2,1), F(""),  FONT_MED, OPT_FLAT);
    THEME(z_axis)     BTN( BTN_POS(2,7), BTN_SIZE(2,1), F(""),  FONT_MED, OPT_FLAT);
  #else
    THEME(axis_label) BTN( BTN_POS(1,5), BTN_SIZE(1,2), F(""),  FONT_LRG, OPT_FLAT);
    THEME(axis_label) BTN( BTN_POS(2,5), BTN_SIZE(1,2), F(""),  FONT_LRG, OPT_FLAT);
    THEME(axis_label) BTN( BTN_POS(3,5), BTN_SIZE(1,2), F(""),  FONT_LRG, OPT_FLAT);
                      BTX( BTN_POS(1,5), BTN_SIZE(1,1), F("X"), FONT_SML);
                      BTX( BTN_POS(2,5), BTN_SIZE(1,1), F("Y"), FONT_SML);
                      BTX( BTN_POS(3,5), BTN_SIZE(1,1), F("Z"), FONT_SML);
    THEME(x_axis)     BTN( BTN_POS(1,6), BTN_SIZE(1,1), F(""),  FONT_MED, OPT_FLAT);
    THEME(y_axis)     BTN( BTN_POS(2,6), BTN_SIZE(1,1), F(""),  FONT_MED, OPT_FLAT);
    THEME(z_axis)     BTN( BTN_POS(3,6), BTN_SIZE(1,1), F(""),  FONT_MED, OPT_FLAT);
  #endif
}

void StatusScreen::dynamic_axis_position() {
  CLCD::CommandFifo cmd;

  char x_str[15];
  char y_str[15];
  char z_str[15];

  dtostrf(Marlin_LCD_API::getAxisPosition_mm(Marlin_LCD_API::X), 5, 1, x_str);
  dtostrf(Marlin_LCD_API::getAxisPosition_mm(Marlin_LCD_API::Y), 5, 1, y_str);
  dtostrf(Marlin_LCD_API::getAxisPosition_mm(Marlin_LCD_API::Z), 5, 1, z_str);

  strcat_P(x_str, PSTR(" mm"));
  strcat_P(y_str, PSTR(" mm"));
  strcat_P(z_str, PSTR(" mm"));

  #if defined(LCD_PORTRAIT)
    BTX( BTN_POS(2,5), BTN_SIZE(2,1), x_str, FONT_MED);
    BTX( BTN_POS(2,6), BTN_SIZE(2,1), y_str, FONT_MED);
    BTX( BTN_POS(2,7), BTN_SIZE(2,1), z_str, FONT_MED);
  #else
    BTX( BTN_POS(1,6), BTN_SIZE(1,1), x_str, FONT_MED);
    BTX( BTN_POS(2,6), BTN_SIZE(1,1), y_str, FONT_MED);
    BTX( BTN_POS(3,6), BTN_SIZE(1,1), z_str, FONT_MED);
  #endif

  //#define MARGIN_T 5
}

#if defined(LCD_PORTRAIT)
  #define GRID_COLS 8
#else
  #define GRID_COLS 12
#endif

void StatusScreen::static_temperature() {
  CLCD::CommandFifo cmd;

  BTN_TAG(0)
  #if defined(LCD_PORTRAIT)
    THEME(temp)      BTN( BTN_POS(1,1), BTN_SIZE(4,2), F(""), FONT_SML, OPT_FLAT);
    THEME(temp)      BTN( BTN_POS(1,1), BTN_SIZE(8,1), F(""), FONT_SML, OPT_FLAT);
    THEME(fan_speed) BTN( BTN_POS(5,2), BTN_SIZE(4,1), F(""), FONT_SML, OPT_FLAT);
    THEME(progress)  BTN( BTN_POS(1,3), BTN_SIZE(4,1), F(""), FONT_SML, OPT_FLAT);
    THEME(progress)  BTN( BTN_POS(5,3), BTN_SIZE(4,1), F(""), FONT_SML, OPT_FLAT);
  #else
    THEME(temp)      BTN( BTN_POS(1,1), BTN_SIZE(4,2), F(""), FONT_SML, OPT_FLAT);
    THEME(temp)      BTN( BTN_POS(1,1), BTN_SIZE(8,1), F(""), FONT_SML, OPT_FLAT);
    THEME(fan_speed) BTN( BTN_POS(5,2), BTN_SIZE(4,1), F(""), FONT_SML, OPT_FLAT);
    THEME(progress)  BTN( BTN_POS(9,1), BTN_SIZE(4,1), F(""), FONT_SML, OPT_FLAT);
    THEME(progress)  BTN( BTN_POS(9,2), BTN_SIZE(4,1), F(""), FONT_SML, OPT_FLAT);
  #endif

  // Draw Extruder Bitmap on Extruder Temperature Button

  cmd.Cmd_Bitmap_Source(Extruder_Icon_Info);
  cmd.Cmd_Bitmap_Layout(Extruder_Icon_Info);
  cmd.Cmd_Bitmap_Size  (Extruder_Icon_Info);

  BTN_TAG(0)
  BTI(BTN_POS(1,1), BTN_SIZE(1,1),  Extruder_Icon_Info, Theme::icon_scale);
  BTI(BTN_POS(5,1), BTN_SIZE(1,1),  Extruder_Icon_Info, Theme::icon_scale);

  // Draw Bed Heat Bitmap on Bed Heat Button
  cmd.Cmd_Bitmap_Source(Bed_Heat_Icon_Info);
  cmd.Cmd_Bitmap_Layout(Bed_Heat_Icon_Info);
  cmd.Cmd_Bitmap_Size  (Bed_Heat_Icon_Info);

  BTN_TAG(0)
  BTI(BTN_POS(1,2), BTN_SIZE(1,1), Bed_Heat_Icon_Info, Theme::icon_scale);

  // Draw Fan Percent Bitmap on Bed Heat Button

  cmd.Cmd_Bitmap_Source(Fan_Icon_Info);
  cmd.Cmd_Bitmap_Layout(Fan_Icon_Info);
  cmd.Cmd_Bitmap_Size  (Fan_Icon_Info);

  BTN_TAG(0)
  BTI(BTN_POS(5,2), BTN_SIZE(1,1), Fan_Icon_Info, Theme::icon_scale);
}

#define ROUND(val) uint16_t((val)+0.5)

void StatusScreen::dynamic_temperature() {
  CLCD::CommandFifo cmd;

  char e0_str[15];
  char e1_str[15];
  char bed_str[15];
  char fan_str[15];

  sprintf_P(
    fan_str,
    PSTR("%-3d %%"),
    Marlin_LCD_API::getFan_percent(0)
  );

  sprintf_P(
    bed_str,
    PSTR("%-3d / %-3d  " ),
    ROUND(Marlin_LCD_API::getActualTemp_celsius(0)),
    ROUND(Marlin_LCD_API::getTargetTemp_celsius(0))
  );

  sprintf_P(
    e0_str,
    PSTR("%-3d / %-3d C"),
    ROUND(Marlin_LCD_API::getActualTemp_celsius(1)),
    ROUND(Marlin_LCD_API::getTargetTemp_celsius(1))
  );

  #if EXTRUDERS == 2
    sprintf_P(
      e1_str,
      PSTR("%-3d / %-3d C"),
      ROUND(Marlin_LCD_API::getActualTemp_celsius(2)),
      ROUND(Marlin_LCD_API::getTargetTemp_celsius(2))
    );
  #else
    strcpy_P(
      e1_str,
      PSTR("-")
    );
  #endif

  BTX( BTN_POS(2,1), BTN_SIZE(3,1), e0_str,  FONT_MED);
  BTX( BTN_POS(6,1), BTN_SIZE(3,1), e1_str,  FONT_MED);
  BTX( BTN_POS(2,2), BTN_SIZE(3,1), bed_str, FONT_MED);
  BTX( BTN_POS(6,2), BTN_SIZE(3,1), fan_str, FONT_MED);
}

void StatusScreen::static_progress() {
  CLCD::CommandFifo cmd;

  #if defined(LCD_PORTRAIT)
    THEME(progress)  BTN( BTN_POS(1,3), BTN_SIZE(4,1), F(""), FONT_SML, OPT_FLAT);
    THEME(progress)  BTN( BTN_POS(5,3), BTN_SIZE(4,1), F(""), FONT_SML, OPT_FLAT);
  #else
    THEME(progress)  BTN( BTN_POS(9,1), BTN_SIZE(4,1), F(""), FONT_SML, OPT_FLAT);
    THEME(progress)  BTN( BTN_POS(9,2), BTN_SIZE(4,1), F(""), FONT_SML, OPT_FLAT);
  #endif
}

void StatusScreen::dynamic_progress() {
  CLCD::CommandFifo cmd;

  const uint32_t elapsed = Marlin_LCD_API::getProgress_seconds_elapsed();
  const uint8_t hrs = elapsed/3600;
  const uint8_t min = (elapsed/60)%60;

  char time_str[10];
  char progress_str[10];

  sprintf_P(time_str,     PSTR(" %02d : %02d"), hrs, min);
  sprintf_P(progress_str, PSTR("%-3d %%"),      Marlin_LCD_API::getProgress_percent() );

  #if defined(LCD_PORTRAIT)
    BTN_TAG(0)
    BTX( BTN_POS(1,3), BTN_SIZE(4,1), time_str,     FONT_MED);
    BTX( BTN_POS(5,3), BTN_SIZE(4,1), progress_str, FONT_MED);
  #else
    BTN_TAG(0)
    BTX( BTN_POS(9,1), BTN_SIZE(4,1), time_str,     FONT_MED);
    BTX( BTN_POS(9,2), BTN_SIZE(4,1), progress_str, FONT_MED);
  #endif
}

#define GRID_COLS 4

void StatusScreen::static_interaction_buttons() {
  CLCD::CommandFifo cmd;

  #if defined(LCD_PORTRAIT)
    BTN_TAG(1) THEME(stop_btn) BTN( BTN_POS(1,8), BTN_SIZE(4,1), F("STOP"),  MENU_BTN_STYLE);
    BTN_TAG(3) THEME(navi_btn) BTN( BTN_POS(1,9), BTN_SIZE(2,1), F(""),      MENU_BTN_STYLE);
    BTN_TAG(4) THEME(navi_btn) BTN( BTN_POS(3,9), BTN_SIZE(2,1), F("MENU"),  MENU_BTN_STYLE);
    #else
    BTN_TAG(1) THEME(stop_btn) BTN( BTN_POS(1,7), BTN_SIZE(2,2), F("STOP"),  MENU_BTN_STYLE);
    BTN_TAG(3) THEME(navi_btn) BTN( BTN_POS(3,7), BTN_SIZE(1,2), F(""),      MENU_BTN_STYLE);
    BTN_TAG(4) THEME(navi_btn) BTN( BTN_POS(4,7), BTN_SIZE(1,2), F("MENU"),  MENU_BTN_STYLE);
  #endif

  // Draw Thumb Drive Bitmap on USB Button

  cmd.Cmd_Bitmap_Source(TD_Icon_Info);
  cmd.Cmd_Bitmap_Layout(TD_Icon_Info);
  cmd.Cmd_Bitmap_Size  (TD_Icon_Info);

  BTN_TAG(3)
  #if defined(LCD_PORTRAIT)
    BTI(BTN_POS(1,9), BTN_SIZE(2,1), TD_Icon_Info, Theme::icon_scale);
  #else
    BTI(BTN_POS(3,7), BTN_SIZE(1,2), TD_Icon_Info, Theme::icon_scale);
  #endif
}

#define GRID_COLS 1

void StatusScreen::dynamic_status_message() {
  CLCD::CommandFifo cmd;

  #if defined(LCD_PORTRAIT)
    THEME(status_msg) BTN( BTN_POS(1,4), BTN_SIZE(1,1), lcd_status_message, FONT_LRG, OPT_FLAT);
  #else
    THEME(status_msg) BTN( BTN_POS(1,3), BTN_SIZE(1,2), lcd_status_message, FONT_LRG, OPT_FLAT);
  #endif
}

#if defined(LCD_PORTRAIT)
  #define GRID_COLS 8
#else
  #define GRID_COLS 12
#endif

void StatusScreen::onStartup() {
  // Load the bitmaps for the status screen

  CLCD::Flash_Write_RGB332_Bitmap(TD_Icon_Info.RAMG_addr,       TD_Icon,       sizeof(TD_Icon));
  CLCD::Flash_Write_RGB332_Bitmap(Extruder_Icon_Info.RAMG_addr, Extruder_Icon, sizeof(Extruder_Icon));
  CLCD::Flash_Write_RGB332_Bitmap(Bed_Heat_Icon_Info.RAMG_addr, Bed_Heat_Icon, sizeof(Bed_Heat_Icon));
  CLCD::Flash_Write_RGB332_Bitmap(Fan_Icon_Info.RAMG_addr,      Fan_Icon,      sizeof(Fan_Icon));
}

void StatusScreen::onRefresh() {
  static CLCD::DLCache dlcache;
  CLCD::CommandFifo cmd;
  cmd.Cmd(CMD_DLSTART);

  if(dlcache.hasData()) {
    dlcache.append();
  } else {
    cmd.Cmd_Clear_Color(Theme::background);
    cmd.Cmd_Clear(1,1,1);

    static_temperature();
    static_progress();
    static_axis_position();
    static_interaction_buttons();

    dlcache.store();
  }

  /* Dynamic content, non-cached data follows */

  dynamic_temperature();
  dynamic_progress();
  dynamic_status_message();
  dynamic_axis_position();

  cmd.Cmd(DL_DISPLAY);
  cmd.Cmd(CMD_SWAP);
  cmd.Cmd_Execute();
}

void StatusScreen::onEntry() {
  onRefresh();
}

void StatusScreen::onIdle() {
  onRefresh();
}

void StatusScreen::onTouchStart(uint8_t tag) {
  switch(tag) {
    case 4:  GOTO_SCREEN(MenuScreen); break;
  }
}

/************************************ MENU SCREEN *******************************/

#if defined(LCD_PORTRAIT)
  #define GRID_ROWS 7
  #define GRID_COLS 2
#else
  #define GRID_ROWS 4
  #define GRID_COLS 2
#endif

void MenuScreen::onRefresh() {
  static CLCD::DLCache dlcache;
  CLCD::CommandFifo cmd;
  cmd.Cmd(CMD_DLSTART);

  if(dlcache.hasData()) {
    dlcache.append();
  } else {
    cmd.Cmd_Clear_Color(Theme::background);
    cmd.Cmd_Clear(1,1,1);

    #if defined(LCD_PORTRAIT)
      BTN_TAG(2) THEME(menu_btn) BTN( BTN_POS(1,1), BTN_SIZE(1,1), F("Auto Home"),          MENU_BTN_STYLE);
      BTN_TAG(3) THEME(menu_btn) BTN( BTN_POS(2,1), BTN_SIZE(1,1), F("Move Axis"),          MENU_BTN_STYLE);
      BTN_TAG(4) THEME(menu_btn) BTN( BTN_POS(1,2), BTN_SIZE(2,1), F("Disable Steppers"),   MENU_BTN_STYLE);

      BTN_TAG(5) THEME(menu_btn) BTN( BTN_POS(1,3), BTN_SIZE(2,1), F("Temperature"),        MENU_BTN_STYLE);
      BTN_TAG(6) THEME(menu_btn) BTN( BTN_POS(1,4), BTN_SIZE(2,1), F("Advanced Settings"),  MENU_BTN_STYLE);
      BTN_TAG(8) THEME(menu_btn) BTN( BTN_POS(1,5), BTN_SIZE(2,1), F("Recalibrate Screen"), MENU_BTN_STYLE);
      BTN_TAG(7) THEME(menu_btn) BTN( BTN_POS(1,6), BTN_SIZE(2,1), F("About Firmware"),     MENU_BTN_STYLE);
    #else
      BTN_TAG(2) THEME(menu_btn) BTN( BTN_POS(1,1), BTN_SIZE(1,1), F("Auto Home"),          MENU_BTN_STYLE);
      BTN_TAG(3) THEME(menu_btn) BTN( BTN_POS(1,2), BTN_SIZE(1,1), F("Move Axis"),          MENU_BTN_STYLE);
      BTN_TAG(4) THEME(menu_btn) BTN( BTN_POS(1,3), BTN_SIZE(1,1), F("Disable Steppers"),   MENU_BTN_STYLE);

      BTN_TAG(5) THEME(menu_btn) BTN( BTN_POS(2,1), BTN_SIZE(1,1), F("Temperature"),        MENU_BTN_STYLE);
      BTN_TAG(6) THEME(menu_btn) BTN( BTN_POS(2,2), BTN_SIZE(1,1), F("Configuration"),      MENU_BTN_STYLE);
      BTN_TAG(7) THEME(menu_btn) BTN( BTN_POS(2,3), BTN_SIZE(1,1), F("About Firmware"),     MENU_BTN_STYLE);
    #endif

    #define MARGIN_T 15

    #if defined(LCD_PORTRAIT)
      BTN_TAG(1) THEME(navi_btn) BTN( BTN_POS(1,7), BTN_SIZE(2,1), F("Back"),               MENU_BTN_STYLE);
    #else
      BTN_TAG(1) THEME(navi_btn) BTN( BTN_POS(1,4), BTN_SIZE(2,1), F("Back"),               MENU_BTN_STYLE);
    #endif

    #define MARGIN_T 5

    dlcache.store();
  }

  cmd.Cmd(DL_DISPLAY);
  cmd.Cmd(CMD_SWAP);
  cmd.Cmd_Execute();
}

void MenuScreen::onTouchStart(uint8_t tag) {
  switch(tag) {
    case 1:  GOTO_PREVIOUS();                     break;
    case 3:  GOTO_SCREEN(MoveAxisScreen);         break;
    case 5:  GOTO_SCREEN(TemperatureScreen);      break;
    case 6:  GOTO_SCREEN(AdvancedSettingsScreen); break;
    case 7:  GOTO_SCREEN(AboutScreen);            break;
    case 8:  GOTO_SCREEN(CalibrationScreen);      break;
  }
}

/******************************* CONFIGURATION SCREEN ****************************/

#if defined(LCD_PORTRAIT)
  #define GRID_ROWS 6
  #define GRID_COLS 2
#else
  #define GRID_ROWS 4
  #define GRID_COLS 2
#endif

void AdvancedSettingsScreen::onRefresh() {
  static CLCD::DLCache dlcache;
  CLCD::CommandFifo cmd;
  cmd.Cmd(CMD_DLSTART);

  if(dlcache.hasData()) {
    dlcache.append();
  } else {
    cmd.Cmd_Clear_Color(Theme::background);
    cmd.Cmd_Clear(1,1,1);

    #if defined(LCD_PORTRAIT)
      BTN_TAG(3) THEME(menu_btn) BTN( BTN_POS(1,1), BTN_SIZE(1,2), F("Z Offset "),        MENU_BTN_STYLE);
      BTN_TAG(4) THEME(menu_btn) BTN( BTN_POS(1,3), BTN_SIZE(1,2), F("Steps/mm"),         MENU_BTN_STYLE);

      BTN_TAG(6) THEME(disabled) BTN( BTN_POS(2,1), BTN_SIZE(1,1), F("Velocity "),        MENU_BTN_STYLE);
      BTN_TAG(7) THEME(disabled) BTN( BTN_POS(2,2), BTN_SIZE(1,1), F("Acceleration"),     MENU_BTN_STYLE);
      BTN_TAG(8) THEME(disabled) BTN( BTN_POS(2,3), BTN_SIZE(1,1), F("Jerk"),             MENU_BTN_STYLE);
      BTN_TAG(5) THEME(menu_btn) BTN( BTN_POS(1,5), BTN_SIZE(2,1), F("Restore Failsafe"), MENU_BTN_STYLE);
      BTN_TAG(1) THEME(navi_btn) BTN( BTN_POS(1,6), BTN_SIZE(1,1), F("Save"),             MENU_BTN_STYLE);
      BTN_TAG(2) THEME(navi_btn) BTN( BTN_POS(2,6), BTN_SIZE(1,1), F("Back"),             MENU_BTN_STYLE);
    #else
      BTN_TAG(3) THEME(menu_btn) BTN( BTN_POS(1,1), BTN_SIZE(1,1), F("Z Offset "),        MENU_BTN_STYLE);
      BTN_TAG(4) THEME(menu_btn) BTN( BTN_POS(1,2), BTN_SIZE(1,1), F("Steps/mm"),         MENU_BTN_STYLE);

      BTN_TAG(6) THEME(disabled) BTN( BTN_POS(2,1), BTN_SIZE(1,1), F("Velocity "),        MENU_BTN_STYLE);
      BTN_TAG(7) THEME(disabled) BTN( BTN_POS(2,2), BTN_SIZE(1,1), F("Acceleration"),     MENU_BTN_STYLE);
      BTN_TAG(8) THEME(disabled) BTN( BTN_POS(2,3), BTN_SIZE(1,1), F("Jerk"),             MENU_BTN_STYLE);
      BTN_TAG(5) THEME(menu_btn) BTN( BTN_POS(1,3), BTN_SIZE(1,1), F("Restore Failsafe"), MENU_BTN_STYLE);

      BTN_TAG(1) THEME(navi_btn) BTN( BTN_POS(1,4), BTN_SIZE(1,1), F("Save"),             MENU_BTN_STYLE);
      BTN_TAG(2) THEME(navi_btn) BTN( BTN_POS(2,4), BTN_SIZE(1,1), F("Back"),             MENU_BTN_STYLE);
    #endif

    dlcache.store();
  }

  cmd.Cmd(DL_DISPLAY);
  cmd.Cmd(CMD_SWAP);
  cmd.Cmd_Execute();
}

void AdvancedSettingsScreen::onTouchStart(uint8_t tag) {
  switch(tag) {
    case 1:  GOTO_PREVIOUS();            break;
    case 2:  GOTO_PREVIOUS();            break;
    case 3:  GOTO_SCREEN(ZOffsetScreen); break;
    case 4:  GOTO_SCREEN(StepsScreen);   break;
  }
}

/******************************** CALIBRATION SCREEN ****************************/

#define GRID_COLS 4
#define GRID_ROWS 16

void CalibrationScreen::onRefresh() {
  CLCD::CommandFifo cmd;
  cmd.Cmd(CMD_DLSTART);
  cmd.Cmd_Clear_Color(Theme::background);
  cmd.Cmd_Clear(1,1,1);


  #if defined(LCD_PORTRAIT)
  BTX( BTN_POS(1,8), BTN_SIZE(4,1), F("Touch the dots"), FONT_LRG);
  BTX( BTN_POS(1,9), BTN_SIZE(4,1), F("to calibrate"), FONT_LRG);
  #else
    #if defined(LCD_800x480)
      BTX( BTN_POS(1,1), BTN_SIZE(4,16), F("Touch the dots to calibrate"), FONT_LRG);
    #else
      BTX( BTN_POS(1,1), BTN_SIZE(4,16), F("Touch the dots to calibrate"), FONT_MED);
    #endif
  #endif

  cmd.Cmd(CMD_CALIBRATE);
  cmd.Cmd(DL_DISPLAY);
  cmd.Cmd(CMD_SWAP);
  cmd.Cmd_Execute();
}

void CalibrationScreen::onIdle() {
  if(CLCD::CommandFifo::Cmd_Is_Idle()) {
    GOTO_SCREEN(StatusScreen);
  }
}

/***************************** CALIBRATION REGISTERS SCREEN ****************************/

#define MARGIN_T 5
#define GRID_ROWS 7
#define GRID_COLS 2

void CalibrationRegistersScreen::onRefresh() {
  const uint32_t T_Transform_A = CLCD::Mem_Read32(REG_TOUCH_TRANSFORM_A);
  const uint32_t T_Transform_B = CLCD::Mem_Read32(REG_TOUCH_TRANSFORM_B);
  const uint32_t T_Transform_C = CLCD::Mem_Read32(REG_TOUCH_TRANSFORM_C);
  const uint32_t T_Transform_D = CLCD::Mem_Read32(REG_TOUCH_TRANSFORM_D);
  const uint32_t T_Transform_E = CLCD::Mem_Read32(REG_TOUCH_TRANSFORM_E);
  const uint32_t T_Transform_F = CLCD::Mem_Read32(REG_TOUCH_TRANSFORM_F);
  char b[20];

  CLCD::CommandFifo cmd;
  cmd.Cmd(CMD_DLSTART);
  cmd.Cmd_Clear_Color(Theme::background);
  cmd.Cmd_Clear(1,1,1);

  BTN_TAG(0)
  THEME(transformA) BTN( BTN_POS(1,1), BTN_SIZE(1,1), F("TOUCH TRANSFORM_A"), 28, OPT_3D);
  THEME(transformB) BTN( BTN_POS(1,2), BTN_SIZE(1,1), F("TOUCH TRANSFORM_B"), 28, OPT_3D);
  THEME(transformC) BTN( BTN_POS(1,3), BTN_SIZE(1,1), F("TOUCH TRANSFORM_C"), 28, OPT_3D);
  THEME(transformD) BTN( BTN_POS(1,4), BTN_SIZE(1,1), F("TOUCH TRANSFORM_D"), 28, OPT_3D);
  THEME(transformE) BTN( BTN_POS(1,5), BTN_SIZE(1,1), F("TOUCH TRANSFORM_E"), 28, OPT_3D);
  THEME(transformF) BTN( BTN_POS(1,6), BTN_SIZE(1,1), F("TOUCH TRANSFORM_F"), 28, OPT_3D);

  THEME(transformVal) BTN( BTN_POS(2,1), BTN_SIZE(1,1), F(""), 28, OPT_FLAT);
  THEME(transformVal) BTN( BTN_POS(2,2), BTN_SIZE(1,1), F(""), 28, OPT_FLAT);
  THEME(transformVal) BTN( BTN_POS(2,3), BTN_SIZE(1,1), F(""), 28, OPT_FLAT);
  THEME(transformVal) BTN( BTN_POS(2,4), BTN_SIZE(1,1), F(""), 28, OPT_FLAT);
  THEME(transformVal) BTN( BTN_POS(2,5), BTN_SIZE(1,1), F(""), 28, OPT_FLAT);
  THEME(transformVal) BTN( BTN_POS(2,6), BTN_SIZE(1,1), F(""), 28, OPT_FLAT);

  sprintf(b, "0x%08lX", T_Transform_A); BTX( BTN_POS(2,1), BTN_SIZE(1,1), b, 28);
  sprintf(b, "0x%08lX", T_Transform_B); BTX( BTN_POS(2,2), BTN_SIZE(1,1), b, 28);
  sprintf(b, "0x%08lX", T_Transform_C); BTX( BTN_POS(2,3), BTN_SIZE(1,1), b, 28);
  sprintf(b, "0x%08lX", T_Transform_D); BTX( BTN_POS(2,4), BTN_SIZE(1,1), b, 28);
  sprintf(b, "0x%08lX", T_Transform_E); BTX( BTN_POS(2,5), BTN_SIZE(1,1), b, 28);
  sprintf(b, "0x%08lX", T_Transform_F); BTX( BTN_POS(2,6), BTN_SIZE(1,1), b, 28);

  #define GRID_COLS 3

  BTN_TAG(1) THEME(navi_btn) BTN( BTN_POS(3,7), BTN_SIZE(1,1), F("Back"), MENU_BTN_STYLE);

  cmd.Cmd(DL_DISPLAY);
  cmd.Cmd(CMD_SWAP);
  cmd.Cmd_Execute();
}

void CalibrationRegistersScreen::onTouchStart(uint8_t tag) {
  switch(tag) {
    case 1:        GOTO_PREVIOUS();                 return;
  }
}

/*************************** GENERIC VALUE ADJUSTMENT SCREEN ******************************/

#if defined(LCD_PORTRAIT)
  #define GRID_COLS  6
  #define GRID_ROWS 10
#else
  #define GRID_COLS  9
  #define GRID_ROWS  6
#endif

void ValueAdjusters::draw_increment_btn(const uint8_t tag, uint8_t decimals) {
  CLCD::CommandFifo  cmd;
  const char        *label = PSTR("?");
  uint8_t            pos;

  switch(tag) {
    case 20: label = PSTR("0.001"); pos = decimals - 3; break;
    case 21: label = PSTR( "0.01"); pos = decimals - 2; break;
    case 22: label = PSTR(  "0.1"); pos = decimals - 1; break;
    case 23: label = PSTR(  "1"  ); pos = decimals + 0; break;
    case 24: label = PSTR( "10"  ); pos = decimals + 1; break;
    case 25: label = PSTR("100"  ); pos = decimals + 2; break;
  }

  BTN_TAG(tag)
  switch(pos) {
    #if defined(LCD_PORTRAIT)
      case 0: BTN( BTN_POS(2,8), BTN_SIZE(1,1), progmem_str(label), FONT_MED, OPT_3D); break;
      case 1: BTN( BTN_POS(3,8), BTN_SIZE(1,1), progmem_str(label), FONT_MED, OPT_3D); break;
      case 2: BTN( BTN_POS(4,8), BTN_SIZE(1,1), progmem_str(label), FONT_MED, OPT_3D); break;
    #else
      case 0: BTN( BTN_POS(8,2), BTN_SIZE(2,1), progmem_str(label), FONT_MED, OPT_3D); break;
      case 1: BTN( BTN_POS(8,3), BTN_SIZE(2,1), progmem_str(label), FONT_MED, OPT_3D); break;
      case 2: BTN( BTN_POS(8,4), BTN_SIZE(2,1), progmem_str(label), FONT_MED, OPT_3D); break;
      #endif
  }
}

void ValueAdjusters::heading_t::static_parts() const {
  CLCD::CommandFifo cmd;
  cmd.Cmd_Clear_Color(Theme::adjust_bg);
  cmd.Cmd_Clear(1,1,1);

  // Draw all the buttons in the off state.
  THEME(toggle_off);
  draw_increment_btn(23 - decimals, decimals);
  draw_increment_btn(24 - decimals, decimals);
  draw_increment_btn(25 - decimals, decimals);
  draw_increment_btn(26 - decimals, decimals);

  #if defined(LCD_PORTRAIT)
    BTN_TAG(0) THEME(adjust_bg) BTN( BTN_POS(1,1),  BTN_SIZE(6,1), heading,             FONT_MED, OPT_FLAT);
    BTN_TAG(0) THEME(adjust_bg) BTN( BTN_POS(1,7),  BTN_SIZE(6,1), F("Increment:"),     FONT_SML, OPT_FLAT);
    BTN_TAG(1) THEME(navi_btn)  BTN( BTN_POS(1,10), BTN_SIZE(6,1), F("Back"),           MENU_BTN_STYLE);
  #else
    BTN_TAG(0) THEME(adjust_bg) BTN( BTN_POS(3,1),  BTN_SIZE(4,1), (progmem_str) label, FONT_MED, OPT_FLAT);
    BTN_TAG(0) THEME(adjust_bg) BTN( BTN_POS(8,1),  BTN_SIZE(2,1), F("Increment"),      FONT_MED, OPT_FLAT);
    BTN_TAG(1) THEME(navi_btn)  BTN( BTN_POS(7,6),  BTN_SIZE(3,1), F("Back"),           MENU_BTN_STYLE);
  #endif
}

void ValueAdjusters::heading_t::dynamic_parts() const {
  CLCD::CommandFifo cmd;

  THEME(toggle_on);
  draw_increment_btn(increment, decimals);
}

#if defined(LCD_PORTRAIT)
  #if defined(LCD_800x480)
    #define EDGE_R 20
  #else
    #define EDGE_R 10
  #endif
#else
  #if defined(LCD_800x480)
    #define EDGE_R  40
  #else
    #define EDGE_R  20
  #endif
#endif

void ValueAdjusters::adjuster_t::static_parts() const {
  CLCD::CommandFifo cmd;
  progmem_str   str  = (progmem_str) label;
  const uint8_t tag  = line * 2;

  BTN_TAG( 0     ) RGB(color)       BTN( BTN_POS(3,line+1), BTN_SIZE(2,1), F(""),  FONT_SML, OPT_FLAT);
  BTN_TAG( 0     ) THEME(adjust_bg) BTN( BTN_POS(1,line+1), BTN_SIZE(2,1), str,    FONT_SML, OPT_FLAT);
  BTN_TAG(tag    ) THEME(incr_btn)  BTN( BTN_POS(5,line+1), BTN_SIZE(1,1), F("-"), FONT_MED, OPT_3D);
  BTN_TAG(tag + 1) THEME(incr_btn)  BTN( BTN_POS(6,line+1), BTN_SIZE(1,1), F("+"), FONT_MED, OPT_3D);

  increment = 23 - decimals;
}

void ValueAdjusters::adjuster_t::dynamic_parts(float value) const {
  CLCD::CommandFifo cmd;
  char b[32];

  dtostrf(value, 5, decimals, b);
  strcat_P(b, PSTR(" "));
  strcat_P(b, (const char*) units);

  BTN_TAG(0)
  BTX( BTN_POS(3,line+1), BTN_SIZE(2,1), b, FONT_SML);
}

void ValueAdjusters::onTouchStart(uint8_t tag) {
  switch(tag) {
    case 1:         GOTO_PREVIOUS();                 return;
    case 2  ... 9:  current_screen.onTouchHeld(tag); return;
    case 20 ... 25: increment = tag;                 break;
  }
  current_screen.onRefresh();
}

float ValueAdjusters::getIncrement() {
  switch(increment) {
    case 20: return   0.001;
    case 21: return   0.01;
    case 22: return   0.1;
    case 23: return   1.0;
    case 24: return  10.0;
    case 25: return 100.0;
  }
}

uint8_t ValueAdjusters::increment = 20;

#define EDGE_R 0

/******************************** MOVE AXIS SCREEN ******************************/

void MoveAxisScreen::onRefresh() {
  static CLCD::DLCache dlcache;
  CLCD::CommandFifo cmd;
  cmd.Cmd(CMD_DLSTART);

  /*                    #  Label:              Units:      Color:         Precision: */
  const heading_t  a = {   PSTR("Move Axis"),                             1          };
  const adjuster_t b = {1, PSTR("X:"),         PSTR("mm"), Theme::x_axis, 1          };
  const adjuster_t c = {2, PSTR("Y:"),         PSTR("mm"), Theme::y_axis, 1          };
  const adjuster_t d = {3, PSTR("Z:"),         PSTR("mm"), Theme::z_axis, 1          };

  if(dlcache.hasData()) {
    dlcache.append();
  } else {
    a.static_parts();
    b.static_parts();
    c.static_parts();
    d.static_parts();
    dlcache.store();
  }
  a.dynamic_parts();
  b.dynamic_parts(marlin_x_axis);
  c.dynamic_parts(marlin_y_axis);
  d.dynamic_parts(marlin_z_axis);

  cmd.Cmd(DL_DISPLAY);
  cmd.Cmd(CMD_SWAP);
  cmd.Cmd_Execute();
}

void MoveAxisScreen::onTouchHeld(uint8_t tag) {
  switch(tag) {
    case 2:  marlin_x_axis -= getIncrement(); break;
    case 3:  marlin_x_axis += getIncrement(); break;
    case 4:  marlin_y_axis -= getIncrement(); break;
    case 5:  marlin_y_axis += getIncrement(); break;
    case 6:  marlin_z_axis -= getIncrement(); break;
    case 7:  marlin_z_axis += getIncrement(); break;
  }
  onRefresh();
}

/******************************* TEMPERATURE SCREEN ******************************/

void TemperatureScreen::onRefresh() {
  static CLCD::DLCache dlcache;
  CLCD::CommandFifo cmd;
  cmd.Cmd(CMD_DLSTART);

  /*                    #  Label:              Units:     Color:            Precision: */
  const heading_t  a = {   PSTR("Nozzle:"),                                 0          };
  const adjuster_t b = {1, PSTR("Nozzle:"),    PSTR("C"), Theme::temp,      0          };
  const adjuster_t c = {2, PSTR("Bed:"),       PSTR("C"), Theme::temp,      0          };
  const adjuster_t d = {3, PSTR("Fan Speed:"), PSTR("%"), Theme::fan_speed, 0          };

  if(dlcache.hasData()) {
    dlcache.append();
  } else {
    a.static_parts();
    b.static_parts();
    c.static_parts();
    d.static_parts();
    dlcache.store();
  }
  a.dynamic_parts();
  b.dynamic_parts(marlin_e0_temp);
  c.dynamic_parts(marlin_bed_temp);
  d.dynamic_parts(marlin_fan_speed);

  cmd.Cmd(DL_DISPLAY);
  cmd.Cmd(CMD_SWAP);
  cmd.Cmd_Execute();
}

void TemperatureScreen::onTouchHeld(uint8_t tag) {
  switch(tag) {
    case 2:  marlin_e0_temp   -= getIncrement(); break;
    case 3:  marlin_e0_temp   += getIncrement(); break;
    case 4:  marlin_bed_temp  -= getIncrement(); break;
    case 5:  marlin_bed_temp  += getIncrement(); break;
    case 6:  marlin_fan_speed -= getIncrement(); break;
    case 7:  marlin_fan_speed += getIncrement(); break;
  }
  onRefresh();
}

/******************************* STEPS SCREEN ******************************/

void StepsScreen::onRefresh() {
  static CLCD::DLCache dlcache;
  CLCD::CommandFifo cmd;
  cmd.Cmd(CMD_DLSTART);

  /*                    #  Label:      Units:             Color:            Precision: */
  const heading_t  a = {               PSTR("Steps/mm"),                    0};
  const adjuster_t b = {1, PSTR("X:"), PSTR(""),          Theme::x_axis,    0};
  const adjuster_t c = {2, PSTR("Y:"), PSTR(""),          Theme::y_axis,    0};
  const adjuster_t d = {3, PSTR("Z:"), PSTR(""),          Theme::z_axis,    0};
  const adjuster_t e = {4, PSTR("E:"), PSTR(""),          Theme::z_axis,    0};

  if(dlcache.hasData()) {
    dlcache.append();
  } else {
    a.static_parts();
    b.static_parts();
    c.static_parts();
    d.static_parts();
    e.static_parts();
    dlcache.store();
  }
  a.dynamic_parts();
  b.dynamic_parts(marlin_x_steps );
  c.dynamic_parts(marlin_y_steps );
  d.dynamic_parts(marlin_z_steps );
  e.dynamic_parts(marlin_e0_steps);

  cmd.Cmd(DL_DISPLAY);
  cmd.Cmd(CMD_SWAP);
  cmd.Cmd_Execute();
}

void StepsScreen::onTouchHeld(uint8_t tag) {
  switch(tag) {
    case 2:  marlin_x_steps   -= getIncrement(); break;
    case 3:  marlin_x_steps   += getIncrement(); break;
    case 4:  marlin_y_steps   -= getIncrement(); break;
    case 5:  marlin_y_steps   += getIncrement(); break;
    case 6:  marlin_z_steps   -= getIncrement(); break;
    case 7:  marlin_z_steps   += getIncrement(); break;
    case 8:  marlin_e0_steps  -= getIncrement(); break;
    case 9:  marlin_e0_steps  += getIncrement(); break;
  }
  onRefresh();
}

/***************************** Z-OFFSET SCREEN ***************************/

void ZOffsetScreen::onRefresh() {
  static CLCD::DLCache dlcache;
  CLCD::CommandFifo cmd;
  cmd.Cmd(CMD_DLSTART);

  /*                    #  Label:             Units:      Color:            Precision: */
  const heading_t  a = {   PSTR("Z Offset"),                                3          };
  const adjuster_t b = {2, PSTR("Z Offset:"), PSTR("mm"), Theme::z_axis,    3          };

  if(dlcache.hasData()) {
    dlcache.append();
  } else {
    a.static_parts();
    b.static_parts();
    dlcache.store();
  }
  a.dynamic_parts();
  b.dynamic_parts(marlin_z_offset);

  cmd.Cmd(DL_DISPLAY);
  cmd.Cmd(CMD_SWAP);
  cmd.Cmd_Execute();
}

void ZOffsetScreen::onTouchHeld(uint8_t tag) {
  switch(tag) {
    case 4:  marlin_z_offset -= getIncrement(); break;
    case 5:  marlin_z_offset += getIncrement(); break;
  }
  onRefresh();
}

/******************************** MAIN EVENT HANDLER *******************************/

#define DISPLAY_UPDATE_INTERVAL 1000

void lcd_init() {
  CLCD::Init();
  current_screen.start();
}

void lcd_update() {
  const  uint8_t  NONE    = 0xFF;
  const  uint8_t  IGNORE  = 0xFE;
  static uint8_t  pressed = NONE;
  static uint32_t last_repeat = 0;
  static uint32_t last_update = 0;

  if(millis() - last_update > DISPLAY_UPDATE_INTERVAL) {
    current_screen.onIdle();
    last_update = millis();
  }

  // If the LCD is processing commands, don't check
  // for tags since they may be changing and could
  // cause spurious events.
  if(!CLCD::CommandFifo::Cmd_Is_Idle()) {
    return;
  }

  CLCD::Test_Pulse();

  const uint8_t tag = CLCD::Get_Tag();

  if(tag == 0) {
    // When the user lifts their finger, activate the onTouchEnd handler,
    // except when pressed is IGNORE.
    if(pressed == IGNORE) {
      pressed = NONE;
    }
    else if(pressed != NONE) {
      current_screen.onTouchEnd(pressed);
      pressed = NONE;
      #if defined(UI_FRAMEWORK_DEBUG)
        #if defined (SERIAL_PROTOCOLLNPAIR)
          SERIAL_PROTOCOLLNPAIR("Touch end: ", tag);
        #else
          Serial.print("Touch end: ");
          Serial.println(tag);
        #endif
      #endif
    }
  }
  else if(pressed == NONE) {
    // When the user taps on a button, activate the onTouchStart handler
    const uint8_t lastScreen = current_screen.getScreen();
    current_screen.onTouchStart(tag);
    last_repeat = millis();

    #if defined(UI_FRAMEWORK_DEBUG)
      #if defined (SERIAL_PROTOCOLLNPAIR)
        SERIAL_PROTOCOLLNPAIR("Touch start: ", tag);
      #else
        Serial.print("Touch start: ");
        Serial.println(tag);
      #endif
    #endif

    if(lastScreen != current_screen.getScreen()) {
      // In the case in which a touch event triggered a new screen to be
      // drawn, we don't issue a touchEnd since it would be sent to the
      // wrong screen.
      pressed = IGNORE;
    } else {
      pressed = tag;
    }
  } else if(tag == pressed) {
    // The user is holding down a button.
    if((millis() - last_repeat) > 250) {
      current_screen.onTouchHeld(tag);
      last_repeat = millis();
    }
  }
}

inline bool lcd_hasstatus() { return true; }

void lcd_setstatus(const char * const message, const bool persist = false) {
  strncpy(lcd_status_message, message, STATUS_MESSAGE_BUFFER_LENGTH);
}

void lcd_setstatusPGM(const char * const message, int8_t level = 0) {
  strncpy_P(lcd_status_message, message, STATUS_MESSAGE_BUFFER_LENGTH);
}

void lcd_status_printf_P(const uint8_t level, const char * const fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vsnprintf_P(lcd_status_message, STATUS_MESSAGE_BUFFER_LENGTH, fmt, args);
  va_end(args);
}

void lcd_setalertstatusPGM(const char * const message) {
  lcd_setstatusPGM(message, 1);
  GOTO_SCREEN(StatusScreen);
}

void lcd_buttons_update() {}
inline void lcd_reset_alert_level() {}
inline bool lcd_detected() { return true; }
inline void lcd_refresh() {current_screen.onIdle();}
