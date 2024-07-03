/*
Software License Agreement (BSD License)

Copyright (c) 2024 Pavol Ňachaj.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

#include "DisplaysSyncGFX.h"


void DisplaysSyncGFX::begin(Mode mode) {
    currentMode = mode;
}

void DisplaysSyncGFX::addPrimary(Adafruit_GFX *gfx, GetColorFunction getColor) {
    primaryDisplay = gfx;
    colorFunction = getColor;
}

void DisplaysSyncGFX::add(Adafruit_GFX *gfx) {
    if (currentMode == pixelUpgrade) {
        
        updateDisplay(gfx);
        
    }
    displays.push_back(gfx);
    if (currentMode == re_rendering) {
        if (re_renderingFunction) {
            re_renderingFunction();
        }
    }
}

void DisplaysSyncGFX::setRe_rendering(InputRe_renderingFunction re_renderingFunction) {
    this->re_renderingFunction = re_renderingFunction;
}

void DisplaysSyncGFX::updateDisplay(Adafruit_GFX *display) {
    if (primaryDisplay && colorFunction) 
    {
        for (int16_t y = 0; y < primaryDisplay->height(); y++) 
        {
            for (int16_t x = 0; x < primaryDisplay->width(); x++) 
            {
                uint16_t color = colorFunction(x, y);
                //display->drawPixel(x, y, color);
            }
        }
    }
}