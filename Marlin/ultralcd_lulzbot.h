/*
 * Modern Interface for the RepRapDiscount Full
 * Graphics Smart Controller (ST7920-based 128x64 LCD)
 *
 * (c) 2017 Aleph Objects, Inc.
 *
 * The code in this page is free software: you can
 * redistribute it and/or modify it under the terms of the GNU
 * General Public License (GNU GPL) as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.  The code is distributed WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU GPL for more details.
 *
 */

#define BUFFER_WIDTH   256
#define BUFFER_HEIGHT  32

#define DDRAM_LINE_1   0x00
#define DDRAM_LINE_2   0x10
#define DDRAM_LINE_3   0x08
#define DDRAM_LINE_4   0x18

//set optimization so ARDUINO optimizes this file
#pragma GCC optimize (3)

typedef const __FlashStringHelper *progmem_str;

void lcd_data(uint8_t data) {
  ST7920_WRITE_BYTE(data);
}

void lcd_cmd(uint8_t data) {
  ST7920_SET_CMD();
  ST7920_WRITE_BYTE(data);
}

void lcd_write_begin() {
  ST7920_SET_DAT();
}

void lcd_write_byte(uint8_t w) {
  lcd_data(w & 0xFF);
}

void lcd_write_word(uint16_t w) {
  lcd_data((w >> 8) & 0xFF);
  lcd_data((w >> 0) & 0xFF);
}

void lcd_write_str(const char *str) {
  while(*str) {
     lcd_write_byte(*str++);
  }
}

void lcd_write_str(const char *str, uint8_t len) {
  while(*str && len--) {
     lcd_write_byte(*str++);
  }
}

void lcd_write_str_P(const char *str) {
  const char *p_str = (const char *)str;
  char c = pgm_read_byte_near(p_str++);
  while(c) {
     lcd_write_byte(c);
     c = pgm_read_byte_near(p_str++);
  }
}

void lcd_write_str(progmem_str str) {
  lcd_write_str_P((const char*)str);
}

void lcd_write_number(uint8_t value, uint8_t digits=3) {
  char  str[7];
  const char *fmt;
  switch(digits) {
    case 6: fmt = PSTR("%6d"); break;
    case 5: fmt = PSTR("%5d"); break;
    case 4: fmt = PSTR("%4d"); break;
    case 3: fmt = PSTR("%3d"); break;
    case 2: fmt = PSTR("%2d"); break;
    case 1: fmt = PSTR("%1d"); break;
  }
  sprintf_P(str,fmt,value);
  lcd_write_str(str);
}

void lcd_clear()          {
  lcd_cmd(0x00000001);
  u8g_Delay(15);                 //delay for CGRAM clear
}

void lcd_display_status(bool display_on, bool cursor_on, bool blink_on) {
  lcd_cmd(0b00001000 |
    (display_on ? 0b0100 : 0) |
    (cursor_on  ? 0b0010 : 0) |
    (blink_on   ? 0b0001 : 0)
  );
}

void lcd_extended_function_set(bool extended, bool graphics) {
  lcd_cmd(  0b00100000 |
    (extended   ? 0b00000100 : 0) |
    (graphics   ? 0b00000010 : 0)
  );
}

void lcd_entry_mode_select(bool ac_increase, bool shift) {
  lcd_cmd(0b00000100 |
    (ac_increase ? 0b00000010 : 0) |
    (shift       ? 0b00000001 : 0)
  );
}

void lcd_scroll_or_addr_select(bool sa) {
  lcd_cmd(0b00100010 |
    (sa   ? 0b000001 : 0)
  );
}

void lcd_set_ddram_address(uint8_t addr) {
  lcd_cmd(0b10000000 | (addr & 0b00111111));
}

void lcd_set_cgram_address(uint8_t addr) {
  lcd_cmd(0b01000000 | (addr & 0b00111111));
}

void lcd_set_gdram_address(uint8_t x, uint8_t y) {
  lcd_cmd(0b10000000 | (y & 0b01111111));
  lcd_cmd(0b10000000 | (x & 0b00001111));
}

void clear_ddram()
{
  lcd_extended_function_set(false, true);
  lcd_set_ddram_address(DDRAM_LINE_1);
  lcd_write_begin();
  for(int i=0; i < 64;i++) {
    lcd_write_byte(' ');
  }
  lcd_extended_function_set(true, true);
}

