

#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp;
#include <BH1750.h>
BH1750 lightMeter;
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <Wire.h>
#include <SPI.h>

char auth[] = "qu9fxJ6AsZPop3AMM_gINrR7rZwTmxKY";
char ssid[] = "ORBI65";
char pass[] = "newzoo218";

int TempC;
int lux;

void setup() {
  Serial.begin(115200);
  lightMeter.begin();
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1) delay(10);
  }
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("...");
  }
  Serial.println("WiFi connected");
  Blynk.begin(auth, ssid, pass, "server.wyns.it", 80);

}

void loop() {
  delay(1000);

  TempC = bmp.readTemperature();


  lux = lightMeter.readLightLevel();

  Serial.println("----NEXT READING----");  
  Serial.print("Temperature = ");
  Serial.print(TempC);
  Serial.println(" °C");
  Serial.print("Light = ");
  Serial.print(lux);
  Serial.println(" lux");
  Serial.println();

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("C: ");
  display.print(TempC,1);

  display.setCursor(0,24);
  display.print("Lux: ");
  display.print(lux);
  display.display();

  Blynk.run();
  Blynk.virtualWrite(V1, TempC);
  Blynk.virtualWrite(V2, lux);
}
