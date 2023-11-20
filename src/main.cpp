#include <Arduino.h>
#include <EEPROM_memory.h>
auto temperature_day1  = create('d',"temp day1");
auto temperature_day2  = create(2, "temp day2");
auto temperature_day3  = create(4440, "temp day3");

void setup() {
  Serial.begin(115200);
  Serial.println();
  memory.update(0);
}

void loop() {
}
