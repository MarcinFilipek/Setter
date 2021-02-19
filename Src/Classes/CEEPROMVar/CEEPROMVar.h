/*
 * CEEPROMVar.h
 *
 *  Created on: 18-09-2012
 *      Author: sporysz
 */

#ifndef CEEPROMVAR_H_
#define CEEPROMVAR_H_

#include <string.h>
#include "eeprom.h"
#include "eepromFlashSignature.h"
#include "CEEPROMVarConf.h"
#include "tech_exception.h"

#ifndef __TAddressOffset
#define __TAddressOffset uint16_t
#endif

/*
 * Przykład użycia
 *

   void initSerownika()
   {
	 * 	eepDrv.init(&i2cDrv,0xA2);
		CEEPROMMgr::init(&eepDrv);
		CFlashSignature::setSignature();

		backlight.initVar(CEEPROMDefaults::DEFAULT_BACKLIGHT_PERCENT);

		ustawJasnoscEkranu(backlight); //odczyt




	}

	void zmienJasnosc(int p)
	{
		backlight = p; //zapis
		ustawJasnoscEkranu(backlight);
	}

 */

/**
 *	@brief Statyczna klasa inicjalizująca system obsługi obiektów klas szablonowych.
 *
 *	Programistę interesują tylko metody publiczne, reszta to helpery wykorzystywane prez klasy szablonowe.
 *	Klasa zarządza blokiem danych zdefiniowanym przez programistę w pliku <i>CEEPROMVarConf.h</i> Maksymalny rozmiar bloku to 64KB
 *
 */
class CEEPROMMgr
{
	template <class T> friend class CEEPROMVar;
	friend class CEEPROMVarTests;

public:
    enum TEEPROMError
    {
        TEE_NO_ERROR = 0,
        TEE_READ_ERROR,
        TEE_WRITE_ERROR
    };
    typedef void (*TEEPROMErrorCallback)(TEEPROMError e);

private:
	static bool shouldInitialize;
	static uint32_t alloctedData;
	static Ceeprom* eepDrvRef;
    static TEEPROMError eeError;
    static TEEPROMErrorCallback errorCallback;




public:
	/**
	 * @brief Inicjalizuje klasę.
	 * @param eepromDrv - wskaźnik do zainicjalizowanego obiektu Ceeprom (standardowa klasa w ^stm/classes/)
	 * @param forceDefaults - jeśli jest true to wszystkie obiekty CEEPROMVar i CEEPROMArr
	 * zostaną zainicjalizowane wart. domyślną przy okazji wywoływania metody initVar()
	 *
	 * Metoda ustawiwa wewnetrzne flagi, ustawia także globalną flage sygnalizującą potrzebe inicjalizacji zmiennych eepromowych, korzystając z
	 * klasy CFlashSignature. Metoda ta @b nie wywołuje CFlashSignature::setSignature(), ustawienie flagi sygnalizującej zaprogramowanie eepromu
	 * spada na programistę (najlepiej po zainicjalizowaniu innych klas korzystających z eepromu, ale nie zarządzanych przez poniższe klasy).
	 *
	 */
	static void init(Ceeprom* eepromDrv, bool forceDefaults = false);

	/**
	 * @return Zwraca liczbę bajtów zaalokowanych w bloku zarządzanym przez klasę.
	 */
	static uint32_t getAllocatedBytes();

	/**
	 * @brief Zwraca stan flagi bledu.
	 * Flaga jest uaktualniana przy metodzie initVar() oraz każdej próbe synchronizach cache z pamięcą.
	 * @return Kod błędu.
	 */
	static TEEPROMError getEEPROMError();

	/**
	 * @return Czy jest jakikolwiek błąd eepromu.
	 */
	static bool isEEPROMError();

	/**
	 * @param Funkcja obsługi błędu eepromu.
	 */
	static void setEEPROMErrorCallback(TEEPROMErrorCallback);

private:
	static uint32_t allocateVar(uint16_t size);
	static bool getShouldInitialize();
	static void setupError(bool operationFault, TEEPROMError possibleError);
	static inline uint32_t getEEPROMStart() {return CEEPROMVarConf::EEPROM_MANAGED_BLOCK_START;}
	static inline uint32_t getEEPROMEnd() {return CEEPROMVarConf::EEPROM_MANAGED_BLOCK_END;}
	static inline Ceeprom* getEEPROMDriver() {return eepDrvRef;}

};


/**
 * @brief Klasa szablonowa dedykowana łatwego zarządzania zmiennymi przechowywanymi w pamięci EEPROM.
 *
 * Argumentem typu mogą być wszystkie wbudowane typy liczbowe, a także zdefiniowane przez programitę typy struct i enum.
 *
 * <b> Wszytkie obiekty tej klasy muszą być statyczne!!!<\b>
 *
 */
