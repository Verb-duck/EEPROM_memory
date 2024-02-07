#ifndef CLASS_DEFINITION_H
#define CLASS_DEFINITION_H

void Memory::update(byte key_reset_EEPROM = 0)
{
  #if defined(ESP8266) || defined(ESP32)
    EEPROM.begin(next_addr - 1);  //выделяем достаточно байт памяти для esp
  #endif
  if(key_reset_EEPROM != EEPROM.read(0))  //если ключ не совпал
  {    
    EEPROM.put(0,key_reset_EEPROM);     //перезаписываем ключ в EEPROM 
    for(size_t i = 0 ; i < arrayContaier.length ; i++)   
    {
      arrayContaier[i] -> writeEEPROM();    //перезаписываем все значения в EEPROM
    }
    
    #if defined(ESP8266) || defined(ESP32)
      EEPROM.commit();    //для esp обновляем
    #endif 
    Serial.println("update EEPROM settings");   
  }
  else {
    for(size_t i = 0 ; i < arrayContaier.length ; i++)   
    {
      arrayContaier[i] -> readEEPROM(); //считываем все значения из EEPROM
    }
    Serial.println("read EEPROM settings");
  }
}

void Memory::print()
{
  for(size_t i = 0 ; i < arrayContaier.length ; i++)   
    {
      arrayContaier[i] -> print(); 
    }
}

vector::vector()
{
}

vector::~vector()
{
  if(!array)
    delete[] array;
}
void vector::push_back(abstractConteiner *add_conteiner)
{
  length++;
  if(!array)
  {
    array = new abstractConteiner*[1];
    array[0] = add_conteiner;
  }
  else 
  {
    abstractConteiner **temp = new abstractConteiner*[length];
    for(size_t i = 0 ; i < length - 1 ; i++)
      temp[i] = array[i];
    delete[] array;
    array = temp;
    array[length - 1] = add_conteiner;
  }
}
abstractConteiner *vector::operator[](size_t index)
{
  return array[index];
}

#endif