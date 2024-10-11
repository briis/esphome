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
#include "ft6236.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ft6236 {

  static const uint8_t FT6236_ADDR = 0x38;        // I2C address
  static const uint8_t FT6236_REG_NUMTOUCHES = 0x02; // Number of touch points
  static const uint8_t FT6236_REG_VENDID = 0xA8; // Vendor ID register
  static const uint8_t FT6236_VENDID = 0x11;       // Expected Vendor ID
  static const uint8_t FT6236_REG_CHIPID = 0xA3; // Chip ID register
  static const uint8_t FT6236_CHIPID = 0x36;     // FT6236 Chip ID
  static const uint8_t FT6236U_CHIPID = 0x64;    // FT6236U Chip ID
  static const uint8_t FT6206_CHIPID = 0x06;     // FT6206 Chip ID

  static const char *TAG = "ft6236";

  FT6236Touchscreen::FT6236Touchscreen(void) : interval_(1000), display_(nullptr), listener_(nullptr) { touches = 0; }

  void FT6236Touchscreen::setup()
  {
    ESP_LOGCONFIG(TAG, "Setting up FT6236...");

    // Initialize the I2C device, check the chip ID and vendor ID
    if (readRegister8(FT6236_REG_VENDID) != FT6236_VENDID)
    {
      ESP_LOGE(TAG, "Failed to find FT6236, wrong vendor ID.");
      mark_failed();
      return;
    }

    uint8_t id = readRegister8(FT6236_REG_CHIPID);
    if (id != FT6236_CHIPID && id != FT6236U_CHIPID && id != FT6206_CHIPID)
    {
      ESP_LOGE(TAG, "Wrong chip ID: 0x%02X", id);
      mark_failed();
    }
}

void FT6236Touchscreen::loop() {
  uint8_t n = touched();
  if (n > 0) {
    TS_Point point = getPoint(0);
    ESP_LOGD(TAG, "Touch at: X=%d, Y=%d", point.x, point.y);
    if (this->listener_) {
      this->listener_();  // Trigger the listener if touch detected
    }
  }
}

uint8_t FT6236Touchscreen::touched(void) {
  uint8_t n = readRegister8(FT6236_REG_NUMTOUCHES);
  if (n > 2) {
    n = 0;
  }
  return n;
}

TS_Point FT6236Touchscreen::getPoint(uint8_t n) {
  readData();
  if (touches == 0 || n > 1) {
    return TS_Point(0, 0, 0);
  }
  return TS_Point(touchX[n], touchY[n], 1);
}

void FT6236Touchscreen::readData(void) {
  uint8_t data[16];
  this->read_bytes(0x00, data, 16);

  touches = data[2] & 0x0F;

  if (touches > 0) {
    touchX[0] = ((data[3] & 0x0F) << 8) | data[4];
    touchY[0] = ((data[5] & 0x0F) << 8) | data[6];
  }
}

void FT6236Touchscreen::writeRegister8(uint8_t reg, uint8_t val) {
  this->write_byte(reg, val);
}

uint8_t FT6236Touchscreen::readRegister8(uint8_t reg) {
  uint8_t val;
  this->read_bytes(reg, &val, 1);
  return val;
}

void FT6236Touchscreen::dump_config() {
  ESP_LOGCONFIG(TAG, "FT6236:");
  ESP_LOGCONFIG(TAG, "  I2C Address: 0x38");
}

}  // namespace ft6236
}  // namespace esphome