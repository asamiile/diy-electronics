#include"Histogram.h"

TFT_Histogram histogram=TFT_Histogram();
TFT_eSPI tft = TFT_eSPI();

void setup() {
  tft.begin();
  histogram.initHistogram(&tft);

  histogram.formHistogram("a",1,50.55,40,TFT_RED); //Column 1
  histogram.formHistogram("b",2,20,40,TFT_BLACK); //Column 2
  histogram.formHistogram("c",3,100,50,TFT_GREEN); //Column 3
  histogram.formHistogram("d",4,53,50,TFT_BLUE); //Column 4
  histogram.formHistogram("e",5,133,30,TFT_YELLOW); //Column 5
  histogram.formHistogram("f",6,53,50,TFT_ORANGE); //Column 6
  histogram.formHistogram("g",7,80,50,TFT_PINK); //Column 7

  histogram.showHistogram();
  delay(3000);

  histogram.changeParam(6,"F",55,TFT_PINK);
  histogram.deleteCylinder(7);
  histogram.lineChart(TFT_BLACK);

  delay(2000);
  histogram.notShowAxis();

}

void loop() {
  // put your main code here, to run repeatedly:

}
