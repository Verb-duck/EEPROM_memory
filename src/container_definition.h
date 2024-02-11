#ifndef CONTAINER_DEFINITION_H
#define CONTAINER_DEFINITION_H


template <class Type>
inline Container<Type>::Container(Type enter_value,const char* enter_name )
{
  this->value = enter_value;
  write_name(enter_name);           //записываем имя переменной в контейнер
  this->addres = memory.next_addr;  //сохраняем адрес 
  memory.next_addr +=sizeof(value);    //считаем следующий адрес
  memory.push_back(this); //добавляем контейнер в массив
}

template <class Type>
inline Type Container<Type>::getValue()
{
	return this->value;
}

template <class Type>
inline const char *Container<Type>::getName()
{
	return this->name;
}

template <class Type>
inline void Container<Type>::readEEPROM()
{
  EEPROM.get(addres, value);
  #if defined DEBUGING
    Serial.print("read from memory ");
    print();
  #endif
}

template <class Type>
inline void Container<Type>::writeEEPROM()
{
  EEPROM.put(addres,value);
  #if defined(ESP8266) || defined(ESP32)
    //if(memory.update_now && )   //для сохранения по ходу выполнения, после сброса настроек
    EEPROM.commit();        //для esp обновляем
  #endif
  #if defined DEBUGING 
  Serial.print("write in memory ");
  print();
  #endif
}

template <class Type>
inline void Container<Type>::print()
{
  Serial.print(value);
  Serial.print(" in ");
  Serial.print(name);
  Serial.print(" at addres ");
  Serial.println(addres);
}

template <class Type>
inline void Container<Type>::write_name(const char *enter_name)
{
  if(strlen(enter_name) != 1 ) {
    size_t size = 0;
    while (enter_name[size]) size++;
    size++;
    name = new char[size];
    size = 0;
    while (enter_name[size]) {
        name[size] = enter_name[size];
        size++;
    }
    name[size] = '\0';
  }
  else 
  {
    name = new char[0];
  }
}

template <class Type>
inline void Container<Type>::operator =(Type value)
{
  this->value = value;
  writeEEPROM();
}
template <class Type>
template <class Type_other>
inline void Container<Type>::operator =(Container<Type_other> &other)
{
  this->value = Type(other.getValue());
  writeEEPROM();
}
template <class Type>
inline Type Container<Type>:: operator +=(Type value)
{
  this->value += value;
  writeEEPROM();
  return this->value;
}
template <class Type>
template <class Type_other>
inline Type Container<Type>::operator +=(Container<Type_other> &other)
{
  this->value += Type(other.getValue());
  writeEEPROM();
  return this->value;
}
template <class Type>
inline Type Container<Type>:: operator -=(Type value)
{
  this->value -= value;
  writeEEPROM();
  return this->value;
}
template <class Type>
template <class Type_other>
inline Type Container<Type>::operator -=(Container<Type_other> &other)
{
  this->value -= Type(other.getValue());
  writeEEPROM();
  return this->value;
}
template <class Type>
inline Type Container<Type>:: operator *=(Type value)
{
  this->value *= value;
  writeEEPROM();
  return this->value;
}
template <class Type>
template <class Type_other>
inline Type Container<Type>::operator *=(Container<Type_other> &other)
{
  this->value *= Type(other.getValue());
  writeEEPROM();
  return this->value;
}
template <class Type>
inline Type Container<Type>:: operator /=(Type value)
{
  this->value /= value;
  writeEEPROM();
  return this->value;
}
template <class Type>
template <class Type_other>
inline Type Container<Type>::operator /=(Container<Type_other> &other)
{
  this->value /= Type(other.getValue());
  writeEEPROM();
  return this->value;
}
template <class Type>
inline Type Container<Type>:: operator ++()
{
  this->value++;
  writeEEPROM();
  return this->value;
}
template <class Type>
inline Type Container<Type>:: operator ++(int )
{
  Type temp = value; 
  this->value++;
  writeEEPROM();
  return temp;
}
template <class Type>
inline Type Container<Type>:: operator --()
{
  this->value--;
  writeEEPROM();
  return this->value;
}
template <class Type>
inline Type Container<Type>:: operator --(int )
{
  Type temp = value; 
  this->value--;
  writeEEPROM();
  return temp;
}
template <class Type>
inline bool Container<Type>:: operator ==(Type value)
{
  return this->value == value;
}
template <class Type>
template <class Type_other>
inline bool Container<Type>::operator ==(Container<Type_other> &other)
{
  return this->value == Type(other.getValue());
}
template <class Type>
inline bool Container<Type>:: operator !=(Type value)
{
  return this->value != value;
}
template <class Type>
template <class Type_other>
inline bool Container<Type>::operator !=(Container<Type_other> &other)
{
  return this->value != Type(other.getValue());
}
template <class Type>
inline bool Container<Type>:: operator >=(Type value)
{
  return this->value >= value;
}
template <class Type>
template <class Type_other>
inline bool Container<Type>::operator >=(Container<Type_other> &other)
{
  return this->value >= Type(other.getValue());
}
template <class Type>
inline bool Container<Type>:: operator <=(Type value)
{
  return this->value <= value;
}
template <class Type>
template <class Type_other>
inline bool Container<Type>::operator <=(Container<Type_other> &other)
{
  return this->value <= Type(other.getValue());
}
template <class Type>
inline bool Container<Type>:: operator >(Type value)
{
  return this->value > value;
}
template <class Type>
template <class Type_other>
inline bool Container<Type>::operator >(Container<Type_other> &other)
{
  return this->value > Type(other.getValue());
}
template <class Type>
inline bool Container<Type>:: operator <(Type value)
{
  return this->value < value;
}
template <class Type>
template <class Type_other>
inline bool Container<Type>::operator <(Container<Type_other> &other)
{
  return this->value < Type(other.getValue());
}

#endif