#include "CSystem.h"


IWDG_HandleTypeDef CSystem::m_hiwdg;

CSystem::TOscilatorType CSystem::m_oscilatorType = CSystem::OT_OSCILATOR_EXTERNAL;
volatile uint64_t CSystem::m_timeMiliseconds;

IInterruptUpdatable* CSystem::m_interruptUpdatable[UPDATABLES_COUNT] = {NULL};
IInterruptUpdatable* CSystem::m_fastInterruptUpdatable[FAST_UPDATABLES_COUNT] = {NULL};

void CSystem::CDelayFunctions::delayms(uint16_t ms)
{
    CSystem::delayMs(ms);
}

void CSystem::CDelayFunctions::delayus(uint16_t ns)
{
    CSystem::delayUs(ns);
}

void CSystem::initSystemClock(TOscilatorType oscilatorType)
{
    m_oscilatorType = oscilatorType;

    HAL_Init();

    __HAL_RCC_AFIO_CLK_ENABLE();
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
    HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
    HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
    HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
    HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
    HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
    HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
    __HAL_AFIO_REMAP_SWJ_NOJTAG();

    switch (oscilatorType)
    {
        case OT_OSCILATOR_EXTERNAL:
            initSystemClockOscExternal();
        break;

        case OT_OSCILATOR_INTERNAL:
            initSystemClockOscInternal();
        break;
    }

    RCC_ClkInitTypeDef RCC_ClkInitStruct;

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

//	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
//	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	__HAL_RCC_PLLI2S_ENABLE();

	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

uint32_t CSystem::getSystemClockFreq()
{
    static const uint32_t m_oscilatorExternalFreq = 8000000;
    static const uint32_t m_oscilatorExternalPLLMul = 9;

    static const uint32_t m_oscilatorInternalFreq = 8000000;
    static const uint32_t m_oscilatorInternalPLLMul = 9;

    switch (m_oscilatorType)
    {
        case OT_OSCILATOR_EXTERNAL:
            return m_oscilatorExternalFreq * m_oscilatorExternalPLLMul;

        case OT_OSCILATOR_INTERNAL:
            return m_oscilatorInternalFreq * m_oscilatorInternalPLLMul;

        default:
            return 0;
    }
}

bool CSystem::initSystemClockOscExternal()
{
	RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL_NONE;

//	RCC_OscInitTypeDef RCC_OscInitStruct;
//	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_HSE;
//	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
//	RCC_OscInitStruct.LSEState = RCC_LSE_ON;
//	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
//	RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_HSE;
//	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
//	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
//	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
//	RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL_NONE;

    return HAL_RCC_OscConfig(&RCC_OscInitStruct) == HAL_OK;
}

bool CSystem::initSystemClockOscInternal()
{

    return false;

}

void CSystem::initPeripherialsClock()
{
	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();
	__GPIOD_CLK_ENABLE();
	__GPIOE_CLK_ENABLE();
}

void CSystem::initBrownOutDetection()
{
    __PWR_CLK_ENABLE();

    PWR_PVDTypeDef sConfigPVD;
    sConfigPVD.PVDLevel = PWR_PVDLEVEL_0;
    sConfigPVD.Mode = PWR_MODE_IT_RISING_FALLING;
    HAL_PWR_PVDConfig(&sConfigPVD);

    NVIC_SetPriority(PVD_IRQn, 0);
    NVIC_EnableIRQ (PVD_IRQn);

    HAL_PWR_EnablePVD();
}

void CSystem::configureWatchdog(uint16_t miliseconds)
{
    int32_t reload = (miliseconds * 40L) / 256;
    if (reload > 0x0FFF)
        reload = 0x0FFF;

    m_hiwdg.Instance = IWDG;
    m_hiwdg.Init.Prescaler = IWDG_PRESCALER_256;
    m_hiwdg.Init.Reload = 4000;
    HAL_IWDG_Init(&m_hiwdg);
//    HAL_IWDG_Start(&m_hiwdg);
}

void CSystem::reloadWatchdog()
{
    if (m_hiwdg.Instance != NULL)
    {
        HAL_IWDG_Refresh(&m_hiwdg);
    }
}

void CSystem::reset()
{
    HAL_NVIC_SystemReset();
}

uint32_t CSystem::getTimeSeconds()
{
    return getTimeMiliseconds() / 1000;
}

uint64_t CSystem::getTimeHSeconds()
{
    return getTimeMiliseconds() / 10;
}

uint64_t CSystem::getTimeMiliseconds()
{
    uint64_t time;
    do
    {
        time = m_timeMiliseconds;
    }
    while (time != m_timeMiliseconds);
    return time;
}

uint64_t CSystem::getTimeMicroseconds()
{
    uint32_t LOAD = SysTick->LOAD;
    uint32_t VAL = SysTick->VAL;
    return getTimeMiliseconds() * 1000 + ((1000UL * (LOAD - VAL)) / (LOAD + 1));
}

void CSystem::delayMs(uint32_t miliseconds)
{
    uint64_t time = getTimeMiliseconds() + miliseconds;
    while (time >= getTimeMiliseconds())
        continue;
}

void CSystem::delayUs(uint32_t microseconds)
{
    uint64_t time = getTimeMicroseconds() + microseconds;
    while (time >= getTimeMicroseconds())
        continue;
}

void CSystem::print(const char *format, ...)
{
#ifdef DEBUG
    va_list ap;
    va_start(ap, format);
    debug_vprintf(format, ap);
    va_end(ap);
#endif
}

void CSystem::vprint(const char *format, va_list ap)
{
#ifdef DEBUG
    debug_vprintf(format, ap);
#endif
}

void CSystem::println(const char *format, ...)
{
#ifdef DEBUG
    va_list ap;
    va_start(ap, format);
    debug_vprintf(format, ap);
    debug_printf("\n");
    va_end(ap);
#endif
}

void CSystem::addInterruptUpdatable(IInterruptUpdatable *interruptUpdatable)
{
	for(uint8_t i=0; i<UPDATABLES_COUNT; i++)
	{
		if(m_interruptUpdatable[i] == NULL)
		{
			m_interruptUpdatable[i] = interruptUpdatable;
			break;
		}
	}
}

void CSystem::addFastInterruptUpdatable(IInterruptUpdatable *interruptUpdatable)
{
	for(uint8_t i=0; i<FAST_UPDATABLES_COUNT; i++)
	{
		if(m_fastInterruptUpdatable[i] == NULL)
		{
			m_fastInterruptUpdatable[i] = interruptUpdatable;
			break;
		}
	}
}

void CSystem::SysTick_Handler()
{
    m_timeMiliseconds++;
    if (m_timeMiliseconds % 8 == 0)
    {
    	for(uint8_t i=0; i<UPDATABLES_COUNT; i++)
    	{
    		if(m_interruptUpdatable[i] != NULL)
    		{
    			m_interruptUpdatable[i]->updateFromInterrupt(125);
    		}
    	}
    }

	for(uint8_t i=0; i<FAST_UPDATABLES_COUNT; i++)
	{
		if(m_fastInterruptUpdatable[i] != NULL)
		{
			m_fastInterruptUpdatable[i]->updateFromInterrupt(1000);
		}
	}

//    uint32_t msp = __get_MSP();
//    static uint32_t max = 0xFFFFFFFF;
//    if (msp < max)
//    {
//        max = msp;
//        debug_printf("Max MSP: %08X\n", max);
//    }
}

extern "C" void PVD_IRQHandler()
{
    HAL_PWR_PVD_IRQHandler();
    NVIC_SystemReset();
}
