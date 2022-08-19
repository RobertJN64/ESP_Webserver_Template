# ESP Webserver Template

Base project for building webservers on the ESP32. Uses [ESP Async WebServer](https://github.com/me-no-dev/ESPAsyncWebServer) and [ArduinoJson](https://arduinojson.org/).


## Setup

Create your secrets.h file, and add it to the include folder.
```h
#define SSID "YOUR SSID"
#define PASS "YOUR PASS"
```

## Use

Edit the cpp code in [main.cpp](src/main.cpp) and the html files in [html](/html). Any updates or new html / css / js files will be automatically included whenever you run move_html.py.

Build and upload to the ESP32 with PlatformIO.

Visit the IP address printed by the Serial Monitor to view and interact with the webpage.

## Demos
 - Rendering multiple pages with external css and preprocessing
 - Send and recieve json updates
 - Handle asynchronous IO requests