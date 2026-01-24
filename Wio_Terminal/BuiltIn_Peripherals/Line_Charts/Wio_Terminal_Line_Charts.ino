#include"seeed_line_chart.h"
TFT_eSPI tft;

#define max_size 50
doubles data;
TFT_eSprite spr = TFT_eSprite(&tft);

void setup() {
  tft.begin();
  tft.setRotation(3);
  spr.createSprite(TFT_HEIGHT,TFT_WIDTH);

}

void loop() {
  spr.fillSprite(TFT_WHITE);
  if (data.size() == max_size) {
    data.pop();
  }
  data.push(0.01 * random(1, 10));

  // Displaying Line Chart Title
  auto header =   text(0, 0); 
  header.value("Chart");
  header.align(center);
  header.valign(vcenter);
  header.width(tft.width());
  header.thickness(3);
  header.height(header.font_height() * 2);
  header.draw(); 

  // Displaying Line Chart
  auto content = line_chart(20, header.height());
  content.height(tft.height() - header.height() * 1.5);
  content.width(tft.width() - content.x() * 2);
  content.based_on(0.0);
  content.show_circle(false);
  content.value(data);
  content.color(TFT_DARKCYAN);
  content.draw();
  
  spr.pushSprite(0, 0);
  delay(50);

}
