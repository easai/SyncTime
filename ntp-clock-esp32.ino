#include <WiFi.h>
#include "time.h"
#include <U8g2lib.h>
#include "config.h"
char ssid[] = SECRET_SSID;
char password[] = SECRET_PASS;

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -5 * 3600;  // EST (UTC -5)
const int daylightOffset_sec = 3600;   // Adjust for EDT

U8G2_SH1106_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, 7, 6); // SH1106 OLED Display

unsigned long lastUpdate = 0;
const unsigned long updateInterval = 60 * 1000; // Update every minute

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("\nConnected!");

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    u8g2.begin();
}

void loop() {
    if (millis() - lastUpdate >= updateInterval) {  
        struct tm timeinfo;
        if (!getLocalTime(&timeinfo)) {
            Serial.println("Failed to obtain time");
            return;
        }

        // Format time as HH:MM (no seconds)
        char timeString[6];
        strftime(timeString, sizeof(timeString), "%H:%M", &timeinfo);

        // Format date as YYYY-MM-DD
        char dateString[12];
        strftime(dateString, sizeof(dateString), "%Y-%m-%d", &timeinfo);

        // Display date & time
        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_fub20_tr); // Large font for time
        u8g2.drawStr(20, 30, timeString);

        u8g2.setFont(u8g2_font_ncenB12_tr); // Medium font for date
        u8g2.drawStr(10, 55, dateString);

        u8g2.sendBuffer();

        Serial.print("Updated time: ");
        Serial.println(timeString);
        Serial.print("Updated date: ");
        Serial.println(dateString);

        lastUpdate = millis(); // Save last update time
    }
}
