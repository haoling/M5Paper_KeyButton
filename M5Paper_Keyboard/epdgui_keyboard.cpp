#include "epdgui_keyboard.h"
#include "keyboard_config.h"

static void buttonPressedCb(epdgui_args_vector_t& args)
{
    ((EPDGUI_Keyboard *)args[0])->onButtonPressed((EPDGUI_Button *)args[1]);
}

static void buttonReleasedCb(epdgui_args_vector_t& args)
{
    ((EPDGUI_Keyboard *)args[0])->onButtonReleased((EPDGUI_Button *)args[1]);
}

EPDGUI_Keyboard::EPDGUI_Keyboard() : EPDGUI_Base()
{
    const uint16_t kKeyWidth = 140;
    const uint16_t kKeyHeight = 240;
    const uint16_t kKeyInterval = 8;
    const uint16_t kFirstLineY = 122;
    const uint16_t kBaseX = 60;

    for (int i = 0; i < 5; i++)
    {
        String name = String(i);
        _btn[i] = new EPDGUI_Button(name, kBaseX + (kKeyInterval + kKeyWidth) * i, kFirstLineY, kKeyWidth, kKeyHeight);
        _state[i] = KEY_NOACTION;

        _btn[i]->Bind(EPDGUI_Button::EVENT_PRESSED, buttonPressedCb);
        _btn[i]->AddArgs(EPDGUI_Button::EVENT_PRESSED, 0, this);
        _btn[i]->AddArgs(EPDGUI_Button::EVENT_PRESSED, 1, _btn[i]);

        _btn[i]->Bind(EPDGUI_Button::EVENT_RELEASED, buttonReleasedCb);
        _btn[i]->AddArgs(EPDGUI_Button::EVENT_RELEASED, 0, this);
        _btn[i]->AddArgs(EPDGUI_Button::EVENT_RELEASED, 1, _btn[i]);
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
        _btn[i]->Draw(mode);
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
        _btn[i]->Draw(canvas);
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
        _btn[i]->UpdateState(x, y);
    }
}

uint8_t EPDGUI_Keyboard::getState(uint8_t buttonNum)
{
    uint8_t state = _state[buttonNum];
    _state[buttonNum] = KEY_NOACTION;
    return state;
}

void EPDGUI_Keyboard::onButtonPressed(EPDGUI_Button *button)
{
    Serial.println("EPDGUI_Keyboard::buttonPressedCb: " + button->getLabel());
    for (int i = 0; i < 5; i++) {
        if (_btn[i] == button) {
            _state[i] = KEY_PRESSED;
            break;
        }
    }
}

void EPDGUI_Keyboard::onButtonReleased(EPDGUI_Button *button)
{
    Serial.println("EPDGUI_Keyboard::onButtonReleased: " + button->getLabel());
    for (int i = 0; i < 5; i++) {
        if (_btn[i] == button) {
            _state[i] = KEY_RELEASED;
            break;
        }
    }
}
