/*
This is a library for the FT6236 touchscreen controller by FocalTech.

The FT6236 and FT6236u work the same way.

A lot of this library is originally written by Limor Fried/Ladyada.

Because Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

@section author Author
Written by Limor Fried/Ladyada for Adafruit Industries.

@section license License
MIT license, all text above must be included in any redistribution
*/
#pragma once

#include "esphome/components/i2c/i2c.h"
#include "esphome/components/touchscreen/touchscreen.h"
#include "esphome/core/component.h"


namespace esphome {
namespace ft6236 {

using namespace touchscreen;

class TS_Point {
 public:
  TS_Point(void);
  TS_Point(int16_t x, int16_t y, int16_t z);

  bool operator==(TS_Point);
  bool operator!=(TS_Point);

  int16_t x;
  int16_t y;
  int16_t z;
};

class FT6236Touchscreen : public Component, public i2c::I2CDevice {
 public:
  FT6236Touchscreen(void);

  void setup() override;
  void loop() override;
  void dump_config() override;

  // Set update interval
  void set_interval(uint32_t interval) { this->interval_ = interval; }

  // Set display (if applicable)
  void set_display(void* display) { this->display_ = display; }

  // Get update trigger for custom event handling
  Trigger<>* get_update_trigger() { return &this->update_trigger_; }

    // Register listener for touch events
  void register_listener(std::function<void()> listener) { this->listener_ = listener; }

  uint8_t touched(void);
  TS_Point getPoint(uint8_t n = 0);

 protected:
  void writeRegister8(uint8_t reg, uint8_t val);
  uint8_t readRegister8(uint8_t reg);
  void readData(void);

  uint8_t touches;
  uint16_t touchX[2], touchY[2], touchID[2];
  uint32_t interval_;  // For update interval
  void* display_;  // For display interaction (if applicable)
  Trigger<> update_trigger_;  // Event trigger for updates
  

}  // namespace ft6236
}  // namespace esphome