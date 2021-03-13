#ifndef RFM22_HRD_H_
#define RFM22_HRD_H_

/**************/
/*STM32L0 VERSION*/
/**************/

/** Interrupt request pin of transceiver */
#define RFM22_INT_PORT_ENABLE()     __GPIOB_CLK_ENABLE()
#define RFM22_INT_PORT              GPIOB
#define RFM22_INT_BIT               GPIO_PIN_11

/** Interrupt NVIC config*/
#define RFM22_IRQ                   EXTI15_10_IRQn

#define RFM22_SPI					SPI2
#define RFM22_SPI_HANDLE            hspi2

/** SDN pin */
#define RFM22_SDN_PORT_ENABLE()     __GPIOC_CLK_ENABLE()
#define RFM22_SDN_PORT              GPIOC
#define RFM22_SDN_BIT               GPIO_PIN_6

/** chip select pin */
#define RFM22_SPI_CS_PORT_ENABLE()  __GPIOB_CLK_ENABLE()
#define RFM22_SPI_CS_PORT           GPIOB
#define RFM22_SPI_CS_BIT            GPIO_PIN_12

#define RFM22_VCC_PORT_ENABLE()  __GPIOC_CLK_ENABLE()
#define RFM22_VCC_PORT	GPIOC
#define RFM22_VCC_BIT	GPIO_PIN_8


#endif //RFM22_HRD_H_
