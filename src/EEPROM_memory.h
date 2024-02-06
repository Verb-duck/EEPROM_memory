#ifndef EEPROM_memory_h
#define EEPROM_memory_h
#include <EEPROM.h>
#include <Arduino.h>
#define DEBUGING 1
/*           AVR   ESP
bool         1     1 byte
int/enum     2     4
int32_t      4     4
float        4     4
double       4     8    на 32битных МК 8
int64_t      8     8
*            2     4    на 32битных МК 4
*/




//нужен только чтобы создать массив контейнеров
  class abstractConteiner {   
    public:
    virtual void readEEPROM() = 0;
    virtual void writeEEPROM() = 0;
    virtual void print() = 0;
  }; 

template<class Type> class Container ;

//========== масив контейнеров ======================
  class vector {
    public:
      vector();
      ~vector();
      void push_back(abstractConteiner *add_conteiner);
      size_t length = 0;
      abstractConteiner **array = nullptr;
      abstractConteiner* operator [](size_t index);
  };

//========= класс для упарвления выделенной памяти ===================.
  class Memory {
    private:
      byte next_addr = 4;       //0 занят для key_reset_EEPROM
      vector arrayContaier;  //маасив созданных контейнеров для быстрого доступа к значениям
    public:  
      template<class Type> friend class Container; 
      void update(byte key_reset_EEPROM );  //для сброса значений в памяти поменять число
      void print();                         //вывод всех значений в памяти через Serial.
  };

Memory memory;

//=========== контейнер значений ===========
  template<class Type>
  class Container : public abstractConteiner{
    protected:
      Type value;         // значение
      int addres;         // адрес в памяти
      char* name;         // название для удобства отладки
    public:		
      Container(Type enter_value = Type() , const char* enter_name = "");
      friend Container<Type> create(Type value,const char* name );
      Type getValue();
      const char* getName();
      virtual void readEEPROM();
      virtual void writeEEPROM();
      virtual void print();
      void operator =(Type value)
      {
          this->value = value;
          writeEEPROM();
      }
      void operator +=(Type value)
      {
          this->value += value;
          writeEEPROM();
      }
      void operator -=(Type value)
      {
          this->value -= value;
          writeEEPROM();
      }
      void operator *=(Type value)
      {
          this->value *= value;
          writeEEPROM();
      }
      void operator /=(Type value)
          {
              this->value /= value;
              writeEEPROM();
          }
      Type operator ++()
          {
              this->value++;
              writeEEPROM();
              return this->value;
          }
      Type operator --()
          {
              this->value--;
              writeEEPROM();
              return this->value;
          }
      bool operator ==(Type value)
      {
        return this->value == value;
      }
      bool operator >=(Type value)
      {
        return this->value >= value;
      }
      bool operator <=(Type value)
      {
        return this->value <= value;
      }
      bool operator >(Type value)
      {
        return this->value > value;
      }
      bool operator <(Type value)
      {
        return this->value < value;
      }
      void write_name(const char* enter_name);  //запись имени переменной в контейнер
  };

//создание переменной с присвоением адреса в EEPROM
template<class Type>
Container<Type> create(Type value,const char* name = "") {
  return Container<Type>(value, name); 
}

template <class Type>
inline Container<Type>::Container(Type enter_value,const char* enter_name )
{
  this->value = enter_value;
  write_name(enter_name);           //записываем имя переменной в контейнер
  this->addres = memory.next_addr;  //сохраняем адрес 
  memory.next_addr +=sizeof(value);    //считаем следующий адрес
  memory.arrayContaier.push_back(this); //добавляем контейнер в массив
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
  #if(DEBUGING == 1)
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
  #if(DEBUGING == 1)
  print();
  Serial.print("write in memory ");
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

void Memory::update(byte key_reset_EEPROM = 0)
{
  #if defined(ESP8266) || defined(ESP32)
    EEPROM.begin(next_addr - 1);  //выделяем достаточно байт памяти для esp
  #endif
  if(key_reset_EEPROM != EEPROM.read(0))  //если ключ не совпал
  {    
    EEPROM.put(0,key_reset_EEPROM);     //перезаписываем ключ в EEPROM 
    abstractConteiner *temp;
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