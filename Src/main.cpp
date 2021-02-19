#include "main.h"
#include "CSystem.h"
#include "timer.h"
#include "Driver.h"

int main(void)
{
	CSystem::initSystemClock(CSystem::OT_OSCILATOR_EXTERNAL);
	CSystem::initPeripherialsClock();
	CTimer::classInit1000(HAL_GetTick);
	Driver::getInstance().init();
	int i;
	while (1)
	{
		i++;
	}
}

void HAL_SYSTICK_Callback()
{
	CSystem::SysTick_Handler();
}

void Error_Handler(void)
{
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	 tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
