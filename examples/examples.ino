#include "EEPROM_memory.h"
#define key_reset_EEPROM 0    // для сброса значений в памяти поменять число


//создание переменной и сохранение сразу в EEEprom память
auto byte_temp = create(2);
auto char_temp  = create('c',"char");         // (значение, имя) 
auto int_temp  = create(uint32_t(6), "int");  
auto double_temp  = create(8.23, "double");

// Имя переменной хранится в flash памяти. 
void setup() {
  Serial.begin(115200);
  Serial.println();

  memory.update(key_reset_EEPROM);    // чтение/запись переменных в EEEprom памяти

// вывести в Serial 
  int_temp.print(); 

// возвращяет название переменной
  Serial.println(int_temp.getName()); 

// получение значения переменной
  int example = int_temp.getValue();
  
  char_temp = 'a';
  ++int_temp ;
  int_temp /= 2;
  int_temp *= 4;
  double_temp += 4;
  double_temp -= 8;
  
// выведет в Serial все записи из EEEprom
  memory.print(); 
}

void loop() {
 
}