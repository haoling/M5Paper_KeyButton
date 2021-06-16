#ifndef __EPDGUI_KEYBOARD_H
#define __EPDGUI_KEYBOARD_H

#include "epdgui_button.h"

const uint8_t KEY_NOACTION = 0x00;
const uint8_t KEY_PRESSED = 0x01;
const uint8_t KEY_RELEASED = 0x02;

class EPDGUI_Keyboard: public EPDGUI_Base
{
public:
    EPDGUI_Keyboard();
    ~EPDGUI_Keyboard();
    void Draw(m5epd_update_mode_t mode = UPDATE_MODE_DU4);
    void Draw(M5EPD_Canvas* canvas);
    void Bind(int16_t event, void (* func_cb)(epdgui_args_vector_t&));
    void UpdateState(int16_t x, int16_t y);
    uint8_t getState(uint8_t buttonNum);
    void onButtonPressed(EPDGUI_Button *button);
    void onButtonReleased(EPDGUI_Button *button);

private:
    EPDGUI_Button *_btn[5];
    uint8_t _state[5];

};


#endif //__EPDGUI_KEYBOARD_H