template <class T>
class CEEPROMVar
{
    friend class CEEPROMVarTests;
	__TAddressOffset addressOffset;
	T cache;
#ifdef EEPROMVAR_DEFAULT_PTR
	const T* initialPtr;
#endif

public:
	/**
	 * @brief Domyślny konstruktor klasy, wywoływany niejawnie.
	 *
	 * Głównym zadaniem konstruktora jest przypisanie adresu w eepromie, pod którym będzie zapisana zmienna.
	 * Statyczność obiektu gwarantuje przypisywanie zmiennym tych samych adresów przy każdym uruchomieniu.
	 */
	CEEPROMVar()
	{
		addressOffset = CEEPROMMgr::allocateVar(sizeof(T));
#ifdef EEPROMVAR_DEFAULT_PTR
		initialPtr = 0;
#endif
	}

	/**
	 * @brief Metoda musi być wywołana dla każdej zmiennej @b PO inicjalizacji CEEPROMVMgr:init(), ale @b PRZED pierwszym odczytem lub zapisem.
	 *
	 * Najlepiej wywoływać ją metodach inicjalizacyjnych poszczególnych klas, które zawierają zmienne eepromowe jako składniki tej klasy.
	 * Jeżeli eeprom juz był wcześniej zaprogramowany, wywołanie tej metody spowoduje odczyt wartości zmiennej z eepromu i zapisanie do
	 * cache.
	 *
	 * @param initial - wartość domyślna, które będzie wpisana do eepromu przy pierwszym uruchomieniu,
	 * lub na rządanie po wywołaniu metody CEEPROMMgr::init() z parametrem forceDefaults = true.
	 */
    void initVar(T initial)
    {
        if (CEEPROMMgr::getShouldInitialize())
        {
            cache = initial;
//            sync();
        }
        else
        {
            bool error = CEEPROMMgr::getEEPROMDriver()->readBlock((void*) (CEEPROMMgr::getEEPROMStart() + addressOffset), &cache, sizeof(T));

            CEEPROMMgr::setupError(error, CEEPROMMgr::TEE_READ_ERROR);

            if (CEEPROMMgr::eeError)
            {
                cache = initial;
            }
        }
    }

#ifdef EEPROMVAR_DEFAULT_PTR
	void initVar(const T* initialPtr)
	{
	    if(initialPtr)
	    {
	        this->initialPtr = initialPtr;
	        initVar(*initialPtr);
	    }
	}
#endif


	/**
	 * @brief Metoda zwraca aktualną wartość zmiennej zawartej w cache w pamięci RAM.
	 *
	 * Można używać tej metody jeżeli ktoś nie lubi przeładowanych operatorów, lub dana sytuacja nie pozwala na wykorzystanie operatora rzutowania.
	 *
	 * @return wartość zmiennej.
	 */
	T getValue()
	{
		return cache;
	}

	/**
	 * @brief Metoda uaktualnia wartość zmiennej.
	 *
	 * Wywołanie spowoduje uaktulanienie wartości w cache,
	 * a także sprawdzenie czy nowa wartość jest z zgodna z aktulanie zapisaną w pamięci eeprom - jeżeli nie, nastąpi zapis do eepromu.
	 *
	 * Można używać tej metody jeżeli ktoś nie lubi przeładowanych operatorów, lub dana sytuacja nie pozwala na wykorzystanie operatora przypisania.
	 *
	 * @param force - wymusza sync() nawet jesli cache sie zgadza
	 * @param val - nowa wartość zmiennej.
	 */
    void setValue(T val)
    {
        if (memcmp(&cache, &val, sizeof(T)))
        {
            cache = val;
            sync();
        }
    }

	/**
	 *
	 * @return Wskaźnik do cachowanej wartosci w ramie, zapis przez wskaźnik ze spowoduje aktualizacji w eepromie.
	 */
	T* getCachePtr()
	{
		return &cache;
	}

	/**
	 * @brief Aktualizuje wartosc w eepromie z zawartoscia cache.
	 *
	 * Przydatne jeżeli zarządzamy np. dużą strukturą, której składniki aktualizujemy przez wskaźnik.
	 */
	void sync()
	{
		T tmpUpdate;
        bool error = CEEPROMMgr::getEEPROMDriver()->readBlock((void*) (CEEPROMMgr::getEEPROMStart() + addressOffset), &tmpUpdate, sizeof(T));
        CEEPROMMgr::setupError(error, CEEPROMMgr::TEE_READ_ERROR);

		if(CEEPROMMgr::eeError == CEEPROMMgr::TEE_NO_ERROR && memcmp(&tmpUpdate,&cache,sizeof(T)))
		{
            error = CEEPROMMgr::getEEPROMDriver()->writeBlock((void*) (CEEPROMMgr::getEEPROMStart() + addressOffset), &cache, sizeof(T));
            CEEPROMMgr::setupError(error, CEEPROMMgr::TEE_WRITE_ERROR);
		}
	}

#ifdef EEPROMVAR_DEFAULT_PTR
	void restoreDefault()
	{
	    if(initialPtr)
	    {
	        setValue(*initialPtr);
	    }
	}
#endif

