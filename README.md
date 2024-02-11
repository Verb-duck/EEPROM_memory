Небольшая библиотека для облегчения работы EEPROM памятью.

Теперь не нужно высчитывать и явно указывать адрес в памяти. Достаточно проcто создать переменную 
и при инизиализации контроллер сам высчитает адрес и запишет значение в память.
При каждом изменении значения, оно автоматически перезаписывается.

````
// #define DEBUGING     //если раскоментировать при записи и чтениии в EEEprom будет выводить в Serial значение переменной  
    
    /* для сброса значений в памяти поменять число. 
    менять после каждого добавления новой переменной или смене значения */
  #define key_reset_EEPROM 0   

#include "EEPROM_memory.h"

    //создание переменной и сохранение сразу в EEEprom память
  auto char_temp  = create('c',"char");      
    /* название переменной хранится в постоянной памяти, не EEEprom.
    Для удобства отладки */
  auto byte_temp = create(byte(2));          
    /*с явным указаним типа хранимого значения, т.к. при создании переменной 
    компилятор определяет тип по переданному значению */
  auto int_temp  = create(6, "int");  
  auto int32_temp  = create(int32_t(6), "int");  
  auto double_temp  = create(8.23, "double");


void setup() {
  Serial.begin(115200);

  memory.update(key_reset_EEPROM);    // чтение/запись переменных в EEEprom памяти
  
   // выведит в Serial название и значение
  int_temp.print(); 

    // возвращяет название переменной
  Serial.println(int_temp.getName()); 

    // получение значения переменной
  int example = int_temp.getValue();
  Serial.println(int_temp.getValue());
  
    // работают все математические функции и операторы сравнения
  char_temp = 'a';
  ++int_temp;
  byte_temp--;
  int_temp /= 2;
  int_temp *= 4;
  double_temp += 4.2;
  double_temp -= 8;
  int_temp = byte_temp;

     Serial.print("int_temp > byte_temp ");
  Serial.println(int_temp > byte_temp);
    Serial.print("int_temp != byte_temp ");
  Serial.println(int_temp != byte_temp);
    Serial.print("double_temp <= byte_temp ");
  Serial.println(double_temp <= byte_temp);
  
    // выведет в Serial все записи из EEEprom
  memory.print(); 
}

void loop() {
 
}
````
