# mkrtThermoClient

## Indoor temperature  and moisture plus Weather forecast 
This Application presents indoor temperature and mousture, fetches a temperature   
forecast from given url and presents the result on 16x2 lcd panel.   

Forecast format (via https):
forecast.txt
``` 
 08| 12| 18| 21|
  1|  2|  2|  1|
Ulko: 0'C
```

### Web backend
Example backend solution:  https://github.com/vesakoo/fmiForecastEspoo  
Creates a forecast.txt file that one can place into webserver to share.   
Example renders weather forecast on Finland / Espoo - area fetching the data  
from  Finish institute of meteorology Open data interface:   
https://www.ilmatieteenlaitos.fi/avoin-data   


### Hardware
* Arduino mkr Wifi 1010 board
* Liquid Crystal 16x2 lcd panel HD44780 (or a compatible)  
* Digital thermometer DHT22

For Connecting MKR board to lcd Please check this tutorial:   
http://arduinoairpollution.altervista.org/tutorial-arduino-mkr1000-display-lcd-hd44780/

### Requirements
* install libs
* add SSID.h to with connection parameters for your WIFI router

SSID.h
```
#define SECRET_SSID "your-secret"
#define SECRET_PASS "your-pass"
#define ACTION_TTL (unsigned long) 15000
#define AUTH      WIFLY_AUTH_WPA2_PSK
```