/* This fills the entire graphics buffer with zeros
 */
void clear_gdram()
{
  for(int y = 0; y < BUFFER_HEIGHT; y++) {
    lcd_extended_function_set(true, true);
    lcd_set_gdram_address(0,y);
    lcd_extended_function_set(false, true);
    lcd_write_begin();
    for(int i = 0; i < (BUFFER_WIDTH / 16); i++) {
      lcd_write_byte(0);
      lcd_write_byte(0);
    }
  }
  lcd_extended_function_set(false, true);
}

void load_cgram_icon(uint16_t addr, const void *data) {
  const uint16_t *p_word = (const uint16_t *)data;
  lcd_set_cgram_address(addr);
  lcd_write_begin();
  for(int i = 0; i < 16; i++) {
    uint16_t word = pgm_read_word_near(p_word++);
    lcd_write_byte((word & 0xFF00) >> 8);
    lcd_write_byte((word & 0x00FF) >> 0);
  }
}

/* Draws an icon in GDRAM. The position is specified in
   as if they were DDRAM coordinates, i.e. the x position
   is [1-8], while the y position is [1-4] */
void draw_gdram_icon(uint8_t x, uint8_t y, const void *data) {
  const uint16_t *p_word = (const uint16_t *)data;
  if(y > 2) {
    // Handle display folding
    y -= 2;
    x += 8;
  }
  x -= 1;
  y -= 1;
  for(int i = 0; i < 16; i++) {
    uint16_t word = pgm_read_word_near(p_word++);
    lcd_extended_function_set(true, true);
    lcd_set_gdram_address(x,i+y*16);
    lcd_extended_function_set(false, true);
    lcd_write_begin();
    lcd_write_byte((word & 0xFF00) >> 8);
    lcd_write_byte((word & 0x00FF) >> 0);
  }
}

/************************** ICON DEFINITIONS *************************************/

#define CGRAM_ICON_1_ADDR 0x00
#define CGRAM_ICON_2_ADDR 0x10
#define CGRAM_ICON_3_ADDR 0x20
#define CGRAM_ICON_4_ADDR 0x30

#define CGRAM_ICON_1_WORD 0x00
#define CGRAM_ICON_2_WORD 0x02
#define CGRAM_ICON_3_WORD 0x04
#define CGRAM_ICON_4_WORD 0x06

#define N_ELEMENTS(a) sizeof(a)/sizeof(a[0])

PROGMEM const uint16_t nozzle_icon[] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000111111110000,
  0b0001111111111000,
  0b0001111111111000,
  0b0001111111111000,
  0b0000111111110000,
  0b0000111111110000,
  0b0001111111111000,
  0b0001111111111000,
  0b0001111111111000,
  0b0000011111100000,
  0b0000001111000000,
  0b0000000110000000,
  0b0000000000000000,
  0b0000000000000000
};

PROGMEM const uint16_t bed_icon[] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0111111111111110,
  0b0111111111111110,
  0b0000000000000000,
  0b0000000000000000
};

PROGMEM const uint16_t heat1_icon[] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0010001000100000,
  0b0001000100010000,
  0b0000100010001000,
  0b0000100010001000,
  0b0001000100010000,
  0b0010001000100000,
  0b0010001000100000,
  0b0001000100010000,
  0b0000100010001000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000
};

PROGMEM const uint16_t heat2_icon[] = {
  0b0000000000000000,
  0b0000000000000000,
  0b0000100010001000,
  0b0000100010001000,
  0b0001000100010000,
  0b0010001000100000,
  0b0010001000100000,
  0b0001000100010000,
  0b0000100010001000,
  0b0000100010001000,
  0b0001000100010000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000
};

PROGMEM const uint16_t fan1_icon[] = {
  0b0000000000000000,
  0b0111111111111110,
  0b0111000000001110,
  0b0110001111000110,
  0b0100001111000010,
  0b0100000110000010,
  0b0101100000011010,
  0b0101110110111010,
  0b0101100000011010,
  0b0100000110000010,
  0b0100001111000010,
  0b0110001111000110,
  0b0111000000001110,
  0b0111111111111110,
  0b0000000000000000,
  0b0000000000000000
};

