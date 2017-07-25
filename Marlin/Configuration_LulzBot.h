#ifndef CONFIGURATION_LULZBOT
#define CONFIGURATION_LULZBOT

/*

  If compiling from the command line:

      build-all-taz-toolheads.sh

   Else, if compiling using Arduino IDE, edit lines 38 and 39.

   Printer Model Choices:
      Gladiola_Mini            // Lulzbot Mini  (Gladiola)
      Huerfano_Mini            // Lulzbot Mini  (Huerfano)
      Gladiola_GLCD            // Lulzbot Mini  (Gladiola w/ LCD)
      Oliveoil_TAZ_6           // Lulzbot TAZ 6 (Olive Oil)
      Huerfano_TAZ_7           // Lulzbot TAZ 7 (Huerfano)

   Mini Toolhead Choices:
      Gladiola_SingleExtruder  // Standard Single Extruder (Gladiola)
      Albatross_Flexystruder   // Flexystruder (Albatross)
      Heather_Aero             // Titan AERO (Heather)

   TAZ Toolhead Choices:
      Oliveoil_SingleExtruder  // Standard Single Extruder (TAZ Olive)
      Kanyu_Flexystruder       // Flexystruder (Kanyu)
      Opah_Moarstruder         // Moarstruder (Opah)
      Javelin_DualExtruder     // Dual Extruder v2 (Javelin)
      Longfin_FlexyDually      // FlexyDually (Longfin)
      Yellowfin_DualExtruder   // Dual Extruder v3 (Yellowfin)
      Angelfish_Aero           // Titan AERO (Angelfish)

*/

// If compiling using the Arduino IDE, change printer model and toolhead here:

#define LULZBOT_Huerfano_TAZ_7
#define TOOLHEAD_Angelfish_Aero

#include "Conditionals_LulzBot.h"

#endif /* CONFIGURATION_LULZBOT */