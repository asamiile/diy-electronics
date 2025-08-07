#include"TFT_eSPI.h"
TFT_eSPI tft;

void setup() {
    tft.begin();
    tft.setRotation(3);

    // fill screen
    tft.fillScreen(TFT_NAVY);
    delay(1000);
    tft.fillScreen(TFT_DARKGREY);
    delay(1000);
    tft.fillScreen(TFT_ORANGE);
    delay(1000);

    // drawing a black pixel at (4,7)
    tft.drawPixel(4,7,TFT_BLACK); 

    // drawing line
    tft.drawFastHLine(0,120,320,TFT_BLACK);
    tft.drawFastVLine(160,0,240,TFT_BLACK);

    // drawing rectangles
    tft.drawRect(110,70,100,100,TFT_BLACK);

    // drawing circles
    tft.drawCircle(160,120,50,TFT_BLACK);

    // drawing ellipse
    tft.drawEllipse(160,120,50,100,TFT_BLACK);

    // drawing triangles
    tft.drawTriangle(160,70,60,170,260,170,TFT_BLACK);

    // drawing round rectangles
    tft.drawRoundRect(110,70,100,100,10,TFT_BLACK);

    // drawing charactor
    tft.drawChar(140,120,'A',TFT_BLACK, TFT_RED,2);

    // drawing text strings
    tft.setTextColor(TFT_BLACK); 
    tft.setTextSize(2);
    tft.drawString("Hello world!", 0, 10);
}

void loop() {}