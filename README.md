This application offers a friendly interface to interact with the system through an ESP32-like microcontroller.

![Image](https://github.com/LluisV/DeejOS/assets/100292815/4fda418f-5bb1-47b6-bbc3-9c1d5b64f4d1)

In my case the system has:
- 1 ESP32
- 5 [normal potentiometers](https://es.aliexpress.com/item/1005006213044445.html?spm=a2g0o.order_list.order_list_main.34.567e194dwLe4gY&gatewayAdapt=glo2esp)
- 5 [slider potentiometers](https://es.aliexpress.com/item/1005005779958904.html?spm=a2g0o.order_list.order_list_main.44.567e194dwLe4gY&gatewayAdapt=glo2esp)
- 3 [Toggles](https://es.aliexpress.com/item/1005004411546037.html?spm=a2g0o.order_list.order_list_main.14.567e194dwLe4gY&gatewayAdapt=glo2esp)
- 1 [3.5'' TFT touch screen](https://es.aliexpress.com/item/32985467436.html?spm=a2g0o.order_list.order_list_main.49.567e194dwLe4gY&gatewayAdapt=glo2esp)
- 1 DHT11 temperature/humidity sensor


# Install

- You can install the application on your device through Arduino IDE. In case you get an error saying that the app is too large, go to Tools/Partition scheme and select a partition larger than the current one.
- 

# To consider

- In order for potentiometers to properly control system volume, you must first install and configure [Deej](https://github.com/omriharel/deej).
- In order for the system to correctly display the date and time, your microcontroller must have Wi-Fi. You must also enter the credentials of your Wi-Fi network in the constants.h file.
- In order to program actions that your PC's operating system must perform, the microcontroller must act as a virtual keyboard to simulate keyboard shortcuts, so they can then run [AutoHotkey](https://www.autohotkey.com/) scripts. In order for the ESP32 to act as a virtual keyboard, it will need to be connected via Bluetooth to your computer. The pairing process is the same as with any other Bluetooth device.

# Troubleshooting

- One user reported that the screen appeared blank, but this was solved by selecting the 'ESP32 Wrover Module' board from the Arduino IDE.

# 3D Printable Models

- [The case](https://cad.onshape.com/documents/befb4cefc8aa52996e2020ea/w/6cc10283c7151f4204e16538/e/aff931e3298d5f47d85bc136?renderMode=0&uiState=66980cd00ccabb550b9276ff)
- [Slider grips](https://cad.onshape.com/documents/23d9c0773a4837f3e78bb4b3/w/3215c4032fce906298b19593/e/6e14c188ca74b6a55d9f865c?renderMode=0&uiState=66980cf962da612f619619bb)
