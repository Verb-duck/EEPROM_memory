#include <Arduino.h>
#include "EEPROM_memory.h"
#define key_reset_EEPROM 1    // для сброса значений в памяти поменять число

//создание переменной и сохранение сразу в EEEprom память
auto byte_temp = create(2);
auto char_temp  = create('c',"char");         // (значение, имя) 
auto int_temp  = create(uint32_t(6), "int");  
auto double_temp  = create(8.23, "double");

void setup() {
  Serial.begin(115200);
  Serial.println();

  memory.update(key_reset_EEPROM);    // чтение/запись переменных в EEEprom памяти
  Serial.print("result: ");
  Serial.println( double_temp >= 5); 
}

void loop() {
 
}
