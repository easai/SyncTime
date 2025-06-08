# SyncTime

SyncTime zis a compact yet functional timekeeping system built around the ESP32. It achieves real-time synchronization using NTP servers and displays the current time and date on an SH1106 OLED screen.

## Project Overview
* Wi-Fi Connectivity: The ESP32 connects to a Wi-Fi network using credentials stored in config.h, ensuring modular security.
* NTP Time Sync: It fetches the time from "pool.ntp.org" and adjusts for EST (or EDT during daylight savings).
* OLED Display (SH1106): Uses the U8g2 library to render time and date with different fonts for readability.
* Periodic Updates: Time synchronization occurs every minute, avoiding excessive network requests.
* Serial Feedback: Displays connection status and time updates via the Serial Monitor.

## Core Features
* Displays HH:MM format for time and YYYY-MM-DD for the date.
* Non-blocking update mechanism using millis(), ensuring efficient looping.
* Board-specific I2C adjustments, with GPIO6 and GPIO7 mapped correctly for the SH1106.
* This project combines networking, real-time processing, and embedded display control into a practical tool.

## Setup 
### Create config.h and Set Values
Create a separate file named config.h in your project folder.

config.h
```cpp
#ifndef CONFIG_H
#define CONFIG_H

#define SECRET_SSID "your_wifi_ssid"
#define SECRET_PASS "your_wifi_password"

#endif
```

### Set the correct GMT offset 
Find your local UTC offset and modify `gmtOffset_sec` accordingly. 

- Eastern Time (UTC -5): const long gmtOffset_sec = -5 * 3600;
- Pacific Time (UTC -8): const long gmtOffset_sec = -8 * 3600;
- UTC itself: const long gmtOffset_sec = 0;

### Adjust for daylight saving 
If your region observes daylight saving time, set `daylightOffset_sec`. Otherwise, set it to 0.