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



#ifndef DISPLAYSSYNCGFX_H
#define DISPLAYSSYNCGFX_H

#include <Adafruit_GFX.h>
#include <vector>

// Definice typu pro getColorFunction
typedef uint16_t (*GetColorFunction)(int16_t, int16_t);

typedef void (*InputRe_renderingFunction)();

typedef std::vector<Adafruit_GFX*> ListDispleySecund;

enum Mode {
    pixelUpgrade,//Podle Primarníh
    re_rendering
};

class DisplaysSyncGFX: public Adafruit_GFX {
public:

    DisplaysSyncGFX(GFXcanvas16 *gfxCan16);

    DisplaysSyncGFX(Adafruit_GFX *gfx, GetColorFunction getColor);

    DisplaysSyncGFX(Adafruit_GFX *gfx, InputRe_renderingFunction re_renderingFunction);


    DisplaysSyncGFX(Adafruit_GFX *gfx, InputRe_renderingFunction re_renderingFunction, GetColorFunction getColor, Mode mode);
    // Inicializace s režimem fungování
    ListDispleySecund displaysSecund;

    // Přidání primárního displeje
    void setModePixelUpgrate( GetColorFunction getColor);
    void setModePixelUpgrate();

    // Přidání dalšího sekundárního displeje
    void addDisp(Adafruit_GFX *gfx);

    void upgradeView(ListDispleySecund &list);
    void upgradeView();

    // Nastavení re_rendering funkce. V režimu re_rendering je funkce použivana.
    void setModeRe_rendering(InputRe_renderingFunction re_renderingFunction);
    void setModeRe_rendering();

    ~DisplaysSyncGFX();
    
    // Základní grafické funkce
    
    
    /**********************************************************************/
    /*!
    @brief  Draw to the screen/framebuffer/etc.
    Must be overridden in subclass.
    @param  x    X coordinate in pixels
    @param  y    Y coordinate in pixels
    @param color  16-bit pixel color.
    */
    /**********************************************************************/
    
    void drawPixel(int16_t x, int16_t y, uint16_t color);

    // TRANSACTION API / CORE DRAW API
    // These MAY be overridden by the subclass to provide device-specific
    // optimized code.  Otherwise 'generic' versions are used.
    void startWrite(void);
    void writePixel(int16_t x, int16_t y, uint16_t color);
    void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                uint16_t color);
    void writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    void writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    void writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                            uint16_t color);
    void endWrite(void);

    // CONTROL API
    // These MAY be overridden by the subclass to provide device-specific
    // optimized code.  Otherwise 'generic' versions are used.
    void setRotation(uint8_t r);
    void invertDisplay(bool i);

    // BASIC DRAW API
    // These MAY be overridden by the subclass to provide device-specific
    // optimized code.  Otherwise 'generic' versions are used.

    // It's good to implement those, even if using transaction API
    void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                        uint16_t color);
    void fillScreen(uint16_t color);
    // Optional and probably not necessary to change
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                        uint16_t color);
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h,
                        uint16_t color);


    
    

private:
    Adafruit_GFX *primaryDisplay = NULL;
    GetColorFunction colorFunction = NULL;
    InputRe_renderingFunction re_renderingFunction = NULL;
    GFXcanvas16 *GFXc16;

    Mode currentMode = pixelUpgrade;
    bool init = false;
    void setMode(Mode mode);


        // postupné vykreslení podle primarního displeje. V režimu pixelUpgrade je funkce použivana.
    void updateDisplayPixelUpgrade(ListDispleySecund &list);
    void updateDisplayRe_rendering();

    uint16_t getColorCanvas16(int16_t x, int16_t y);

};

#endif // DISPLAYSSYNCGFX_H
