/**
 * @file CRTCalendar.cpp
 *
 * @author Marcin Sporysz
 * @date 12/05/2012
 */

#include "CRTCalendar.h"
#include "CTimeFix.h"


volatile bool CRTCalendar::secondsChanged = true;
bool CRTCalendar::useCacheInterrupt;
IDelayFunctions* CRTCalendar::delayFn;

CRTCalendar::TRTCInitResult CRTCalendar::initialize(TRTCClock clkSrc, bool useChacheIT, IDelayFunctions* delays)
{
	useCacheInterrupt = useChacheIT;
	delayFn = delays;

	RCC->APB1ENR |= RCC_APB1ENR_BKPEN;
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_DBP;

	switch (clkSrc)
	{
		case TRCTCLK_LSI:
			RCC->CSR |= RCC_CSR_LSION;
			if(!waitForRegisterFlag(&RCC->CSR,RCC_CSR_LSIRDY, delayFn))
			{
				initStatus = TRTC_FAIL;
				return initStatus;
			}
			break;

		case TRCTCLK_LSE:
			break;
		default:
			break;
	}

	if(!(RCC->BDCR & RCC_BDCR_RTCEN))
	{


		RCC->BDCR |= RCC_BDCR_BDRST;
		RCC->BDCR &= ~RCC_BDCR_BDRST;


		switch(clkSrc)
		{
			case TRCTCLK_LSI:
				RCC->BDCR |= RCC_BDCR_RTCSEL_LSI;
				break;

			case TRCTCLK_LSE:
				RCC->BDCR |= RCC_BDCR_LSEON;
				if(!waitForRegisterFlag(&RCC->BDCR,RCC_BDCR_LSERDY, delayFn))
				{
					initStatus = TRTC_FAIL;
					return initStatus;
				}
				RCC->BDCR |= RCC_BDCR_RTCSEL_LSE;
				break;

			default:
				break;
		}


		RCC->BDCR |= RCC_BDCR_RTCEN;

		if(!waitForSync())
		{
			initStatus = TRTC_FAIL;
			return initStatus;
		}
		if(!waitForTask())
		{
			initStatus = TRTC_FAIL;
			return initStatus;
		}

		RTC->CRL |= RTC_CRL_CNF;

		switch(clkSrc)
		{
		case TRCTCLK_LSE:
			RTC->PRLL = 0x7fff;
			break;
		case TRCTCLK_LSI:
			RTC->PRLL = 0x9c40;
			break;

		default:
			break;
		}

		RTC->CRL &= ~RTC_CRL_CNF;
		if(!waitForTask())
		{
			initStatus = TRTC_FAIL;
			return initStatus;
		}
		setDate(INITIAL_YEAR,1,1);
		setTime(12,0,0);
		initStatus = TRTC_OK_RESET;
	}else
	{
		if(!waitForSync())
		{
			initStatus = TRTC_FAIL;
			return initStatus;
		}
		initStatus = TRTC_OK;
	}

	PWR->CR &= ~PWR_CR_DBP;

    return initStatus;
}

uint8_t CRTCalendar::getWeekDay()
{
	return getTimeStruct()->tm_wday;
}

uint8_t CRTCalendar::getDay()
{
	return getTimeStruct()->tm_mday;
}

uint8_t CRTCalendar::getMonth()
{
	return getTimeStruct()->tm_mon+1;
}

uint16_t CRTCalendar::getYear()
{
	return getTimeStruct()->tm_year + 1900;
}

uint8_t CRTCalendar::getSeconds()
{
	return getTimeStruct()->tm_sec;
}

uint8_t CRTCalendar::getMinutes()
{
	return getTimeStruct()->tm_min;
}

uint8_t CRTCalendar::getHours()
{
	return getTimeStruct()->tm_hour;
}

void CRTCalendar::setTime(uint8_t hr, uint8_t min, uint8_t sec)
{
	tm* o = getTimeStruct();
	o->tm_hour = hr;
	o->tm_min = min;
	o->tm_sec = sec;
	writeRTC((uint32_t)CTimeFix::mktimeFix(o));
	secondsChanged = true;

}

void CRTCalendar::setDate(uint16_t yr, uint8_t month, uint8_t day)
{
	tm* o = getTimeStruct();
	o->tm_year =  yr - 1900;
	o->tm_mon = month - 1;
	o->tm_mday = day;
	writeRTC((uint32_t)CTimeFix::mktimeFix(o));
	secondsChanged = true;
}

