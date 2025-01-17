/**************************************************************************/
 /**************************************************************************/
 
 #pragma once
 
 #include "esphome/components/i2c/i2c.h"
 #include "esphome/components/touchscreen/touchscreen.h"
 #include "esphome/core/component.h"
 
 namespace esphome {
 namespace ft6236 {
 
 using namespace touchscreen;
 
 static const uint8_t FT6236_DEFAULT_THRESHOLD = 80;
 
 class FT6236Touchscreen : public Touchscreen, public i2c::I2CDevice {
  public:
   void setup() override;
   void dump_config() override;
 
   void set_interrupt_pin(InternalGPIOPin *pin) { this->interrupt_pin_ = pin; }
   void set_reset_pin(GPIOPin *pin) { this->reset_pin_ = pin; }
   void set_threshold(uint8_t threshold) { this->threshold_ = threshold; }
 
  protected:
   void hard_reset_();
   void update_touches() override;
 
   InternalGPIOPin *interrupt_pin_{nullptr};
   GPIOPin *reset_pin_{nullptr};
   uint8_t threshold_{FT6236_DEFAULT_THRESHOLD};
 
   uint8_t read_touch_number_();
 
   uint16_t read_touch_x_(uint8_t touch);
   uint16_t read_touch_y_(uint8_t touch);
   uint8_t read_touch_event_(uint8_t touch);
   uint8_t read_touch_id_(uint8_t touch);
   uint8_t read_touch_weight_(uint8_t touch);
   uint8_t read_touch_misc_(uint8_t touch);
 
   uint8_t read_byte_(uint8_t addr);
 };
 
 }  // namespace ft6236
 }  // namespace esphome