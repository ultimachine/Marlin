# Experimental LulzBot Marlin 1.1.4 firmware

This is an experimental development branch of Marlin 1.1.4 for LulzBot printers.

# Safety and warnings:

**This is alpha level software.** It has not been extensively tested and may damage your printer and present other hazards. Use at your own risk. Do not operate your printer while unattended and be sure to power it off when leaving the room. Please consult the documentation that came with your printer for additional safety and warning information.

# Compilation:

The source on this branch can compile firmware for the TAZ 6 and Mini, as well as all the current toolheads. This firmware also supports some internal R&D prototypes and toolheads.

To select what firmware to build, modify lines 6 and 7 of "Configuration_LulzBot.h" according to the instructions on line 39.

# Known Issues:

1. The Makefile does not work. Building must be done via the Arduino IDE (internal builds are being done with 1.8.3)
2. Printer needs to be power cycled to clear "clean nozzle" state.