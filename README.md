# ESP32
ESP32 With Arduino/Web Server/TCP Server

## Structure of ESP32
<img src="https://github.com/AUTO-KKYU/ESP32/assets/118419026/32cf20ad-40cd-4573-a82c-e635e59422b7">



## Install ESP32 On Arduino IDE
- Additional boards manager URLs
    - https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
- esp32 by Espressif Systems install on boards manager
- AsyncTCP : https://github.com/me-no-dev/AsyncTCP
- ESPAsyncWebServer : https://github.com/me-no-dev/ESPAsyncWebServer
    - 두 라이브러리를 다운로드하여 Arduino Library 폴더에 복사    

- when error msg execute env on MacBook
```sh
xcrun: error: invalid active developer path (/Library/Developer/CommandLineTools), missing xcrun at: /
Library/Developer/CommandLineTools/usr/bin/xcrun
```
```sh
$ xcode-select --install
```