	/**
	 * @brief Przeładowany operator przypisania.
	 * @param val - nowa wartość zmiennej
	 */
	void operator=(T val)
	{
		setValue(val);
	}

	/**
	 * @brief Przeładowany operator rzutowania.
	 */
	operator T()
	{
		return getValue();
	}

	T& operator++()
	{
		setValue(cache + 1);
		return cache;
	}

	T& operator--()
	{
		setValue(cache - 1);
		return cache;
	}

	T operator++(int)
	{
		T tmp = cache;
		setValue(cache + 1);
		return tmp;
	}

	T operator--(int)
	{
		T tmp = cache;
		setValue(cache - 1);
		return tmp;
	}

	operator T*()
	{
		return getCachePtr();
	}


	/**
	 * @return Zwraca adres zmiennej względem adresu początku bloku.
	 */
	const void* getAdressOffset()
	{
		return addressOffset;
	}
};

/**
 * @brief Klasa szablonowa dedykowana łatwego zarządzania zmiennymi tablicowymi przechowywanymi w pamięci EEPROM.
 *
 * Klasa wykorzystuje @b stertę jako pamięć cache. Należy zaalokować odpowiednią ilość pamięci stercie przy konfiguracji projektu.
 * Kazdy element tablicy będzie zajmował (sizeof(T) + 2) bajtów sterty.
 * <b> Wszystkie obiekty tej klasy muszą być statyczne</b>
 */
template <class T>
class CEEPROMArr
{
    friend class CEEPROMVarTests;
	CEEPROMVar<T>* arrayCache;
	const uint16_t capacity;
#ifdef EEPROMVAR_DEFAULT_PTR
	const T* defaultValues;
#endif

public:
	/**
	 * @brief Konstruktor domyślny wywoływany niejawnie.
	 *
	 * Tworzy i inicjalizuje cache. Jeżeli ilość wojego miejsca na stercie będzie nie wystarczające program wejdzie w pętlę nieskończoną - jako że
	 * obiekt jest statyczny stanie się to zaraz po uruchomieniu programu, przez co błąd zostanie łatwo dostrzeżony przez programistę.
	 *
	 * @param capacity - ilość elementów tablicy.
	 */
	CEEPROMArr(uint16_t capacity):capacity(capacity)
	{
		uint16_t elementSize = sizeof(CEEPROMVar<T>);
		CEEPROMVar<T>* arr = (CEEPROMVar<T>*) malloc(elementSize * capacity);

		if(arr)
		{
			arrayCache = arr;
		}else
		{
		    throwException(EC_EEPROMVAR_HEAP_ALLOCATION_FAIL);
		    while(1);
		}

		for (uint16_t i = 0; i < capacity; ++i)
		{
			arrayCache[i] = CEEPROMVar<T>();
		}
#ifdef EEPROMVAR_DEFAULT_PTR
        defaultValues = 0;
#endif
	}


	/**
	 * @brief Metoda musi być wywołana dla każdej zmiennej @b PO inicjalizacji CEEPROMVMgr:init(), ale @b PRZED pierwszym odczytem lub zapisem.
	 *
	 * Najlepiej wywoływać ją metodach inicjalizacyjnych poszczególnych klas, które zawierają zmienne eepromowe jako składniki tej klasy.
	 * Jeżeli eeprom juz był wcześniej zaprogramowany, wywołanie tej metody spowoduje odczyt wartości z eepromu i zapisanie do
	 * cache.
	 *
	 * @param defaultValues -  wskaźnik do tablicy z wartościami, które będą wpisane do eepromu przy pierwszym uruchomieniu,
	 * lub na rządanie po wywołaniu metody CEEPROMMgr::queueReinit(). Jeżeli wpiszemy tutaj NULL to tablica zostanie zainicjalizowana zerami.
	 */
	void initArr(const T* defaultValues)
	{
#ifdef EEPROMVAR_DEFAULT_PTR
	    this->defaultValues = defaultValues;
#endif
		if(defaultValues)
		{
			for (uint16_t i = 0; i < capacity; ++i)
			{
				arrayCache[i].initVar(defaultValues[i]);
			}
		}else
		{
			T tmp;
			memset(&tmp,0,sizeof(T));

			for (uint16_t i = 0; i < capacity; ++i)
			{
				arrayCache[i].initVar(tmp);
			}
		}
	}

#ifdef EEPROMVAR_DEFAULT_PTR
	void restoreDefaults()
	{
	    if(defaultValues)
	    {
	        for (int i = 0; i < capacity; ++i)
	        {
	            arrayCache[i].setValue(defaultValues[i]);
            }
	    }
	}
#endif

	/**
	 * @brief Przeładowany operator indeksu.
	 *
	 * Obsługuje zarówno odczyt jak i przypisywanie wartości wybranym elementom tablicy.
	 */
	CEEPROMVar<T>& operator[](const uint16_t index)
	{
		return arrayCache[index];
	}
};


#endif /* CEEPROMVAR_H_ */
