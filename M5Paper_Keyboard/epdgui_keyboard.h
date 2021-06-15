#ifndef __EPDGUI_KEYBOARD_H
#define __EPDGUI_KEYBOARD_H

#include "epdgui_button.h"
#include "epdgui_switch.h"

class EPDGUI_Keyboard: public EPDGUI_Base
{
public:
    EPDGUI_Keyboard();
    ~EPDGUI_Keyboard();
    void Draw(m5epd_update_mode_t mode = UPDATE_MODE_DU4);
    void Draw(M5EPD_Canvas* canvas);
    void Bind(int16_t event, void (* func_cb)(epdgui_args_vector_t&));
    void UpdateState(int16_t x, int16_t y);
    String getData(void);

private:
    EPDGUI_Button *_btn[5];
    EPDGUI_Base *_key[5];
    String _data;

public:

};


#endif //__EPDGUI_KEYBOARD_H
