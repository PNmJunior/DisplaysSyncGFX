#include "DisplaysSyncGFX.h"



#define SPI_MISO    19
#define SPI_MOSI    23
#define SPI_SCLK    18

#define TFT_MISO    SPI_MISO
#define TFT_MOSI    SPI_MOSI
#define TFT_SCLK    SPI_SCLK
#define TFT_CS      14      // Chip select control pin
#define TFT_DC      27      // Data Command control pin
#define TFT_RST     33
#define TFT_BL      32       // TFT backlight  pin
#define TFT_BACKLIGHT_ON HIGH

#define TOUCH_MISO     SPI_MISO
#define TOUCH_MOSI     SPI_MOSI
#define TOUCH_SCLK     SPI_SCLK
#define TOUCH_CS       12      // TouchScreen Chip Select

#define SPI_FREQUENCY  40000000
#define SPI_READ_FREQUENCY  20000000
#define SPI_TOUCH_FREQUENCY  2500000

#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ST7796S_kbv.h"
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
Adafruit_ST7796S_kbv tft = Adafruit_ST7796S_kbv(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST, TFT_MISO);


  #define TFT2_CS         17
  #define TFT2_RST        16
  #define TFT2_RS         4//DC
  #define TFT2_SDA    SPI_MOSI//mosi
  #define TFT2_CLK    SPI_SCLK//sclk

Adafruit_ST7735 tft2 = Adafruit_ST7735(TFT2_CS, TFT2_RS, TFT2_SDA, TFT2_CLK, TFT2_RST);
Adafruit_GFX* gfx2 = &tft2;
DisplaysSyncGFX md = DisplaysSyncGFX(100,100);

void setup() {
  // put your setup code here, to run once:
  tft.begin();
  tft2.initR(INITR_BLACKTAB);
  Serial.begin(9600);
  Serial.print("Size vector:");
  Serial.println(md.sizeDisp());
  Serial.print("find 'tft':");
  Serial.println(md.findDisp((Adafruit_GFX*)&tft));
  md.addDisp((Adafruit_GFX*)&tft);
  Serial.print("Size vector:");
  Serial.println(md.sizeDisp());
  Serial.print("find 'tft':");
  Serial.println(md.findDisp((Adafruit_GFX*)&tft));
  //md.addDisp((Adafruit_GFX*)&tft2);
  Serial.print("Size vector:");
  Serial.println(md.sizeDisp());
  Serial.print("find 'tft':");
  Serial.println(md.findDisp((Adafruit_GFX*)&tft));
  Serial.print("delete 'tft':");
  Serial.println(md.deleteDisp((Adafruit_GFX*)&tft));
  Serial.print("Size vector:");
  Serial.println(md.sizeDisp());
  Serial.print("find 'tft':");
  Serial.println(md.findDisp((Adafruit_GFX*)&tft));
  md.addDisp((Adafruit_GFX*)&tft);
  Serial.print("Size vector:");
  Serial.println(md.sizeDisp());

  
  Serial.println("Test color:");
  Serial.println("Reg");
    md.fillScreen(ST77XX_RED);
    delay(10000);
  Serial.println("Grean");
    md.fillScreen(ST77XX_GREEN);
    delay(10000);
  Serial.println("Blue");
  md.fillScreen(ST77XX_BLUE);
  delay(10000);
  uint16_t time = millis();
  md.fillScreen(ST77XX_BLUE);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  // large block of text
  md.fillScreen(ST77XX_BLACK);
  testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", ST77XX_WHITE);
  delay(1000);

  // md print function!
  mdPrintTest();
  delay(4000);

  // a single pixel
  md.drawPixel(md.width()/2, md.height()/2, ST77XX_GREEN);
  delay(500);

  // line draw test
  testlines(ST77XX_YELLOW);
  delay(500);

  // optimized lines
  testfastlines(ST77XX_RED, ST77XX_BLUE);
  delay(500);

  testdrawrects(ST77XX_GREEN);
  delay(500);

  testfillrects(ST77XX_YELLOW, ST77XX_MAGENTA);
  delay(500);

  md.fillScreen(ST77XX_BLACK);
  testfillcircles(10, ST77XX_BLUE);
  testdrawcircles(10, ST77XX_WHITE);
  delay(500);

  testroundrects();
  delay(500);

  testtriangles();
  delay(500);

  mediabuttons();
  delay(500);

  Serial.println("done");
  delay(1000);
}

void loop() {
  md.invertDisplay(true);
  delay(500);
  md.invertDisplay(false);
  delay(500);
}

void testlines(uint16_t color) {
  md.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < md.width(); x+=6) {
    md.drawLine(0, 0, x, md.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < md.height(); y+=6) {
    md.drawLine(0, 0, md.width()-1, y, color);
    delay(0);
  }

  md.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < md.width(); x+=6) {
    md.drawLine(md.width()-1, 0, x, md.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < md.height(); y+=6) {
    md.drawLine(md.width()-1, 0, 0, y, color);
    delay(0);
  }

  md.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < md.width(); x+=6) {
    md.drawLine(0, md.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < md.height(); y+=6) {
    md.drawLine(0, md.height()-1, md.width()-1, y, color);
    delay(0);
  }

  md.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < md.width(); x+=6) {
    md.drawLine(md.width()-1, md.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < md.height(); y+=6) {
    md.drawLine(md.width()-1, md.height()-1, 0, y, color);
    delay(0);
  }
}

