# NodeMCU-Boilerplate
Boilerplate Code for IOT projects using NodeMCU

## esp_get.ino
Updates voltage state of hardwares connected to the NodeMCU GPIO array, depending on any API returning a N bit data with binary variation in its characters for representing ON and OFF and where N equals the number of devices that can be controlled.
Configurable parameters in the code are-

Line Number|Variable Name|Description|
|-|-|-|
|4|pins[]|Array of GPIO Pins for output|
|8|serverName|Server Url|
|9|state_on|Character in API Response for ON State|
|10|state_off|Character in API Response for OFF State|
|11|ping_frequency|API Polling Frequency|
|13|ssid|Internet Enabled WIFI Router Name|
|14|password|Internet Enabled WIFI Router Password|
|15|serial_port|Arduino Terminal Baud Rate|

## esp_push.ino
Relays voltage values of sensors connected a the NodeMCU GPIO array to an API as a GET Query Param Request, by concatenating the states into a N bit data with binary variation in its characters for representing ON and OFF and where N equals the number of devices that can be controlled.
Configurable parameters in the code are-

Line Number|Variable Name|Description|
|-|-|-|
|4|pins[]|Array of GPIO Pins for output|
|5|analogPinCount|If there are multiple analogPins present, number needs to be defined here|
|11|baseApi|API Url|
|12|ping_frequency|API Polling Frequency|
|13|retry_connecting_frequency|Network Dialling Animation Frequency|
|14|ssid[]|Internet Enabled WIFI Router Name|
|15|password[]|Internet Enabled WIFI Router Password|
|16|serial_port|Arduino Terminal Baud Rate|
|17|retry_connecting_message|Network Dialling Animation Message|
