/*
 * iDateTime.h
 *
 *  Created on: 17-04-2013
 *      Author: damian
 *     Version: 1.0.0
 */

#ifndef IDATETIME_H_
#define IDATETIME_H_

#include <stdint.h>
#include <time.h>

class IDateTime
{
    public:

        static const uint16_t INITIAL_YEAR = 2016; // po 1 lutego zmieniać na bieżący rok
        static const uint16_t CENTURY_BASE = 2000;

        enum TError
        {
            ERROR_NONE = 0,
            ERROR_READ_PROBLEM,
            ERROR_TIME_NOT_SET,
        };

        virtual ~IDateTime() {};

        /**
         * \return Numer miesiąca (1-12)
         */
        virtual uint8_t getMonth() = 0;

        /**
         * \return pełny rok np. 2013
         */
        virtual uint16_t getYear() = 0;

        /**
         * \return Dzień aktualnego miesiąca
         */
        virtual uint8_t getDay() = 0;

        /**
         * \return Sekundy aktualnej godziny (0-59)
         */
        virtual uint8_t getSeconds() = 0;

        /**
         * \return Minuty aktualnej godziny (0-59)
         */
        virtual uint8_t getMinutes() = 0;

        /**
         * \return Godzina aktualnej dobry (0-23)
         */
        virtual uint8_t getHours() = 0;

        /**
         * \return Numer dnia tygodnia (0-6)
         */
        virtual uint8_t getWeekDay() = 0;

        /**
         * \brief Ustawia Date, bez zmiany godziny
         * \param year pełny rok np. 2013
         * \param month numer miesiąca
         * \param day numer dnia miesiąca
         */
        virtual void setDate(uint16_t year, uint8_t month, uint8_t day) = 0;

        /**
         * \brief Ustawia godzinę, bez zmiany daty
         * \param hour godziny
         * \param minute minuty
         * \param second sekundy
         */
        virtual void setTime(uint8_t hours, uint8_t minutes, uint8_t seconds) = 0;

        /**
         * \brief Ustawia dzień tygodnia
         * \param weekDay dzień tygodnia (0-6)
         */
        virtual void setWeekDay(uint8_t weekDay) = 0;

        /**
         * \brief Służy np. do zbuforowania odczytu zegara do lokalnych zmiennych
         * \return kod błedu w przypadku jego wystąpienia
         */
        virtual TError update() { return ERROR_NONE; }

        /**
         *\brief zwraca czas w formacie time_t
         *\return time_t
         */
        virtual time_t getTotalTime(void)=0;

        /**
         * \return zwraca true, jeśli po restarcie zegara, data została ustawiona przez użytkownika
         */
        virtual bool isDateTimeSet() = 0;
};

#endif /* IDATETIME_H_ */
