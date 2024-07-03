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

enum Mode {
    pixelUpgrade,//Podle Primarníh
    re_rendering
};

class DisplaysSyncGFX: public Adafruit_GFX {
public:

    // Inicializace s režimem fungování
    void begin(Mode mode);

    // Přidání primárního displeje
    void addPrimary(Adafruit_GFX *gfx, GetColorFunction getColor);

    // Přidání dalšího sekundárního displeje
    void add(Adafruit_GFX *gfx);

    // Nastavení re_rendering funkce. V režimu re_rendering je funkce použivana.
    void setRe_rendering(InputRe_renderingFunction re_renderingFunction);

    // postupné vykreslení podle primarního displeje. V režimu pixelUpgrade je funkce použivana.
    void updateDisplay(Adafruit_GFX *gfx);


private:

    Adafruit_GFX *primaryDisplay = NULL;
    GetColorFunction colorFunction = NULL;
    InputRe_renderingFunction re_renderingFunction = NULL;
    std::vector<Adafruit_GFX*> displays;
    Mode currentMode = pixelUpgrade;



};

#endif // DISPLAYSSYNCGFX_H