void testdrawtext(char *text, uint16_t color) {
  md.setCursor(0, 0);
  md.setTextColor(color);
  md.setTextWrap(true);
  md.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
  md.fillScreen(ST77XX_BLACK);
  for (int16_t y=0; y < md.height(); y+=5) {
    md.drawFastHLine(0, y, md.width(), color1);
  }
  for (int16_t x=0; x < md.width(); x+=5) {
    md.drawFastVLine(x, 0, md.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  md.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < md.width(); x+=6) {
    md.drawRect(md.width()/2 -x/2, md.height()/2 -x/2 , x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  md.fillScreen(ST77XX_BLACK);
  for (int16_t x=md.width()-1; x > 6; x-=6) {
    md.fillRect(md.width()/2 -x/2, md.height()/2 -x/2 , x, x, color1);
    md.drawRect(md.width()/2 -x/2, md.height()/2 -x/2 , x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < md.width(); x+=radius*2) {
    for (int16_t y=radius; y < md.height(); y+=radius*2) {
      md.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < md.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < md.height()+radius; y+=radius*2) {
      md.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  md.fillScreen(ST77XX_BLACK);
  uint16_t color = 0xF800;
  int t;
  int w = md.width()/2;
  int x = md.height()-1;
  int y = 0;
  int z = md.width();
  for(t = 0 ; t <= 15; t++) {
    md.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void testroundrects() {
  md.fillScreen(ST77XX_BLACK);
  uint16_t color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = md.width()-2;
    int h = md.height()-2;
    for(i = 0 ; i <= 16; i+=1) {
      md.drawRoundRect(x, y, w, h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}

void mdPrintTest() {
  float p = 3.1415926;
  md.setTextWrap(false);
  md.fillScreen(ST77XX_BLACK);
  md.setCursor(0, 30);
  md.setTextColor(ST77XX_RED);
  md.setTextSize(1);
  md.println("Hello World!");
  md.setTextColor(ST77XX_YELLOW);
  md.setTextSize(2);
  md.println("Hello World!");
  md.setTextColor(ST77XX_GREEN);
  md.setTextSize(3);
  md.println("Hello World!");
  md.setTextColor(ST77XX_BLUE);
  md.setTextSize(4);
  md.print(1234.567);
  delay(1500);
  md.setCursor(0, 0);
  md.fillScreen(ST77XX_BLACK);
  md.setTextColor(ST77XX_WHITE);
  md.setTextSize(0);
  md.println("Hello World!");
  md.setTextSize(1);
  md.setTextColor(ST77XX_GREEN);
  md.print(p, 6);
  md.println(" Want pi?");
  md.println(" ");
  md.print(8675309, HEX); // print 8,675,309 out in HEX!
  md.println(" Print HEX!");
  md.println(" ");
  md.setTextColor(ST77XX_WHITE);
  md.println("Sketch has been");
  md.println("running for: ");
  md.setTextColor(ST77XX_MAGENTA);
  md.print(millis() / 1000);
  md.setTextColor(ST77XX_WHITE);
  md.print(" seconds.");
}

void mediabuttons() {
  // play
  md.fillScreen(ST77XX_BLACK);
  md.fillRoundRect(25, 10, 78, 60, 8, ST77XX_WHITE);
  md.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_RED);
  delay(500);
  // pause
  md.fillRoundRect(25, 90, 78, 60, 8, ST77XX_WHITE);
  md.fillRoundRect(39, 98, 20, 45, 5, ST77XX_GREEN);
  md.fillRoundRect(69, 98, 20, 45, 5, ST77XX_GREEN);
  delay(500);
  // play color
  md.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_BLUE);
  delay(50);
  // pause color
  md.fillRoundRect(39, 98, 20, 45, 5, ST77XX_RED);
  md.fillRoundRect(69, 98, 20, 45, 5, ST77XX_RED);
  // play color
  md.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_GREEN);
}





  
/*
delay(10000);
  
  Serial.begin(9600);
  Serial.print("Size vector:");
  Serial.println(md.sizeDisp());
  Serial.print("find 'tft':");
  Serial.println(md.findDisp((Adafruit_GFX*)&tft));
  md.addDisp((Adafruit_GFX*)&tft);
  Serial.print("Size vector:");
  Serial.println(md.sizeDisp());
  Serial.print("find 'tft':");
  Serial.println(md.findDisp((Adafruit_GFX*)&tft));
  md.addDisp((Adafruit_GFX*)&tft2);
  Serial.print("Size vector:");
  Serial.println(md.sizeDisp());
  Serial.print("find 'tft':");
  Serial.println(md.findDisp((Adafruit_GFX*)&tft));
  Serial.print("delete 'tft':");
  Serial.println(md.deleteDisp((Adafruit_GFX*)&tft));
  Serial.print("Size vector:");
  Serial.println(md.sizeDisp());
  Serial.print("find 'tft':");
  Serial.println(md.findDisp((Adafruit_GFX*)&tft));
  md.addDisp((Adafruit_GFX*)&tft);
  Serial.print("Size vector:");
  Serial.println(md.sizeDisp());

  md.fillScreen(0);
  Serial.println("a");
  delay(1000);
  md.setRotation(0);
  Serial.println("b");
  delay(1000);
  md.writeFastHLine(0, 0, 9, 0x1111);
  Serial.println("c");
  delay(1000);
  md.setRotation(1);
  Serial.println("d");
  delay(1000);
  md.writeFastHLine(0, 0, 9, 0x8888);
  Serial.println("e");
  delay(1000);
  md.setRotation(2);
  Serial.println("f");
  delay(1000);
  md.writeFastHLine(0, 0, 9,0x8888);
  Serial.println("g");
  delay(1000);
  md.setRotation(3);
  Serial.println("h");
  delay(1000);
  md.writeFastHLine(0, 0, 9, 0x8888);
  Serial.println("i");
  delay(1000);
  md.setRotation(1);
  Serial.println("j");
  delay(1000);
  md.fillRect(3, 8, 5, 5, 0x8888);
  Serial.println("k");
  delay(1000);
  
}

void loop(void) {}*/