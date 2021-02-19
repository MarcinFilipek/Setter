/*
 * CBacklightDriver.h
 *
 *  Created on: Dec 9, 2014
 *      Author: krzysiek
 */

#ifndef CBACKLIGHTDRIVER_H_
#define CBACKLIGHTDRIVER_H_

#include "CEEPROMVar.h"
#include "pwmController.h"
#include "iinterruptupdatable.h"

#include <stdint.h>

/**
 * Klasa sterująca podświetleniem wyświetlacza.
 */
class CBacklightDriver: public IInterruptUpdatable
{
public:
    static const int8_t DEFAULT_DIM_BRIGHTNESS = 30;    ///< Domyślana jasność ekranu w stanie przyciemnionym.
    static const int8_t DEFAULT_NORMAL_BRIGHTNESS = 85; ///< Domyślana jasność ekranu w stanie rozjaśnionym.
    static const int8_t DEFAULT_FADE_TIME = 120;        ///< Domyślany czas bezczynności po którym ekran zostanie przyciemniony.
    static const bool DEFAULT_LIGHT_SENSOR = false;     ///< Domyślany stan korekcji podświetlania przez czujnik.

private:
    static const int8_t MAX_FADE_TIME_ENERGY_SAVING = 15;
    static const int8_t FACTOR_ENERGY_SAVING = 25;
    static const int16_t FACTOR_LINEAR = 250;

    static const int8_t LIGHT_SENSOR_THRESHOLD_MAX = 90;
    static const int8_t LIGHT_SENSOR_BRIGHTNESS_MAX = 100;
    static const int8_t LIGHT_SENSOR_THRESHOLD_MIN = 10;
    static const int8_t LIGHT_SENSOR_BRIGHTNESS_MIN = 20;

    static const int8_t STEP_MULTIPLIER = 2;

    static const int8_t MODE_AUTO = 0;
    static const int8_t MODE_FIXED = 1;

    CPwmController m_pwmController;

    CEEPROMVar<int8_t> m_dimBrightness;
    CEEPROMVar<int8_t> m_normalBrightness;
    CEEPROMVar<int16_t> m_fadeTime;
    CEEPROMVar<bool> m_lightSensor;

    int8_t m_minPWM;
    int8_t m_maxPWM;

    int8_t m_mode;
    int8_t m_lightSensorPercent;

    int16_t m_currentBrightness;
    int16_t m_targetBrightness;
    int32_t m_counterFadeTime;

    bool m_energySaving;

public:

    /**
     * Konstruktor.
     */
    CBacklightDriver();

    /**
     * Metoda inicjalizująca.
     * Rozpaczyna automatyczną regulacje jasności.
     * @param initStruct Struktura inicjalizacyjna dla timera.
     * @param systemClockFrequency Częstotliwość zegara taktującego timer.
     * @param minPWM Określa procent wypełnienia PWM przy minimalnej jasności. Zabezpiecza przed błędami winikającymi ze zbyt niskiej jasności.
     * @param maxPWM Określa procent wypełnienia PWM przy maksymalnej jasności. Zabezpiecza przed nadmiernym poborem energii.
     */
    void init(CPwmController::TInitStruct *initStruct, uint32_t systemClockFrequency, int8_t minPWM, int8_t maxPWM);

    /**
     * Rozpaczyna automatyczną regulacje jasności.
     */
    void startAutomaticMode();

    /**
     * Ustala jasność na stałym poziomie.
     * @param percent Stała jasność wyrażona w procentach. Wartość 0% całkowicie wyłączy podświetlenie.
     */
    void startFixedMode(int8_t percent);

    /**
     * Metoda przeznaczona do cyklicznego wywoływania.
     * @param interact Informacja o naciśnięciu ekranu/przycisków.
     * @param energySaving Tryb oszczędzania energii obniża poziom jasności oraz czas wygaszania ekranu.
     * @param lightSensorPercent Wskazania czujnika oświetlenia wyrażone w procentach.
     */
    void update(bool interact, bool energySaving, int8_t lightSensorPercent);

    void updateFromInterrupt(uint16_t updateFrequency);

    /**
     * Ustawiania jasności ekranu w stanie przyciemnionym.
     * Parametr jest zapamiętywany w EEPROM.
     * @param percent Jasność ekranu wyrażona w procentach. Wartość 0% całkowicie wyłączy podświetlenie.
     */
    void setDimBrightness(int8_t percent);

    /**
     * Pobieranie jasności ekranu w stanie przyciemnionym.
     * @return Jasność ekranu wyrażona w procentach.
     */
    int8_t getDimBrightness();

    /**
     * Ustawianie jasności ekranu w stanie rozjaśnionym.
     * Parametr jest zapamiętywany w EEPROM.
     * @param percent Jasność ekranu wyrażona w procentach.
     */
    void setNormalBrightness(int8_t percent);

    /**
     * Pobieranie jasności ekranu w stanie rozjaśnionym.
     * @return Jasność ekranu wyrażona w procentach.
     */
    int8_t getNormalBrightness();

    /**
     * Ustawianie czasu bezczynności po którym ekran zostanie przyciemniony.
     * Parametr jest zapamiętywany w EEPROM.
     * @param seconds Czas w sekundach.
     */
    void setFadeTime(int16_t seconds);

    /**
     * Pobieranie czasu bezczynności po którym ekran zostanie przyciemniony.
     * @return Czas w sekundach.
     */
    int16_t getFadeTime();

    /**
     * Ustawianie załączenia korekcji podświetlania przez czujnik.
     * Do prawidłowego działania należy cykliczne wywoływać metodę update.
     * Parametr jest zapamiętywany w EEPROM.
     * @param enabled Sensor załączony.
     */
    void setLightSensor(bool enabled);

    /**
     * Pobieranie załączenia korekcji podświetlania przez czujnik.
     * @return Sensor załączony.
     */
    bool getLightSensor();

private:
    int16_t getMax();
    int16_t getMin();
    int16_t getTargetBrightness(bool energySaving);
    void resetCounterFadeTime(bool energySaving = false);
};

#endif /* CBACKLIGHTDRIVER_H_ */