PROGMEM const uint16_t fan2_icon[] = {
  0b0000000000000000,
  0b0111111111111110,
  0b0111000000001110,
  0b0110010000100110,
  0b0100111001110010,
  0b0101111001111010,
  0b0100110000110010,
  0b0100000110000010,
  0b0100110000110010,
  0b0101111001111010,
  0b0100111001110010,
  0b0110010000100110,
  0b0111000000001110,
  0b0111111111111110,
  0b0000000000000000,
  0b0000000000000000
};

PROGMEM const uint16_t feedrate_icon[] = {
  0b0000000000000000,
  0b0111111000000000,
  0b0100000000000000,
  0b0100000000000000,
  0b0100000000000000,
  0b0111111011111000,
  0b0100000010000100,
  0b0100000010000100,
  0b0100000010000100,
  0b0100000011111000,
  0b0000000010001000,
  0b0000000010000100,
  0b0000000010000100,
  0b0000000010000010,
  0b0000000000000000,
  0b0000000000000000
};

/************************** MAIN SCREEN *************************************/

/* Although this is undocumented, the ST7920 allows the character
 * data buffer (DDRAM) to be used in conjunction with the graphics
 * bitmap buffer (CGRAM). The contents of the graphics buffer is
 * XORed with the data from the character generator. This allows
 * us to make the progess bar out of graphical data (the bar) and
 * text data (the percentage).
 */
void draw_progress_bar(uint8_t value) {
  #if EXTRUDERS == 1
    // If we have only one extruder, draw a long progress bar on the third line
    const int top        = 1;         // Top in pixels
    const int bottom     = 13;        // Bottom in pixels
    const int left       = 8;         // Left edge, in 16-bit words
    const int width      = 5;         // Width of progress bar, in 16-bit words
  #else
    const int top        = 16 + 1;    // Top in pixels
    const int bottom     = 16 + 13;   // Bottom in pixels
    const int left       = 5;         // Left edge, in 16-bit words
    const int width      = 3;         // Width of progress bar, in 16-bit words
  #endif
  const int char_pcnt  = 100/width; // How many percent does each 16-bit word represent?

  // Draw the progress bar as a bitmap in CGRAM

  lcd_extended_function_set(false, true);
  for(int y = top; y <= bottom; y++) {
    lcd_extended_function_set(true, true);
    lcd_set_gdram_address(left,y);
    lcd_extended_function_set(false, true);
    lcd_write_begin();
    for(int x = 0; x < width; x++) {
      uint16_t gfx_word = 0x0000;
      if((x+1)*char_pcnt <= value) {
        // Draw completely filled bytes
        gfx_word = 0xFFFF;
      } else if((x*char_pcnt) < value) {
        // Draw partially filled bytes
        gfx_word = int(0x8000) >> (value % char_pcnt)*16/char_pcnt;
      }
      // Draw the frame around the progress bar
      if(y == top || y == bottom) {
        // Draw top/bottom border
        gfx_word = 0xFFFF;
      } else if (x == (width-1)) {
        // Draw right border
        gfx_word |= 0x0001;
      } else if (x == 0) {
        // Draw left border
        gfx_word |= 0x8000;
      }
      lcd_write_word(gfx_word);
    }
  }

  // Draw the percentage as text in DDRAM

  #if EXTRUDERS == 1
    lcd_set_ddram_address(DDRAM_LINE_3 + 1);
  #else
    lcd_set_ddram_address(DDRAM_LINE_2 + left);
  #endif

  lcd_write_begin();
  if(value > 9) {
    lcd_write_number(value,4);
    lcd_write_str(F("% "));
  } else {
    lcd_write_number(value,3);
    lcd_write_str(F("%  "));
  }
}

static void draw_fan_icon(bool whichIcon) {
  lcd_set_ddram_address(DDRAM_LINE_1+5);
  lcd_write_begin();
  lcd_write_word(whichIcon ? CGRAM_ICON_3_WORD : CGRAM_ICON_4_WORD);
}

static void draw_heat_icon(bool whichIcon, bool heating) {
  #if EXTRUDERS == 1
  lcd_set_ddram_address(DDRAM_LINE_2);
  #else
  lcd_set_ddram_address(DDRAM_LINE_3);
  #endif
  lcd_write_begin();
  if(heating) {
    lcd_write_word(whichIcon ? CGRAM_ICON_1_WORD : CGRAM_ICON_2_WORD);
  } else {
    lcd_write_byte(' ');
    lcd_write_byte(' ');
  }
}

