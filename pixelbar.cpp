// Initialize neopixel strip
#include "pixelbar.h"

const uint16_t PixelCount = 6; // Number of neopixels in strip
const uint8_t PixelPin = 7; // Pin number to which the strip is connected
const uint32_t switch_freq = 10000; // Frequency to switch the pixels
uint32_t tick = 0; // Tick for the frequency

// Initialize neopixel strip with 2 alternating colors
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);
RgbColor red(colorSaturation, 0, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor black(0, 0, 0);

// Initialize the neopixel strip
void pixelbar_init()
{
    strip.Begin();
    for(uint16_t i = 0; i < PixelCount; i+=2)
    {
      strip.SetPixelColor(i, red);
      strip.SetPixelColor(i+1, blue);
    }
}

// Turn on the neopixel strip with color changing
void pixelbar_on()
{
    if(tick++ == switch_freq)
    {
        strip.RotateRight(1);
        strip.Show();

        tick = 0;
    }
}

// Turn off the neopixel strip
void pixelbar_off()
{
    for(uint16_t i = 0; i < PixelCount; ++i)
    {
        strip.SetPixelColor(i, black);
    }
    
    strip.Show();
}
