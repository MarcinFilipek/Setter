/*
 * CBacklightDriver.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: krzysiek
 */

#include "CBacklightDriver.h"

CBacklightDriver::CBacklightDriver()
{
}

void CBacklightDriver::init(CPwmController::TInitStruct *initStruct, uint32_t systemClockFrequency, int8_t minPWM,
        int8_t maxPWM)
{
    m_minPWM = minPWM;
    m_maxPWM = maxPWM;

    m_pwmController.init( //
            initStruct,
            1000,
            systemClockFrequency,
            1000);

    m_dimBrightness.initVar(DEFAULT_DIM_BRIGHTNESS);
    m_normalBrightness.initVar(DEFAULT_NORMAL_BRIGHTNESS);
    m_fadeTime.initVar(DEFAULT_FADE_TIME);
    m_lightSensor.initVar(DEFAULT_LIGHT_SENSOR);

    m_currentBrightness = 0;
    startAutomaticMode();
}

void CBacklightDriver::startAutomaticMode()
{
    m_mode = MODE_AUTO;
    m_targetBrightness = getMax();
    resetCounterFadeTime();
}

void CBacklightDriver::startFixedMode(int8_t percent)
{
    m_mode = MODE_FIXED;
    m_targetBrightness = percent * 10;
}

void CBacklightDriver::update(bool interact, bool energySaving, int8_t lightSensorPercent)
{
    if ((interact && m_mode == MODE_AUTO) || (energySaving != m_energySaving))
    {
        m_energySaving = energySaving;
        m_targetBrightness = getMax();
        resetCounterFadeTime(energySaving);
    }

    m_lightSensorPercent = lightSensorPercent;
}

void CBacklightDriver::updateFromInterrupt(uint16_t updateFrequency)
{
    int32_t intervalMS = 1000 / updateFrequency;
    int16_t targetBrightness = getTargetBrightness(m_energySaving);

    if (intervalMS < 1)
    {
        intervalMS = 1;
    }

    if (m_counterFadeTime > 0)
    {
        m_counterFadeTime -= intervalMS;
    }

    if (m_mode == MODE_AUTO)
    {
        if (m_counterFadeTime <= 0)
        {
            m_targetBrightness = getMin();
        }
    }

    if (m_currentBrightness > targetBrightness)
    {
        m_currentBrightness -= intervalMS * STEP_MULTIPLIER;
        if (m_currentBrightness < targetBrightness)
        {
            m_currentBrightness = targetBrightness;
        }
    }

    if (m_currentBrightness < targetBrightness)
    {
        m_currentBrightness += intervalMS * STEP_MULTIPLIER;
        if (m_currentBrightness > targetBrightness)
        {
            m_currentBrightness = targetBrightness;
        }
    }

    if (m_currentBrightness <= 0)
    {
        m_pwmController.setPulseWidth(0);
    }
    else
    {
        int32_t brightness = m_currentBrightness;

        //zmiana charakterystyki z linowej na paraboliczną (dla bardziej jednorodnego sterownia jasnością)
        brightness = ((brightness + FACTOR_LINEAR) * brightness) / (1000 + FACTOR_LINEAR);

        //ograniczanie zakresu sterowania (od m_minPWM do m_maxBrightness)
        brightness = (m_minPWM * 10) + (brightness * (m_maxPWM - m_minPWM)) / 100;

        m_pwmController.setPulseWidth(brightness);
    }
}

void CBacklightDriver::setDimBrightness(int8_t percent)
{
    m_dimBrightness = percent;
}

int8_t CBacklightDriver::getDimBrightness()
{
    return m_dimBrightness;
}

void CBacklightDriver::setNormalBrightness(int8_t percent)
{
    m_normalBrightness = percent;
}

int8_t CBacklightDriver::getNormalBrightness()
{
    return m_normalBrightness;
}

void CBacklightDriver::setFadeTime(int16_t seconds)
{
    m_fadeTime = seconds;
    resetCounterFadeTime();
}

int16_t CBacklightDriver::getFadeTime()
{
    return m_fadeTime;
}

void CBacklightDriver::setLightSensor(bool enabled)
{
    m_lightSensor = enabled;
}

bool CBacklightDriver::getLightSensor()
{
    return m_lightSensor;
}

int16_t CBacklightDriver::getMax()
{
    return m_normalBrightness * 10;
}

int16_t CBacklightDriver::getMin()
{
    return m_dimBrightness * 10;
}

int16_t CBacklightDriver::getTargetBrightness(bool energySaving)
{
    int32_t targetBrightness = m_targetBrightness;

    if (energySaving)
    {
        targetBrightness = (targetBrightness * (100 - FACTOR_ENERGY_SAVING)) / 100;
    }

    if (m_lightSensor)
    {
        int16_t factor;
        if (m_lightSensorPercent > LIGHT_SENSOR_THRESHOLD_MAX)
        {
            factor = LIGHT_SENSOR_BRIGHTNESS_MAX;
        }
        else
        {
            if (m_lightSensorPercent < LIGHT_SENSOR_THRESHOLD_MIN)
            {
                factor = LIGHT_SENSOR_BRIGHTNESS_MIN;
            }
            else
            {
                factor = (m_lightSensorPercent - LIGHT_SENSOR_THRESHOLD_MIN);
                factor *= (LIGHT_SENSOR_BRIGHTNESS_MAX - LIGHT_SENSOR_BRIGHTNESS_MIN);
                factor /= (LIGHT_SENSOR_THRESHOLD_MAX - LIGHT_SENSOR_THRESHOLD_MIN);
                factor += LIGHT_SENSOR_BRIGHTNESS_MIN;
            }
        }
        targetBrightness = (targetBrightness * factor) / 100;
    }

    return targetBrightness;
}

void CBacklightDriver::resetCounterFadeTime(bool energySaving)
{
    if (energySaving && getFadeTime() > MAX_FADE_TIME_ENERGY_SAVING)
    {
        m_counterFadeTime = MAX_FADE_TIME_ENERGY_SAVING * 1000;
    }
    else
    {
        m_counterFadeTime = getFadeTime() * 1000;
    }
}
