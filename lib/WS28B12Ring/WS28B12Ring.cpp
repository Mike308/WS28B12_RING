#include "WS28B12Ring.h"

void WS28B12Ring::setHSVColor(uint16_t h, uint8_t s, uint8_t v, uint8_t *r,
                              uint8_t *g, uint8_t *b) {

  uint8_t diff;
  uint8_t red, green, blue;

  if (h > 359)
    h = 359;
  if (s > 100)
    s = 100;
  if (v > 100)
    v = 100;

  if (h < 61) {
    red = 255;
    green = (425 * h) / 100;
    blue = 0;
  } else if (h < 121) {
    red = 255 - ((425 * (h - 60)) / 100);
    green = 255;
    blue = 0;
  } else if (h < 181) {
    red = 0;
    green = 255;
    blue = (425 * (h - 120)) / 100;
  } else if (h < 241) {
    red = 0;
    green = 255 - ((425 * (h - 180)) / 100);
    blue = 255;
  } else if (h < 301) {
    red = (425 * (h - 240)) / 100;
    green = 0;
    blue = 255;
  } else {
    red = 255;
    green = 0;
    blue = 255 - ((425 * (h - 300)) / 100);
  }

  s = 100 - s;
  diff = ((255 - red) * s) / 100;
  red = red + diff;
  diff = ((255 - green) * s) / 100;
  green = green + diff;
  diff = ((255 - blue) * s) / 100;
  blue = blue + diff;

  red = (red * v) / 100;
  green = (green * v) / 100;
  blue = (blue * v) / 100;
  *r = red;
  *g = green;
  *b = blue;
}

void WS28B12Ring::hsvRotation(unsigned long currentTime, unsigned long fillTime,
                              unsigned long rotationSpeed) {

  static uint8_t fillCnt = 0;
  static uint8_t rotationCnt = 0;
  static unsigned long previousTime = 0;
  static bool rotationFlag = false;
  static uint16_t hArray[WS2812B_RING_LENGTH];
  static int newHue = 0;
  static uint16_t lastHue;
  uint8_t step = 360.0 / WS2812B_RING_LENGTH;
  if (rotationFlag == false) {
    if (currentTime - previousTime >= fillTime) {
      previousTime = currentTime;
      setHSVColor(fillCnt * step, 100, 5, &r, &g, &b);
      setPixelColor(fillCnt, Color(r, g, b));
      show();
      hArray[fillCnt] = fillCnt * step;
      fillCnt++;
      if (fillCnt == WS2812B_RING_LENGTH) {
        rotationFlag = true;
        fillCnt = 0;
        lastHue = hArray[WS2812B_RING_LENGTH - 1];
      }
    }
  } else {
    if (currentTime - previousTime >= rotationSpeed) {
      previousTime = currentTime;
      if (rotationCnt < WS2812B_RING_LENGTH - 1) {

        if (fillCnt < WS2812B_RING_LENGTH) {
          newHue = (int)(hArray[fillCnt] - step);
          if (newHue < 0)
            newHue = lastHue;
          hArray[fillCnt] = (uint16_t)newHue;
          setHSVColor(newHue, 100, 5, &r, &g, &b);
          setPixelColor(fillCnt, Color(r, g, b));
          show();
          fillCnt++;
          if (fillCnt == WS2812B_RING_LENGTH) {
            fillCnt = 0;
            rotationCnt++;
            if (rotationCnt == WS2812B_RING_LENGTH - 1)
              rotationCnt = 0;
          }
        }
      }
    }
  }
}

void WS28B12Ring::hsvRingSpectrum(unsigned long currentTime,
                                  unsigned long fillTime,
                                  unsigned long eraseTime, bool reverse) {

  static int fillCnt = 0;
  static int eraseCnt = 12;
  static unsigned long previousTime = 0;
  static bool clearFlag = false;

  if (clearFlag == false) {
    // previousTime = 0;
    if (currentTime - previousTime >= fillTime) {
      previousTime = currentTime;
      setHSVColor(fillCnt * 15, 100, 5, &r, &g, &b);
      setPixelColor(fillCnt, Color(r, g, b));
      show();
      fillCnt++;
      if (fillCnt == 24) {
        // clearFlag = true;
        fillCnt = 0;
      }
    }
  }
}

void WS28B12Ring::valueRotation(unsigned long currentTime,
                                unsigned long fillTime,
                                unsigned long rotationSpeed) {
  static uint8_t fillCnt = 0;
  static uint8_t rotationCnt = 0;
  static unsigned long previousTime = 0;
  static bool rotationFlag = false;
  static uint8_t vArray[WS2812B_RING_LENGTH];
  static int newValue = 0;
  static uint8_t lastValue;

  if (!rotationFlag) {
    if (currentTime - previousTime >= fillTime) {
      previousTime = currentTime;
      setHSVColor(180, 100, fillCnt + 2, &r, &g, &b);
      setPixelColor(fillCnt, Color(r, g, b));
      show();
      vArray[fillCnt] = fillCnt + 1;
      fillCnt++;
      if (fillCnt == WS2812B_RING_LENGTH) {
        fillCnt = 0;
        rotationFlag = true;
      }
    }
  } else {
    if (currentTime - previousTime >= rotationSpeed) {
      previousTime = currentTime;
      if (rotationCnt < WS2812B_RING_LENGTH - 1) {
        if (fillCnt < WS2812B_RING_LENGTH) {

          newValue = (int)(vArray[fillCnt] - 2);
          if (newValue < 0)
            newValue = 14;
          vArray[fillCnt] = (uint8_t)newValue;
          setHSVColor(180, 100, newValue, &r, &g, &b);
          setPixelColor(fillCnt, Color(r, g, b));
          show();
          fillCnt++;
          if (fillCnt == WS2812B_RING_LENGTH) {
            fillCnt = 0;
            rotationCnt++;
            if (rotationCnt == WS2812B_RING_LENGTH - 1)
              rotationCnt = 0;
          }
        }
      }
    }
  }
}

 void WS28B12Ring::colorRotation(unsigned long currentTime, unsigned long rotationSpeed, uint8_t ledCnt){
    static long previousTime = 0;
    static uint16_t hue = 0;
    if (currentTime - previousTime >= rotationSpeed){
        previousTime = currentTime;
        setHSVColor(hue, 100, 5, &r, &g, &b);
        setMultiplePixel(ledCnt, r, g, b);
        if (hue > 360) hue = 0;
        hue++;
      
        
      

    }
 }

 void WS28B12Ring::setMultiplePixel(uint8_t ledCnt, uint8_t r, uint8_t g, uint8_t b){
    for (int i = 0; i < ledCnt; i++){
        setPixelColor(i, Color(r, g, b));
        show();
        
      }
 }