tm *CRTCalendar::getTimeStruct()
{
	if(secondsChanged || useCacheInterrupt == false)
	{
		secondsChanged = false;

		uint16_t tmp = 0;
		tmp = RTC->CNTL;
		time_t t = (((uint32_t)RTC->CNTH << 16 ) | tmp);
		cachedTimeStruct = CTimeFix::localtimeFix(&t);
	}
	return cachedTimeStruct;
}

bool CRTCalendar::writeRTC(uint32_t counter)
{
	PWR->CR |= PWR_CR_DBP;
	if(!waitForTask()) return false;
	RTC->CRL |= RTC_CRL_CNF;
	RTC->CNTH = counter >> 16;
	RTC->CNTL = counter & 0xffff;
	RTC->CRL &= ~RTC_CRL_CNF;
	if(!waitForTask()) return false;

	PWR->CR &= ~PWR_CR_DBP;
	return true;
}

uint16_t CRTCalendar::getMinutesOfDay()
{
	tm* o = getTimeStruct();
	return o->tm_hour * 60 + o->tm_min;
}

bool CRTCalendar::getLeapYear(uint16_t year)
{
	 return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

bool CRTCalendar::waitForRegisterFlag(volatile uint32_t* reg, uint32_t bit, IDelayFunctions* dl)
{
	uint32_t c = REGISTER_FLAG_TIMEOUT_MS;
	while(!((*reg) & bit) && c)
	{
		dl->delayms(1);
		c--;
	}
	return c;
}

void CRTCalendar::RTCIRQHandler()
{
	secondsChanged = true;
}

void CRTCalendar::initRTCIRQ(uint8_t preemPrio, uint8_t subPrio)
{
	RTC->CRL |= RTC_CRL_CNF;
	waitForTask();
#ifndef USE_HAL_DRIVER
	NVIC_InitTypeDef i;
	i.NVIC_IRQChannel = RTC_IRQn;
	i.NVIC_IRQChannelPreemptionPriority = preemPrio;
	i.NVIC_IRQChannelSubPriority = subPrio;
	i.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&i);
#else
    HAL_NVIC_SetPriority(RTC_IRQn, preemPrio, subPrio);
    HAL_NVIC_EnableIRQ(RTC_IRQn);

//  Obsługa przerwania z pominięciem metod HAL
//    extern "C" void RTC_IRQHandler()
//    {
//    	ITStatus bitstatus = RESET;
//    	bitstatus = (ITStatus)(RTC->CRL & RTC_IT_SEC);
//    	if (((RTC->CRH & RTC_IT_SEC) != (uint16_t)RESET) && (bitstatus != (uint16_t)RESET))
//    	{
//    		RTC->CRL &= (uint16_t)~RTC_IT_SEC;
//    		m_rtc.RTCIRQHandler();
//    	}
//    }

#endif

    RTC->CRH |= RTC_IT_SEC;
	waitForTask();
}

inline bool CRTCalendar::waitForSync()
{
	RTC->CRL &= ~RTC_CRL_RSF;
	return waitForRegisterFlag(&RTC->CRL,RTC_CRL_RSF,delayFn);
}

inline bool CRTCalendar::waitForTask()
{
	return 	waitForRegisterFlag(&RTC->CRL,RTC_CRL_RTOFF,delayFn);
}

int32_t CRTCalendar::getSecondsPassedSince(time_t then)
{
	time_t end = getTotalTime();
	return difftime(then,end);
}

time_t CRTCalendar::getTotalTime()
{
	return CTimeFix::mktimeFix(getTimeStruct());
}

bool CRTCalendar::waitForRegisterFlag(volatile uint16_t* reg, uint16_t bit, IDelayFunctions* dl)
{
	volatile uint32_t c = REGISTER_FLAG_TIMEOUT_MS;
	while(!((*reg) & bit) && c)
	{
		dl->delayms(1);
		c--;
	}
	return c;
}

void CRTCalendar::setWeekDay(uint8_t d)
{
	const uint32_t zeroSeconds = 259200;
	uint32_t currDaySeconds = getMinutesOfDay() * 60;
	uint32_t newDaySeconds = zeroSeconds + (d * 86400) + currDaySeconds;
	writeRTC(newDaySeconds);
	secondsChanged = true;
}

CRTCalendar::TRTCInitResult CRTCalendar::getInitStatus()
{
	return initStatus;
}

bool CRTCalendar::isDateTimeSet()
{
    tm* timeStruct = getTimeStruct();
    uint16_t year = timeStruct->tm_year + 1900;
    return isDateTimeSet(year, timeStruct->tm_mon + 1);
}

bool CRTCalendar::isDateTimeSet(uint16_t year, uint8_t month)
{
    return (year > INITIAL_YEAR || (year == INITIAL_YEAR && month > 1));
}

