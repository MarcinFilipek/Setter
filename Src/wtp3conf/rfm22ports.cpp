#include "rfm22ports.h"
#include "rfm22HRD.h"
#include "rfm22driver.h"
#include "hal.h"

SPI_HandleTypeDef RFM22_SPI_HANDLE;

//------przerwanie INTx--------------
uint8_t rfm22ports_isINTActive()
{
    return HAL_GPIO_ReadPin(RFM22_INT_PORT, RFM22_INT_BIT) == GPIO_PIN_RESET;
}

void rfm22ports_clearIntFlag()
{
    __HAL_GPIO_EXTI_CLEAR_IT(RFM22_INT_BIT);
    HAL_NVIC_ClearPendingIRQ(RFM22_IRQ);
}

void rfm22ports_activateInt()
{
    rfm22ports_clearIntFlag();
    HAL_NVIC_EnableIRQ(RFM22_IRQ);
}

void rfm22ports_deactivateInt()
{
    HAL_NVIC_DisableIRQ(RFM22_IRQ);
}

void rfm22ports_initIntPort()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RFM22_INT_PORT_ENABLE();

    GPIO_InitStruct.Pin = RFM22_INT_BIT;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(RFM22_INT_PORT, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(RFM22_IRQ, 1, 0);
}

void rfm22ports_initVccPort()
{
}

void rfm22ports_setVcc(uint8_t value)
{
}

void rfm22ports_initSDNPort()
{
    //od razu po przelaczeniu na wyjscie stan wysoki (shutdown)

    GPIO_InitTypeDef GPIO_InitStruct;

    RFM22_SDN_PORT_ENABLE();

    GPIO_InitStruct.Pin = RFM22_SDN_BIT;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
    HAL_GPIO_Init(RFM22_SDN_PORT, &GPIO_InitStruct);
    //HAL_GPIO_WritePin(RFM22_SDN_PORT, RFM22_SDN_BIT, GPIO_PIN_SET);
}

void rfm22ports_setSDN(uint8_t value)
{
    HAL_GPIO_WritePin(RFM22_SDN_PORT, RFM22_SDN_BIT, value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

uint8_t rfm22ports_getResetMethod()
{
    return RFM22PORTS_RESET_SDN;
}

void rfm22ports_initSPI()
{
	RFM22_SPI_HANDLE.Instance = RFM22_SPI;
	RFM22_SPI_HANDLE.Init.Mode = SPI_MODE_MASTER;
	RFM22_SPI_HANDLE.Init.Direction = SPI_DIRECTION_2LINES;
	RFM22_SPI_HANDLE.Init.DataSize = SPI_DATASIZE_8BIT;
	RFM22_SPI_HANDLE.Init.CLKPolarity = SPI_POLARITY_LOW;
	RFM22_SPI_HANDLE.Init.CLKPhase = SPI_PHASE_1EDGE;
	RFM22_SPI_HANDLE.Init.NSS = SPI_NSS_SOFT;
	RFM22_SPI_HANDLE.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	RFM22_SPI_HANDLE.Init.FirstBit = SPI_FIRSTBIT_MSB;
	RFM22_SPI_HANDLE.Init.TIMode = SPI_TIMODE_DISABLED;
	RFM22_SPI_HANDLE.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	RFM22_SPI_HANDLE.Init.CRCPolynomial = 10;
	HAL_SPI_Init(&RFM22_SPI_HANDLE);
}

void rfm22ports_deinitSPI()
{
	HAL_SPI_DeInit(&RFM22_SPI_HANDLE);
}

uint8_t rfm22ports_trans(uint8_t address, uint8_t value)
{
    uint8_t txData[2] = {address, value};
    uint8_t feedback[2] = {0, 0};

    HAL_GPIO_WritePin(RFM22_SPI_CS_PORT, RFM22_SPI_CS_BIT, GPIO_PIN_RESET);

    HAL_SPI_TransmitReceive(&RFM22_SPI_HANDLE, txData, feedback, 2, 50);

    HAL_GPIO_WritePin(RFM22_SPI_CS_PORT, RFM22_SPI_CS_BIT, GPIO_PIN_SET);

    return feedback[1];
}

void rfm22ports_burst(uint8_t address, uint8_t length, uint8_t *values)
{
    uint8_t i;

    HAL_GPIO_WritePin(RFM22_SPI_CS_PORT, RFM22_SPI_CS_BIT, GPIO_PIN_RESET);

    HAL_SPI_TransmitReceive(&RFM22_SPI_HANDLE, &address, &i, 1, 50);
    HAL_SPI_TransmitReceive(&RFM22_SPI_HANDLE, values, values, length, 300);

    HAL_GPIO_WritePin(RFM22_SPI_CS_PORT, RFM22_SPI_CS_BIT, GPIO_PIN_SET);
}

void rfm22ports_delay(uint16_t ms)
{
    HAL_Delay(ms);
}

