#ifndef _FRAME_KEYBOARD_H_
#define _FRAME_KEYBOARD_H_

#include "frame_base.h"
#include "epdgui.h"

class Frame_KeyButton : public Frame_Base
{
public:
    Frame_KeyButton();
    ~Frame_KeyButton();
    int run();
    int init(epdgui_args_vector_t &args);

private:
    EPDGUI_Keyboard *keyboard;
};

#endif //_FRAME_KEYBOARD_H_
