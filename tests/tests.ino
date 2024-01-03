#include <M5StickC.h>
#include <Update.h>

int menuIndex = 0;
String menuTitle[] = {"TESTE", "Teste tb"};
int menuCount = 2;

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);

  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("M5StickC Update Menu");

  M5.Lcd.setCursor(0, 8 * 3);

  for (int i = 0; i < menuCount; i++) {
    M5.Lcd.printf(" %s\n", menuTitle[i].c_str());
  }

  M5.Lcd.setCursor(0, 80 - 16);
  M5.Lcd.println("BtnA: Run");
  M5.Lcd.println("BtnB: Select");
}

void loop() {
  M5.update();
}