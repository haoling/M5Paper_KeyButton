#include "epdgui_keyboard.h"
#include "keyboard_config.h"

static const char *kKeyAlphaMapLowerCase[5] = {
    "q", "w", "e", "r", "t"
};

EPDGUI_Keyboard::EPDGUI_Keyboard() : EPDGUI_Base()
{
    const uint16_t kKeyWidth = 72;
    const uint16_t kKeyHeight = 84;
    const uint16_t kKeyInterval = 8;
    const uint16_t kFirstLineY = 122;
    const uint16_t kBaseX = 120;

    for (int i = 0; i < 5; i++)
    {
        String name = String(i);
        _btn[i] = new EPDGUI_Button(name, kBaseX + (kKeyInterval + kKeyWidth) * i, kFirstLineY, kKeyWidth, kKeyHeight);
    }

    for (int i = 0; i < 5; i++)
    {
        _key[i] = _btn[i];
    }
}

EPDGUI_Keyboard::~EPDGUI_Keyboard()
{
    for (int i = 0; i < 5; i++)
    {
        delete _btn[i];
    }
}

void EPDGUI_Keyboard::Draw(m5epd_update_mode_t mode)
{
    if (_ishide)
    {
        return;
    }
    for (int i = 0; i < 5; i++)
    {
        _key[i]->Draw(mode);
    }
}

void EPDGUI_Keyboard::Draw(M5EPD_Canvas *canvas)
{
    if (_ishide)
    {
        return;
    }
    for (int i = 0; i < 5; i++)
    {
        _key[i]->Draw(canvas);
    }
}

void EPDGUI_Keyboard::Bind(int16_t state, void (*func_cb)(epdgui_args_vector_t &))
{
}

void EPDGUI_Keyboard::UpdateState(int16_t x, int16_t y)
{
    if (!_isenable)
    {
        return;
    }
    // log_d("UpdateState %d, %d", x, y);
    for (int i = 0; i < 5; i++)
    {
        bool keypressed = _key[i]->isInBox(x, y);
        _key[i]->UpdateState(x, y);
        if (keypressed)
        {
            if (i < 26)
            {
                _data = kKeyAlphaMapLowerCase[i];
                break;
            }
        }
    }
}

String EPDGUI_Keyboard::getData(void)
{
    String data = _data;
    _data = "";
    return data;
}
