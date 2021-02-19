/*
 * CDriverI2C.cpp
 *
 *  Created on: 14 sty 2015
 *      Author: Sebastian
 *     Version: 1.0.1
 */

#include "driverI2C.h"

//------------------------------------------------------------------------------------------------------------------------
void CDriverI2C::init(TI2CInitParams * paramI2c, uint16_t pageSize)
//------------------------------------------------------------------------------------------------------------------------
{
#ifdef DEF_HAL_F1
	__HAL_RCC_DMA1_CLK_ENABLE();

	HAL_NVIC_SetPriority(paramI2c->DMATxIRQ, 0, 0);
	HAL_NVIC_EnableIRQ(paramI2c->DMATxIRQ);

	HAL_NVIC_SetPriority(paramI2c->DMARxIRQ, 0, 0);
	HAL_NVIC_EnableIRQ(paramI2c->DMARxIRQ);

    if (paramI2c->I2Cx == I2C1)
    {
        __I2C1_CLK_ENABLE();

        if (paramI2c->SCKPort == GPIOB && paramI2c->SCKPin == GPIO_PIN_8)
        {
            __HAL_AFIO_REMAP_I2C1_ENABLE();
        }
    }
    else if (paramI2c->I2Cx == I2C2)
    {
        __I2C2_CLK_ENABLE();
    }
#endif

    __I2C1_FORCE_RESET();
    __I2C1_RELEASE_RESET();

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;

#ifdef DEF_HAL_F4
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
#else
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
#endif

#if defined DEF_HAL_F2 || defined DEF_HAL_F4
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1; // dla GPIO_AF4_I2C2 i GPIO_AF4_I2C3 jest ta sama wartość
#endif

    GPIO_InitStruct.Pin = paramI2c->SDAPin;
    HAL_GPIO_Init(paramI2c->SDAPort, &GPIO_InitStruct);

    GPIO_InitStruct.Pin =  paramI2c->SCKPin;
    HAL_GPIO_Init(paramI2c->SCKPort, &GPIO_InitStruct);


#if defined DEF_HAL_F2 || defined DEF_HAL_F4
    if (paramI2c->I2Cx == I2C1)
    {
        __I2C1_CLK_ENABLE();
    }
    else if (paramI2c->I2Cx == I2C2)
    {
        __I2C2_CLK_ENABLE();
    }
    else if (paramI2c->I2Cx == I2C3)
    {
        __I2C3_CLK_ENABLE();
    }
#endif

    hi2c.Instance = paramI2c->I2Cx;
    hi2c.Init.ClockSpeed = paramI2c->ClockSpeed;
    hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c.Init.OwnAddress1 = 0;
    hi2c.Init.AddressingMode = paramI2c->AddressingMode;
    hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
    hi2c.Init.OwnAddress2 = 0;
    hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
    hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;
    HAL_I2C_Init(&hi2c);

    setAddrLen(1);
    m_pageSize = pageSize;
    m_HALtimeout = 3;

#ifdef DEF_HAL_F1
    m_dma_RX.Instance = paramI2c->DMARx;
    m_dma_RX.Init.Direction = DMA_PERIPH_TO_MEMORY;
    m_dma_RX.Init.PeriphInc = DMA_PINC_DISABLE;
    m_dma_RX.Init.MemInc = DMA_MINC_ENABLE;
    m_dma_RX.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    m_dma_RX.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    m_dma_RX.Init.Mode = DMA_NORMAL;
    m_dma_RX.Init.Priority = DMA_PRIORITY_LOW;
    HAL_DMA_Init(&m_dma_RX);

    __HAL_LINKDMA(&hi2c, hdmarx, m_dma_RX);

    m_dma_TX.Instance = paramI2c->DMATx;
    m_dma_TX.Init.Direction = DMA_MEMORY_TO_PERIPH;
    m_dma_TX.Init.PeriphInc = DMA_PINC_DISABLE;
    m_dma_TX.Init.MemInc = DMA_MINC_ENABLE;
    m_dma_TX.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    m_dma_TX.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    m_dma_TX.Init.Mode = DMA_NORMAL;
    m_dma_TX.Init.Priority = DMA_PRIORITY_LOW;
    HAL_DMA_Init(&m_dma_TX);

    __HAL_LINKDMA(&hi2c, hdmatx, m_dma_TX);
#endif
}

//------------------------------------------------------------------------------------------------------------------------
void CDriverI2C::setAddrLen(uint8_t addrLen)
//------------------------------------------------------------------------------------------------------------------------
{
	if(addrLen == 1)
	{
		m_internalAdressLenght = I2C_MEMADD_SIZE_8BIT;
	}
	else
	{
		m_internalAdressLenght = I2C_MEMADD_SIZE_16BIT;
	}
}

//------------------------------------------------------------------------------------------------------------------------
void CDriverI2C::setHalTimeout(uint32_t Timeout)
//------------------------------------------------------------------------------------------------------------------------
{
	m_HALtimeout = Timeout;
}

