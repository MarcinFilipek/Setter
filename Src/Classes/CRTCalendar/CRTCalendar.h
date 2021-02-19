/**
 * @file CRTCalendar.h
 *
 * @author Marcin Sporysz
 * @date 12/05/2012
 */


#ifndef CRTCALENDAR_H_
#define CRTCALENDAR_H_

#include <stdint.h>
#include <time.h>
#include "iDelay.h"
#include "iDateTime.h"

#ifndef USE_HAL_DRIVER
#include "stm32f10x.h"
#include "misc.h"
#include <stm32f10x_rtc.h>
#else
#include "hal.h"
#endif

/**
 * @brief Klasa do obsługi kalendarza i zegara dla procesorów STM.
 * Klasa operuje na module RTC procesora. Zakładamy że ma on zew. źródło zasilania, chroniące przed utratą informacji.
 * RTC MUSI być skonfigurowany z rozdzielczością 1 sekundy, funkcja initialize() odpowiednio konfiguruje moduł dla procesora pracującego na zewnętrznym oscylatorze HSE lub LSE 32kHz.
 * W innych przypadkach należy zmodyfikować metodę initialize() aby uzyskać częstotliwość 1s.
 * Klasa wykorzystuje funkcje biblioteczne zawarte w <time.h>. Rejestr licznika RTC przechowuje liczbe sekund jakie upłynęły od 1-sty-1970r.
 *
 *	ChangeLog:
 *	18.XI 2013
 *		-dodanie statusu inicjalizacji
 *		-zmiana wartosci zwracanej przez funkcje init
 *	8.VI  2013
 *	    - zezwalanie na zapis do rejestrów chronionych przed kazdym zaspisem do rejestrów RTC.
 *	    - usuniecie obsługi źródła sygnału HSE.
 *	28.VI 2013
 *	    - dodanie metod obliczających różnice czasów.
 *
 *	4.VI 2013
 *		- dopasowanie do IDateTime
 *		- usunięcie metody getFullYear()
 *		- getYear() zwraca pełny rok
 *		- setDate() parametr "yr" oczekuje pełnego roku
 *
 */
class CRTCalendar: public IDateTime
{
public:

	enum TRTCClock
	{
		TRCTCLK_LSE = RCC_BDCR_RTCSEL_LSE,
		TRCTCLK_LSI = RCC_BDCR_RTCSEL_LSI,
	};

	enum TRTCInitResult
	{
		TRTC_NOT_INIT,
		TRTC_OK,
		TRTC_OK_RESET,
		TRTC_FAIL,
	};

private:
	static const uint32_t REGISTER_FLAG_TIMEOUT_MS = 5000;

	static volatile bool secondsChanged;
	static bool useCacheInterrupt;
	static IDelayFunctions* delayFn;
	tm* cachedTimeStruct;
	TRTCInitResult initStatus;

public:
	CRTCalendar()
	{
		initStatus = TRTC_NOT_INIT;
	}
	/**
	 * @brief Przeprowadza pierwszą (lub po zaniku zasilania bateryjnego) inicjalizację RTC.
	 * @param clrSrc Zrodlo zegara dla RTC
	 * @param useCacheIT, klasa oczekuje wywoływania metody RTCIRQHandler z przerwania sekundowego RTC, zwieksza wydajność przy czestym odczycie.
	 * @param delays Wskaźnik do obiektu z funkcjami opóźnien (musi istnieć cały czas)
	 *
	 */
	TRTCInitResult initialize(TRTCClock clkSrc, bool useChacheIT, IDelayFunctions* delays);

	/**
	 * @return Numer dnia tygodnia (0-6).
	 */
	uint8_t getWeekDay();

	/**
	 * @return Numer dnia miesiąca (1-31).
	 */
	uint8_t getDay();

	/**
	 * @return Numer miesiąca (1-12).
	 */
	uint8_t getMonth();

	/**
	 * @return Rok, pełny.
	 */
	uint16_t getYear();

	/**
	 * @return Sekundy aktualnej godziny (0-59).
	 */
	uint8_t getSeconds();

	/**
	 * @return Minuty aktualnej godziny (0-59).
	 */
	uint8_t getMinutes();

	/**
	 * @return Godzina aktualnej dobry (0-23).
	 */
	uint8_t getHours();

	/**
	 * @return Liczba minut, które upłynęły w aktualnej dobie.
	 */
	uint16_t getMinutesOfDay();


	/**
	 * @brief Ustawia Date, bez zmiany godziny.
	 * @param yr pełny rok.
	 * @param month numer miesiąca.
	 * @param day numer dnia miesiąca.
	 */
	void setDate(uint16_t yr, uint8_t month, uint8_t day);

	/**
	 * @brief Ustawia godzinę, bez zmiany daty, sekundy zostają wyzerowane.
	 * @param hr godziny.
	 * @param min minuty.
	 * @param sec sekundy.
	 */
	void setTime(uint8_t hr, uint8_t min, uint8_t sec);

	/*
	 * @brief Ustawia dzien tygodnia.
	 * _UWAGA_ po wykorzystaniu tej funkcji, użytkownik rezygnuje z kalendarza i odczytana wartość dnia, miesiąca, roku będzie błędna.
	 * @param d numer dnia tygodnia.
	 */
	void setWeekDay(uint8_t d);

	/**
	 * @brief Metoda wywoływana z przerwania od sekundowego przerwania RTC.
	 * Służy do odświeżania cache. Wywoływanie nie jest konieczne jeżeli przy inicjalizacji
	 * zostało ustawione useCacheInterrupt na false.
	 */
	static void RTCIRQHandler();

	/**
	 * @brief Inicjalizuje przerwanie sekundowe od RTC, ale nie definiuje.
	 */
	void initRTCIRQ(uint8_t preemPrio, uint8_t subPrio);

	/**
	 * Należy używać funkcji getDay();
	 */
	inline uint8_t getMonthDay() __attribute__ ((deprecated)) {return getDay();}

	/**
	 * @param then - Godzina i data względem której obliczana jest różnica, z reguły jest to data starsza.
	 * @return Różnica (aktualna data - then) w sekundach
	 */
	int32_t getSecondsPassedSince(time_t then);

	/**
	 * @return Zwraca aktualną date i godzinę w reprezentacji time_t z biblioteki time.h
	 */
	time_t getTotalTime();

	/**
	 * @return Zwraca status inicjalizacji rtc
	 */
	TRTCInitResult getInitStatus();

        /**
         * \return zwraca true, jeśli po restarcie zegara, data została ustawiona przez użytkownika
         */
        bool isDateTimeSet();

private:
	/**
	 * @brief Zwraca strukturę opisującą czas na postawie zawartości rejestru RTC.
	 * @return Wskaźnik do statycznej struktury.
	 */
	tm* getTimeStruct();

	/**
	 * @return status operacji
	 * @param counter wartość do zapisania w rejestrze RTC.
	 */
	bool writeRTC(uint32_t counter);

	/*
	 * @return Odpowiedz na pytanie, czy zadany rok jest przestepny.
	 */
	bool getLeapYear(uint16_t year);

	inline bool waitForSync();
	inline bool waitForTask();
	bool waitForRegisterFlag(volatile uint32_t* reg, uint32_t bit, IDelayFunctions* dl);
	bool waitForRegisterFlag(volatile uint16_t* reg, uint16_t bit, IDelayFunctions* dl);


        bool isDateTimeSet(uint16_t year, uint8_t month);

};


#endif /* CRTCALENDAR_H_ */
