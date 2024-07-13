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



void DisplaysSyncGFX::setMode(Mode mode)
{
    currentMode = mode;   
}


DisplaysSyncGFX::DisplaysSyncGFX(Adafruit_GFX *gfx, GetColorFunction getColor):
    Adafruit_GFX(gfx->width(),gfx->height())
{
    primaryDisplay = gfx;   
    setModePixelUpgrate(getColor);
}

DisplaysSyncGFX::DisplaysSyncGFX(Adafruit_GFX *gfx, InputRe_renderingFunction re_renderingFunction):
    Adafruit_GFX(gfx->width(),gfx->height())
{
    primaryDisplay = gfx;
    setModeRe_rendering(re_renderingFunction);
}

DisplaysSyncGFX::DisplaysSyncGFX(Adafruit_GFX *gfx, InputRe_renderingFunction re_renderingFunction, GetColorFunction getColor, Mode mode):
    Adafruit_GFX(gfx->width(),gfx->height())
{
    primaryDisplay = gfx;
    setModeRe_rendering(re_renderingFunction);    
    setModePixelUpgrate(getColor);
    setMode(mode);
}

void DisplaysSyncGFX::setModePixelUpgrate(GetColorFunction getColor)
{
    colorFunction = getColor;
    setModePixelUpgrate();
}

void DisplaysSyncGFX::setModePixelUpgrate()
{
    setMode(pixelUpgrade);
}

void DisplaysSyncGFX::addDisp(Adafruit_GFX *gfx) {
    displaysSecund.push_back(gfx);
    ListDispleySecund newDisp = ListDispleySecund();
    newDisp.push_back(gfx);
    upgradeView(newDisp);
    newDisp.clear();
}

void DisplaysSyncGFX::upgradeView(ListDispleySecund  &list)
{
    if (currentMode == pixelUpgrade) {
        updateDisplayPixelUpgrade(list); 
    }
    if (currentMode == re_rendering) {
        updateDisplayRe_rendering();
    }
}

void DisplaysSyncGFX::upgradeView()
{
    upgradeView(displaysSecund);
}

void DisplaysSyncGFX::setModeRe_rendering(InputRe_renderingFunction re_renderingFunction) {
    
    this->re_renderingFunction = re_renderingFunction;
    setModeRe_rendering();
}

void DisplaysSyncGFX::setModeRe_rendering()
{
    setMode(re_rendering);

}

DisplaysSyncGFX::~DisplaysSyncGFX()
{
    displaysSecund.clear();
}

void DisplaysSyncGFX::updateDisplayPixelUpgrade(ListDispleySecund &list) {
    if (primaryDisplay && colorFunction) 
    {
        for (int16_t y = 0; y < primaryDisplay->height(); y++) 
        {
            for (int16_t x = 0; x < primaryDisplay->width(); x++) 
            {
                uint16_t color = colorFunction(x, y);

                for(auto &display : list)
                {
                    if(display->height() < y && display->width() < x)
                    {
                        display->drawPixel(x, y, color);
                    }
                }               
            }
        }
    }
}

void DisplaysSyncGFX::updateDisplayRe_rendering()
{
    if (re_renderingFunction) {
        re_renderingFunction();
    }
}

void DisplaysSyncGFX::startWrite(void) 
{
    if (primaryDisplay) {
        primaryDisplay->startWrite();
    }
    for (auto &display : displaysSecund) {
        display->startWrite();
    }
}

void DisplaysSyncGFX::writePixel(int16_t x, int16_t y, uint16_t color) {
    if (primaryDisplay) {
        primaryDisplay->writePixel(x, y, color);
    }
    for (auto &display : displaysSecund) {
        display->writePixel(x, y, color);
    }
}


void DisplaysSyncGFX::writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    if (primaryDisplay) {
        primaryDisplay->writeFillRect(x, y, w, h, color);
    }
    for (auto &display : displaysSecund) {
        display->writeFillRect(x, y, w, h, color);
    }
}


void DisplaysSyncGFX::writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    if (primaryDisplay) {
        primaryDisplay->writeFastVLine(x, y, h, color);
    }
    for (auto &display : displaysSecund) {
        display->writeFastVLine(x, y, h, color);
    }
}

void DisplaysSyncGFX::writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    if (primaryDisplay) {
        primaryDisplay->writeFastHLine(x, y, w, color);
    }
    for (auto &display : displaysSecund) {
        display->writeFastHLine(x, y, w, color);
    }
}

void DisplaysSyncGFX::writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    if (primaryDisplay) {
        primaryDisplay->writeLine(x0, y0, x1, y1, color);
    }
    for (auto &display : displaysSecund) {
        display->writeLine(x0, y0, x1, y1, color);
    }
}


void DisplaysSyncGFX::endWrite(void) {
    if (primaryDisplay) {
        primaryDisplay->endWrite();
    }
    for (auto &display : displaysSecund) {
        display->endWrite();
    }
}


void DisplaysSyncGFX::setRotation(uint8_t r) {
    if (primaryDisplay) {
        primaryDisplay->setRotation(r);
    }
    for (auto &display : displaysSecund) {
        display->setRotation(r);
    }
}

void DisplaysSyncGFX::invertDisplay(bool i) {
    if (primaryDisplay) {
        primaryDisplay->invertDisplay(i);
    }
    for (auto &display : displaysSecund) {
        display->invertDisplay(i);
    }
}

void DisplaysSyncGFX::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    if (primaryDisplay) {
        primaryDisplay->drawFastVLine(x, y, h, color);
    }
    for (auto &display : displaysSecund) {
        display->drawFastVLine(x, y, h, color);
    }
}

void DisplaysSyncGFX::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    if (primaryDisplay) {
        primaryDisplay->drawFastHLine(x, y, w, color);
    }
    for (auto &display : displaysSecund) {
        display->drawFastHLine(x, y, w, color);
    }
}

void DisplaysSyncGFX::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    if (primaryDisplay) {
        primaryDisplay->fillRect(x, y, w, h, color);
    }
    for (auto &display : displaysSecund) {
        display->fillRect(x, y, w, h, color);
    }
}

void DisplaysSyncGFX::fillScreen(uint16_t color) {
    if (primaryDisplay) {
        primaryDisplay->fillScreen(color);
    }
    for (auto &display : displaysSecund) {
        display->fillScreen(color);
    }
}

void DisplaysSyncGFX::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    if (primaryDisplay) {
        primaryDisplay->drawLine(x0, y0, x1, y1, color);
    }
    for (auto &display : displaysSecund) {
        display->drawLine(x0, y0, x1, y1, color);
    }
}

void DisplaysSyncGFX::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    if (primaryDisplay) {
        primaryDisplay->drawRect(x, y, w, h, color);
    }
    for (auto &display : displaysSecund) {
        display->drawRect(x, y, w, h, color);
    }
}

void DisplaysSyncGFX::drawPixel(int16_t x, int16_t y, uint16_t color) {
    if (primaryDisplay) {
        primaryDisplay->drawPixel(x, y, color);
    }
    for (auto &display : displaysSecund) {
        display->drawPixel(x, y, color);
    }
}
