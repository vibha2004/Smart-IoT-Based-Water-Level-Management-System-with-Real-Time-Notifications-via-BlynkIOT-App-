#define BLYNK_TEMPLATE_ID "TMPL3BFN2oENm"
#define BLYNK_TEMPLATE_NAME "ESP32 WaterLevel"
#define BLYNK_AUTH_TOKEN "7w4fj76RmqQgt6OsMU0hlFvS5mu1ykih"
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFiClient.h>
#include <WiFi.h>
#define VPIN_BUTTON_1 V1

const char* ssid = "Bread";
const char* password = "vibgyor123";
char auth[] = "7w4fj76RmqQgt6OsMU0hlFvS5mu1ykih";  

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int trigPin = 5;
const int echoPin = 18;
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
long duration;
int distanceCm;
int distanceInch;

void setup() {
    Serial.begin(115200);
    delay(1000);

    Blynk.begin("7w4fj76RmqQgt6OsMU0hlFvS5mu1ykih","Bread","vibgyor123"); 

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;) ;
    }
    delay(500);
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
}

void loop() {
    Blynk.run(); // Handle Blynk communication

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distanceCm = duration * SOUND_SPEED / 2;
    distanceInch = distanceCm * CM_TO_INCH;

    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);
    Serial.print("Distance (inch): ");
    Serial.println(distanceInch);

    // Send distance data to VPIN_BUTTON_1 in the Blynk app
    Blynk.virtualWrite(VPIN_BUTTON_1, distanceCm);

    display.clearDisplay();
    display.setCursor(0, 25);
    display.print(distanceCm);
    display.print(" cm");

    display.display();

    delay(500);
}