static void drawStaticElements() {
  lcd_extended_function_set(true, true);
  lcd_scroll_or_addr_select(0);
  lcd_extended_function_set(false, true);

  // Load the animated bed and fan icons
  load_cgram_icon(CGRAM_ICON_1_ADDR, heat1_icon);
  load_cgram_icon(CGRAM_ICON_2_ADDR, heat2_icon);
  load_cgram_icon(CGRAM_ICON_3_ADDR, fan1_icon);
  load_cgram_icon(CGRAM_ICON_4_ADDR, fan2_icon);

  // Draw the static icons in GDRAM
  draw_gdram_icon(1,1,nozzle_icon);
  #if EXTRUDERS == 2
  draw_gdram_icon(1,2,nozzle_icon);
  #endif
  draw_gdram_icon(6,2,feedrate_icon);
  draw_gdram_icon(1,2,bed_icon);

  // Draw the initial fan icon
  draw_fan_icon(false);
}

#define FAR(a,b) (((a > b) ? (a-b) : (b-a)) > 1)

static void draw_extruder_1_temp(uint8_t temp, uint8_t target) {
  lcd_set_ddram_address(DDRAM_LINE_1+1);
  lcd_write_begin();
  lcd_write_number(temp);
  if(target && FAR(temp, target)) {
    lcd_write_str(F("\x1A"));
    lcd_write_number(target);
  } else {
    lcd_write_str(F("    "));
  }
}

static void draw_extruder_2_temp(uint8_t temp, uint8_t target) {
  lcd_set_ddram_address(DDRAM_LINE_2+1);
  lcd_write_begin();
  lcd_write_number(temp);
  if(target && FAR(temp, target)) {
    lcd_write_str(F("\x1A"));
    lcd_write_number(target);
  } else {
    lcd_write_str(F("    "));
  }
}

static void draw_bed_temp(uint8_t temp, uint8_t target) {
  #if EXTRUDERS == 1
  lcd_set_ddram_address(DDRAM_LINE_2+1);
  #else
  lcd_set_ddram_address(DDRAM_LINE_3+1);
  #endif
  lcd_write_begin();
  lcd_write_number(temp);
  if(target && FAR(temp, target)) {
    lcd_write_str(F("\x1A"));
    lcd_write_number(target);
  } else {
    lcd_write_str(F("    "));
  }
}

static void draw_fan_speed(uint8_t value) {
  lcd_set_ddram_address(DDRAM_LINE_1+6);
  lcd_write_begin();
  lcd_write_number(value,4);
}

static void draw_print_time(uint32_t elapsed) {
  const uint8_t hrs = elapsed/360;
  const uint8_t min = (elapsed/60)%60;
  char  str[7];
  sprintf_P(str,hrs > 99 ? PSTR("%03d:%02d") : PSTR(" %02d:%02d"),hrs,min);

  lcd_set_ddram_address(DDRAM_LINE_3+5);
  lcd_write_begin();
  lcd_write_str(str);
}

static void draw_feedrate_percentage(uint8_t percentage) {
  // We only have enough room for the feedrate when
  // we have one extruder
  #if EXTRUDERS == 1
    lcd_set_ddram_address(DDRAM_LINE_2+6);
    lcd_write_begin();
    lcd_write_number(percentage,4);
  #endif
}

static void draw_status_message(const char *str) {
  lcd_set_ddram_address(DDRAM_LINE_4);
  lcd_write_begin();
  lcd_write_str(str, 16);
}

static void draw_position(const float x, const float y, const float z) {
  char str[7];
  lcd_set_ddram_address(DDRAM_LINE_4);
  lcd_write_begin();

  dtostrf(x, -4, 0, str);
  lcd_write_byte('X');
  lcd_write_str(str, 4);

  dtostrf(y, -4, 0, str);
  lcd_write_byte('Y');
  lcd_write_str(str, 4);

  dtostrf(z, -5, 1, str);
  lcd_write_byte('Z');
  lcd_write_str(str, 5);
}

static void lcd_onEntry() {
  ST7920_CS();
  lcd_extended_function_set(false, true);
  clear_gdram();
  drawStaticElements();
  lcd_extended_function_set(true, true);
  ST7920_NCS();
}

static void lcd_onExit() {
  ST7920_CS();
  lcd_extended_function_set(false, true);
  lcd_clear();
  clear_gdram();
  lcd_extended_function_set(true, true);
  ST7920_NCS();
}

