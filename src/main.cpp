
#define DEBUGING 1  

#include <Arduino.h>
#include "EEPROM_memory.h"
  // #include "avr8-stub.h"
  // #include "app_api.h"

#define key_reset_EEPROM 0    // для сброса значений в памяти поменять число

//создание переменной и сохранение сразу в EEEprom память
// auto byte_temp = create(2);
// auto char_temp  = create('c',"char");         // (значение, имя) 
// auto int_temp  = create(uint32_t(6), "int");  
// auto double_temp  = create(8.23, "");
auto int_temp0  = create(0, "int0");   
auto byte_temp = create(53);
auto char_temp  = create('a',"char");         // (значение, имя) 


void setup() {
    // debug_init();
  Serial.begin(115200);
  Serial.println();
  memory.update(key_reset_EEPROM);    // чтение/запись переменных в EEEprom памяти
  
  // выведет в Serial все записи из EEEprom
  memory.print();
}

void loop() {
 
}
