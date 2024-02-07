#ifndef EEPROM_memory_h
#define EEPROM_memory_h
#include <EEPROM.h>
#include <Arduino.h>

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
    public:  
      byte next_addr = 4;       //0 занят для key_reset_EEPROM
      vector arrayContaier;  //маасив созданных контейнеров для быстрого доступа к значениям
      template<class Type> friend class Container; 
      void update(byte key_reset_EEPROM );  //для сброса значений в памяти поменять число
      void print();                         //вывод всех значений в памяти через Serial.
  };
  Memory memory;

//======== создание переменной с присвоением адреса в EEPROM ======
  template<class Type>
  Container<Type> create(Type value,const char* name = "") {
    return Container<Type>(value, name); 
  }
   
//=========== контейнер значений ===========
  template<class Type>
  class Container : public abstractConteiner{
    protected:
      Type value;         // значение
      int addres;         // адрес в памяти
      char* name;         // название для удобства отладки
      Container(Type enter_value = Type() , const char* enter_name = "");
    public:
      template<class Type2>		
        friend Container<Type2> create(Type2 value,const char* name );
      Type getValue();
      const char* getName();
      virtual void readEEPROM();
      virtual void writeEEPROM();
      virtual void print();
      void operator =(Type value);
      Type operator +=(Type value);
      Type operator -=(Type value);
      Type operator *=(Type value);
      Type operator /=(Type value);
      Type operator ++();
      Type operator ++(int );
      Type operator --();
      Type operator --(int );
      bool operator ==(Type value);
      bool operator >=(Type value);
      bool operator <=(Type value);
      bool operator >(Type value);
      bool operator <(Type value);
      void write_name(const char* enter_name);  //запись имени переменной в контейнер
  };

#endif

#include "container_definition.h"
#include "class_definition.h"