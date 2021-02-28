/*
 * Driver.cpp
 *
 *  Created on: Feb 12, 2021
 *      Author: marcin
 */

#include "Driver.h"
#include "CEEPROMVar.h"
#include "pwmController.h"
#include "CGUI.h"

Driver& Driver::getInstance()
{
	static Driver instance;
	return instance;
}

void Driver::init()
{
	initEeprom();
	deviceID = new CDeviceID(0xC000);
	initRtc();
	initBacklight();
	initBuzzer();
	initRadioSpi();
	driverCommunication.init();

	CGUI::getInstance().init(&delayFunctions, deviceID, &rtc, &backlightDriver, &buzzerAsync);
	CGUI::getInstance().show();
}

void Driver::initEeprom(void)
{
	CDriverI2C::TI2CInitParams i2cParams;
	i2cParams.I2Cx = I2C1;
	i2cParams.ClockSpeed = 50000;
	i2cParams.OwnAddress = 0x02;
	i2cParams.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	i2cParams.SDAPin = GPIO_PIN_7;
	i2cParams.SDAPort = GPIOB;
	i2cParams.SCKPin = GPIO_PIN_6;
	i2cParams.SCKPort = GPIOB;
	i2cParams.DMARx = DMA1_Channel7;
	i2cParams.DMATx = DMA1_Channel6;
	i2cParams.DMATxIRQ = DMA1_Channel6_IRQn;
	i2cParams.DMARxIRQ = DMA1_Channel7_IRQn;

	i2c.init(&i2cParams, 128);
	eeprom.init(&i2c, 0xA2);
	CEEPROMMgr::init(&eeprom, true);
}

void Driver::initRtc()
{
	__HAL_RCC_PWR_CLK_ENABLE()
	;
	HAL_PWR_EnableBkUpAccess();
	__HAL_RCC_BKP_CLK_ENABLE()
	;
	rtc.initialize(CRTCalendar::TRCTCLK_LSE, true, &delayFunctions);
	rtc.initRTCIRQ(0, 0);
	if (rtc.getYear() < 2021)
	{
		rtc.setDate(2021, 1, 1);
	}
}

void Driver::initBacklight(void)
{
	__HAL_RCC_TIM2_CLK_ENABLE()
	;
	CPwmController::TInitStruct initStruct;
	initStruct.TIMx = TIM2;
	initStruct.PWMChannel = 3;
	initStruct.TIMx_OCPolarity = TIM_OCPOLARITY_HIGH;
	initStruct.port = GPIOB;
	initStruct.pin = GPIO_PIN_10;
	initStruct.isAdvancedTimer = false;
	backlightDriver.init(&initStruct, CSystem::getSystemClockFreq(), 0, 100);
	__HAL_AFIO_REMAP_TIM2_PARTIAL_2()
	;
	CSystem::addFastInterruptUpdatable(&backlightDriver);
}

void Driver::initBuzzer()
{
	__HAL_RCC_TIM3_CLK_ENABLE()
	;
	CPwmController::TInitStruct initStruct;
	initStruct.TIMx = TIM3;
	initStruct.PWMChannel = 3;
	initStruct.TIMx_OCPolarity = TIM_OCPOLARITY_HIGH;
	initStruct.port = GPIOB;
	initStruct.pin = GPIO_PIN_0;
	initStruct.isAdvancedTimer = false;
	buzzerHrd.init(&initStruct, 4000, CSystem::getSystemClockFreq());
	buzzerAsync.init(&buzzerHrd);
	CSystem::addFastInterruptUpdatable(&buzzerAsync);
}

void Driver::initRadioSpi(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_SPI2_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_14;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
