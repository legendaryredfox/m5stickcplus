#include <M5StickCPlus.h>
#include <Update.h>
#include <EEPROM.h>

#define EEPROM_SIZE 4
#define BGCOLOR BLACK
#define FGCOLOR GREEN

#define BIG_TEXT 4
#define MEDIUM_TEXT 3
#define SMALL_TEXT 2
#define TINY_TEXT 1

#define M5LED
#define RTC
#define AXP
#define ACTIVE_LOW_IR
#define ROTATION
#define USE_EEPROM

#define DISP M5.Lcd
#define IRLED 9
#define SPEAKER M5.Beep
#define SD_CLK_PIN 0
#define SD_MISO_PIN 36
#define SD_MOSI_PIN 26

int cursor = 0;
int menuIndex = 0;
int current_proc = 1;
int menuCount = 2;
int screen_dim_time = 30;
int screen_dim_current = 0;
int brightness = 100;

String menuTitle[] = {"TESTE", "Teste tb"};

bool rstOverride = false; 
bool isSwitching = true;
bool screen_dim_dimmed = false;

struct MENU {
  char name[19];
  int command;
};


void setup() {
  M5.begin();
  DISP.setRotation(3);
  DISP.fillScreen(BGCOLOR);
  DISP.setTextColor(FGCOLOR);

  DISP.setTextSize(2);
  DISP.setCursor(0, 0);
  DISP.println("Legendary Redfox");

  DISP.setCursor(0, 80 - 16);
  DISP.println("BtnA: Run");
  DISP.println("BtnB: Select");
}

void loop() {
  M5.update();
}

void drawmenu(MENU thismenu[], int size) {
  DISP.setTextSize(SMALL_TEXT);
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 5, 1);
  // scrolling menu
  if (cursor > 5) {
    for ( int i = 0 + (cursor - 5) ; i < size ; i++ ) {
      DISP.print((cursor == i) ? ">" : " ");
      DISP.println(thismenu[i].name);
    }
  } else {
    for (
      int i = 0 ; i < size ; i++ ) {
      DISP.print((cursor == i) ? ">" : " ");
      DISP.println(thismenu[i].name);
    }
  }
}

void number_drawmenu(int nums) {
  DISP.setTextSize(SMALL_TEXT);
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 5, 1);
  // scrolling menu
  if (cursor > 5) {
    for ( int i = 0 + (cursor - 5) ; i < nums ; i++ ) {
      DISP.print((cursor == i) ? ">" : " ");
      DISP.println(i);
    }
  } else {
    for (
      int i = 0 ; i < nums ; i++ ) {
      DISP.print((cursor == i) ? ">" : " ");
      DISP.println(i);
    }
  }
}

MENU mmenu[] = {
  { "TV-B-Gone", 13},
  { "Bluetooth", 16},
  { "WiFi", 12},
  { "QR Codes", 18},
  { "Settings", 2},
};
int mmenu_size = sizeof(mmenu) / sizeof(MENU);

void mmenu_setup() {
  cursor = 0;
  rstOverride = true;
  drawmenu(mmenu, mmenu_size);
  delay(500); // Prevent switching after menu loads up
}

void mmenu_loop() {
  if (check_next_press()) {
    cursor++;
    cursor = cursor % mmenu_size;
    drawmenu(mmenu, mmenu_size);
    delay(250);
  }
  if (check_select_press()) {
    rstOverride = false;
    isSwitching = true;
    current_proc = mmenu[cursor].command;
  }
}

bool check_next_press(){

  if (digitalRead(M5_BUTTON_RST) == LOW){
    dimtimer();
    return true;
  }
  return false;
}

bool check_select_press(){
  if (digitalRead(M5_BUTTON_HOME) == LOW){
    dimtimer();
    return true;
  }
  return false;
}

void dimtimer(){
  if(screen_dim_dimmed){
    screenBrightness(brightness);
    screen_dim_dimmed = false;
  }
  screen_dim_current = uptime() + screen_dim_time + 2;
}

void screenBrightness(int bright){
    M5.Axp.ScreenBreath(bright);
}

int uptime(){
  return(int(millis() / 1000));
}