//------------------------------------------------------------------------------------------------------------------------
uint32_t CDriverI2C::writeByte(uint8_t slaveAddressWrite, uint16_t address, uint8_t data)
//------------------------------------------------------------------------------------------------------------------------
{
#ifdef DEF_HAL_F1
    HAL_StatusTypeDef status = HAL_OK;

	status = HAL_I2C_Mem_Write_DMA(&hi2c , (uint16_t)slaveAddressWrite, address, m_internalAdressLenght, &data, 1);

    if (status != HAL_OK)
    {
        return status;
    }

	while (HAL_I2C_GetState(&hi2c) != HAL_I2C_STATE_READY);

    return HAL_I2C_IsDeviceReady(&hi2c, slaveAddressWrite, 150, m_HALtimeout);
#else
	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Mem_Write(&hi2c, slaveAddressWrite, address, m_internalAdressLenght, &data, 1, m_HALtimeout);

	if (status)
	{
		return status;
	}

	return HAL_I2C_IsDeviceReady(&hi2c, slaveAddressWrite, 150, m_HALtimeout);
#endif
}

//------------------------------------------------------------------------------------------------------------------------
uint32_t CDriverI2C::readByte(uint8_t slaveAddressRead, uint16_t address, uint8_t* data)
//------------------------------------------------------------------------------------------------------------------------
{
#ifdef DEF_HAL_F1
    HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Mem_Read_DMA(&hi2c, slaveAddressRead, address, m_internalAdressLenght, data, 1);
    if (status != HAL_OK)
    {
        return status;
    }

	while (HAL_I2C_GetState(&hi2c) != HAL_I2C_STATE_READY);

	return HAL_I2C_IsDeviceReady(&hi2c, slaveAddressRead, 150, m_HALtimeout);
#else
	return HAL_I2C_Mem_Read(&hi2c, slaveAddressRead, address, m_internalAdressLenght, data, 1, m_HALtimeout);
#endif
}

//------------------------------------------------------------------------------------------------------------------------
uint32_t CDriverI2C::writeBlock(uint8_t slaveAddressWrite, uint16_t address, void* dataBuffer, uint16_t dataLength)
//------------------------------------------------------------------------------------------------------------------------
{
    HAL_StatusTypeDef status = HAL_OK;

    while (dataLength)
    {
        uint16_t size = (m_pageSize * ((address / m_pageSize) + 1)) - address;

        if (size > dataLength)
        {
            size = dataLength;
        }

#ifdef DEF_HAL_F1
        status = HAL_I2C_Mem_Write_DMA(&hi2c , (uint16_t)slaveAddressWrite, address, m_internalAdressLenght, (uint8_t*) dataBuffer, size);
        if (status != HAL_OK)
        {
            return status;
        }

    	while (HAL_I2C_GetState(&hi2c) != HAL_I2C_STATE_READY);
#else
        status = HAL_I2C_Mem_Write(&hi2c, slaveAddressWrite, address, m_internalAdressLenght, (uint8_t*) dataBuffer, size, m_HALtimeout);
        if (status != HAL_OK)
        {
            return status;
        }
#endif

        status = HAL_I2C_IsDeviceReady(&hi2c, slaveAddressWrite, 150, m_HALtimeout);
        if (status != HAL_OK)
        {
            return status;
        }

        address += size;
        dataBuffer = (void*)((uint32_t)dataBuffer + size);
        dataLength -= size;
    }

    return status;
}

//------------------------------------------------------------------------------------------------------------------------
uint32_t CDriverI2C::readBlock(uint8_t slaveAddressRead, uint16_t address, void* dataBuffer, uint16_t dataLength)
//------------------------------------------------------------------------------------------------------------------------
{
#ifdef DEF_HAL_F1
    HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Mem_Read_DMA(&hi2c, slaveAddressRead, address, m_internalAdressLenght, (uint8_t*) dataBuffer, dataLength);
    if (status != HAL_OK)
    {
        return status;
    }

	while (HAL_I2C_GetState(&hi2c) != HAL_I2C_STATE_READY);

	return HAL_I2C_IsDeviceReady(&hi2c, slaveAddressRead, 150, m_HALtimeout);
#else
	return HAL_I2C_Mem_Read(&hi2c, slaveAddressRead, address, m_internalAdressLenght, (uint8_t*) dataBuffer, dataLength, 3);
#endif
}

//------------------------------------------------------------------------------------------------------------------------
uint32_t CDriverI2C::updateByte(uint8_t slaveAddressWrite, uint16_t address, uint8_t data)
//------------------------------------------------------------------------------------------------------------------------
{
	uint8_t dana = 0;
	HAL_StatusTypeDef status = HAL_OK;
	status = (HAL_StatusTypeDef) readByte(slaveAddressWrite, address, &dana);
	if (status)
	{
		return status;
	}
	if (dana != data)
	{
		status = (HAL_StatusTypeDef) writeByte(slaveAddressWrite, address, data);
		if (status)
		{
			return status;
		}
	}
	return status;
}

//------------------------------------------------------------------------------------------------------------------------
uint32_t CDriverI2C::updateBlock(uint8_t slaveAddressWrite, uint16_t address, void* dataBuffer, uint16_t dataLength)
//------------------------------------------------------------------------------------------------------------------------
{
	HAL_StatusTypeDef status = HAL_OK;
	uint8_t *dataBufer = (uint8_t *) dataBuffer;
	for (uint16_t i = 0; i < dataLength; i++)
	{
		status = (HAL_StatusTypeDef) updateByte(slaveAddressWrite, address + i, dataBufer[i]);
		if (status)
		{
			return status;
		}
	}
	return status;
}

#ifdef DEF_HAL_F1
void CDriverI2C::DMARxIrqHandler()
{
	HAL_DMA_IRQHandler(&m_dma_RX);
}

void CDriverI2C::DMATxIrqHandler()
{
	HAL_DMA_IRQHandler(&m_dma_TX);
}
#endif

