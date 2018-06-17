#include <Adafruit_NeoPixel.h>

#define WS2812B_RING_LENGTH 24

class WS28B12Ring : Adafruit_NeoPixel
{
  public:
    void setHSVColor(uint16_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g,
                     uint8_t *b);
    void hsvRingSpectrum(unsigned long currentTime, unsigned long fillTime,
                         unsigned long eraseTime, bool reverse);
    void hsvRotation(unsigned long currentTime, unsigned long fillTime,
                     unsigned long rotationSpeed);
    void valueRotation(unsigned long currentTime, unsigned long fillTime,
                       unsigned long rotationSpeed);

    private:
        uint8_t r,g,b;

                        

};
