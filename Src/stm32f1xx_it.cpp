#include "stm32f1xx_it.h"
#include "hal.h"
#include "Driver.h"
#include "rfm22HRD.h"
#include "rfm22frame.h"

void NMI_Handler(void)
{

}

/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void)
{
	while (1)
	{
	}
}

/**
 * @brief This function handles Memory management fault.
 */
void MemManage_Handler(void)
{
	while (1)
	{
	}
}

/**
 * @brief This function handles Prefetch fault, memory access fault.
 */
void BusFault_Handler(void)
{
	while (1)
	{
	}
}

/**
 * @brief This function handles Undefined instruction or illegal state.
 */
void UsageFault_Handler(void)
{
	while (1)
	{
	}
}

/**
 * @brief This function handles System service call via SWI instruction.
 */
void SVC_Handler(void)
{}

/**
 * @brief This function handles Debug monitor.
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief This function handles Pendable request for system service.
 */
void PendSV_Handler(void)
{
}

/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void DMA1_Channel6_IRQHandler(void)
{
	Driver::getInstance().getI2C()->DMATxIrqHandler();
}

void DMA1_Channel7_IRQHandler(void)
{
	Driver::getInstance().getI2C()->DMARxIrqHandler();
}

void RTC_IRQHandler()
{
	ITStatus bitstatus = RESET;
	bitstatus = (ITStatus)(RTC->CRL & RTC_IT_SEC);
	if (((RTC->CRH & RTC_IT_SEC) != (uint16_t)RESET) && (bitstatus != (uint16_t)RESET))
	{
		RTC->CRL &= (uint16_t)~RTC_IT_SEC;
		Driver::getInstance().getRtc()->RTCIRQHandler();
	}
}

void EXTI15_10_IRQHandler()
{
	HAL_GPIO_EXTI_IRQHandler(RFM22_INT_BIT);
	rfm22frame_isr();
}
