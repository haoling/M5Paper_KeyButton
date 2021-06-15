#include "frame_keybutton.h"
#include "keyboard_config.h"
#ifdef USE_BLE_KEYBOARD
#include <BleKeyboard.h>
extern BleKeyboard bleKeyboard;
#endif

Frame_KeyButton::Frame_KeyButton() : Frame_Base()
{
  _frame_name = "Frame_KeyButton";
  keyboard = new EPDGUI_Keyboard();
  _canvas_title->drawString("M5Paper KeyButton", 250, 34);
}

Frame_KeyButton::~Frame_KeyButton()
{
  delete keyboard;
}

int Frame_KeyButton::init(epdgui_args_vector_t &args)
{
  _is_run = 1;
  M5.EPD.Clear();
  _canvas_title->pushCanvas(0, 8, UPDATE_MODE_NONE);
  EPDGUI_AddObject(keyboard);
  return 6;
}
uint32_t _time = 0;
uint32_t _next_update_time = 0;

int Frame_KeyButton::run(void)
{

  if ((millis() - _time) > _next_update_time)
  {
    char buf[20];
    _canvas_title->fillCanvas(0);
    _canvas_title->setTextDatum(CC_DATUM);
    _canvas_title->drawString("M5Paper KeyButton", 250, 34);

    // Battery
    _canvas_title->setTextDatum(CR_DATUM);
    _canvas_title->pushImage(498, 8 + 7, 32, 32, ImageResource_status_bar_battery_32x32);
    uint32_t vol = M5.getBatteryVoltage();

    if (vol < 3300)
    {
      vol = 3300;
    }
    else if (vol > 4350)
    {
      vol = 4350;
    }
    float battery = (float)(vol - 3300) / (float)(4350 - 3300);
    if (battery <= 0.01)
    {
      battery = 0.01;
    }
    if (battery > 1)
    {
      battery = 1;
    }
    uint8_t px = battery * 25;
    sprintf(buf, "%d%%", (int)(battery * 100));
    _canvas_title->drawString(buf, 498 - 10, 27 + 7);
    _canvas_title->fillRect(498 + 3, 8 + 10 + 7, px, 13, 15);

#ifdef USE_BLE_KEYBOARD
    if (bleKeyboard.isConnected())
    {
      bleKeyboard.setBatteryLevel((uint8_t)(battery * 100));
      _canvas_title->pushImage(100, 15, 32, 32, 2, ImageResource_item_icon_success_32x32);
    }
#endif

    rtc_time_t time_struct;
    M5.RTC.getTime(&time_struct);
    _canvas_title->pushCanvas(0, 0, UPDATE_MODE_GL16);

    _time = millis();
    _next_update_time = (60 - time_struct.sec) * 1000;
  }

  String text = keyboard->getData();
  Serial.print(text);
#ifdef USE_BLE_KEYBOARD
  if (bleKeyboard.isConnected())
  {
    bleKeyboard.print(text);
  }
#else
  Serial2.print(text);
#endif
  return 1;
}
