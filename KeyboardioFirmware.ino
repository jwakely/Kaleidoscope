// Copyright 2015 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#define DEBUG_SERIAL false

#include "KeyboardioFirmware.h"
#include "KeyboardioHID.h"


uint8_t matrixState[ROWS][COLS] = {0};
const Key keymaps[KEYMAPS][ROWS][COLS] = { KEYMAP_LIST };
uint8_t primary_keymap = 0;
uint8_t temporary_keymap = 0;

void setup() {
    wdt_disable();
    Keyboard.begin();
    Mouse.begin();
    AbsoluteMouse.begin();
    KeyboardHardware.setup();
    LEDControl.boot_animation();

    temporary_keymap = primary_keymap = Storage.load_primary_keymap(KEYMAPS);
}


void loop() {
    KeyboardHardware.scan_matrix();
    Keyboard.sendReport();
    Keyboard.releaseAll();
    LEDControl.update(temporary_keymap);
}