static void lcd_implementation_status_screen() {
  // Retrieve values from Marlin
  const uint8_t    fan_speed         = ((fanSpeeds[0] + 1) * 100) / 256;
  const uint8_t    percent_done      = card.percentDone();
  const duration_t elapsed           = print_job_timer.duration();
  const uint32_t   seconds_elapsed   = elapsed.value;
  const float      x_pos             = current_position[X_AXIS];
  const float      y_pos             = current_position[Y_AXIS];
  const float      z_pos             = current_position[Z_AXIS];
  const uint8_t    feedrate_perc     = feedrate_percentage;
  const float      bed_temp          = thermalManager.degBed();
  const float      bed_target        = thermalManager.degTargetBed();
  const float      extruder_1_temp   = thermalManager.degHotend(0);
  const float      extruder_1_target = thermalManager.degTargetHotend(0);
  #if EXTRUDERS == 2
  const float      extruder_2_temp   = thermalManager.degHotend(1);
  const float      extruder_2_target = thermalManager.degTargetHotend(1);
  #endif
  const char *     status_string     = lcd_status_message;
  const bool       blink             = lcd_blink();
  const bool       position_known    = axis_known_position[X_AXIS] && axis_known_position[Y_AXIS] && axis_known_position[Z_AXIS];

  static bool      show_position     = false;
  static uint8_t   last_crc = 0;

const  uint8_t crc =
    uint8_t(blink) ^
    uint8_t(feedrate_perc) ^
    uint8_t(fan_speed) ^
    uint8_t(extruder_1_target) ^
#if EXTRUDERS == 2
    uint8_t(extruder_2_target) ^
#endif
    uint8_t(bed_target) ^
    uint8_t((uint16_t(status_string) & 0x00FF) >> 0) ^
    uint8_t((uint16_t(status_string) & 0xFF00) >> 8);

  // Only update unless something important has changed.
  if(last_crc != crc) {
    last_crc = crc;

    // Draw the status screen

    ST7920_CS();

    lcd_extended_function_set(false, true);
    //drawStaticElements();
    draw_extruder_1_temp(extruder_1_temp, extruder_1_target);
    #if EXTRUDERS == 2
    draw_extruder_2_temp(extruder_2_temp, extruder_2_target);
    #endif
    draw_bed_temp(bed_temp, bed_target);
    draw_fan_speed(fan_speed);
    draw_print_time(seconds_elapsed);
    draw_feedrate_percentage(feedrate_perc);

    static const char *  status_string_last      = 0;
    static uint8_t       status_string_countdown = 0;
    static uint8_t       status_string_pos_crc   = 0;

    // Dismiss the status message automatically after 10 blinks
    // if movement is happening on the x axis.
    const uint8_t pos_crc = uint8_t(x_pos) ^ uint8_t(y_pos);
    if(status_string_last != status_string) {
      status_string_countdown = 5;
      status_string_last      = status_string;
    } else if(pos_crc != status_string_pos_crc && status_string_countdown > 0) {
        status_string_countdown--;
    }
    status_string_pos_crc   = pos_crc;

    if(strlen(status_string) && status_string_countdown > 0) {
      draw_status_message(status_string);
      show_position = false;
    } else if(position_known) {
      show_position = true;
    }
    draw_progress_bar(percent_done);


    // Update the fan and bed animations
    if(fan_speed > 0) {
      draw_fan_icon(blink);
    }
    if(bed_target > 0) {
      draw_heat_icon(blink, true);
    } else {
      draw_heat_icon(false, false);
    }

    lcd_extended_function_set(true, true);
    ST7920_NCS();
  } else if(show_position) {
    ST7920_CS();
    lcd_extended_function_set(false, true);
    draw_position(x_pos, y_pos, z_pos);
    lcd_extended_function_set(true, true);
    ST7920_NCS();
  }
}

static void lcd_in_status(bool inStatus) {
  static bool lastInStatus = false;
  if(!lastInStatus && inStatus) {
    lcd_onEntry();
    lastInStatus = true;
  }
  if(lastInStatus && !inStatus) {
    lcd_onExit();
    lastInStatus = false;
  }
}

void lcd_clear_text_buffer() {
  ST7920_CS();
  clear_ddram();
  ST7920_NCS();
}

#pragma GCC reset_options