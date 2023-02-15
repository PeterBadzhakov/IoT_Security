#ifndef PIXELBAR_H
#define PIXELBAR_H

#include <NeoPixelBus.h>

extern const uint16_t PixelCount;
extern const uint8_t PixelPin;
extern const uint32_t switch_freq;
extern uint32_t tick;

#define colorSaturation 128

extern NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip;

extern RgbColor red;
extern RgbColor blue;
extern RgbColor black;

void pixelbar_init();
void pixelbar_on();
void pixelbar_off();

#endif
