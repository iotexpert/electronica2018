#pragma once

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}led_color_t;

extern led_color_t leftColor;
extern led_color_t rightColor;

extern void ledUARTinit(void);
extern void ledUARTsendColorValues(uint8_t leftValue, uint8_t rightValue);
