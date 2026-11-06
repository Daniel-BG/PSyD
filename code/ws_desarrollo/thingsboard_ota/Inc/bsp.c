#include <bsp.h>
#include <stdio.h>
#include <stdarg.h>


/////////////////////////// UART /////////////////////////////
void UART_FlushRX(USART_TypeDef *usart) {
    uint8_t dummy;
    while (UART_ReadDataRegisterNonBlocking(usart, &dummy));
}

//Transmit a full string
void UART_WriteString(USART_TypeDef *usart, const char *str) {
    while (*str)
    	UART_TransmitByte(usart, *str++);
}

void UART_WriteBytes(USART_TypeDef *usart, const uint8_t *buf, uint16_t len) {
    for (uint16_t i = 0; i < len; i++) {
        UART_TransmitByte(usart, buf[i]);
    }
}


/////////////////////////// I2C /////////////////////////////
/* Writes 1 byte to a specific register inside the sensor */
void I2C_Reg_Write(I2C_TypeDef *I2Cx, uint8_t slave_addr, uint8_t reg, uint8_t val) {
    //Issue START + Address (Write Mode, expecting 2 bytes)
    I2C_Start(I2Cx, slave_addr, I2C_WRITE, 2);

    //Write Target Register Address
    I2C_Write(I2Cx, reg);

    //Write Value
    I2C_Write(I2Cx, val);

    //Wait for hardware to finish clocking out NBYTES (2 bytes)
	I2C_Wait_TC(I2Cx);

	//Manually issue STOP condition
	I2C_Stop(I2Cx);
}

/* Reads 'len' sequential bytes starting from 'reg' */
void I2C_Reg_Read_Seq(I2C_TypeDef *I2Cx, uint8_t slave_addr, uint8_t reg, uint8_t *dest, uint32_t len) {
    // ================= PHASE 1: WRITE REGISTER ADDRESS =================
    // Issue START + Slave Address (Write Mode, 1 Byte payload)
    I2C_Start(I2Cx, slave_addr, I2C_WRITE, 1);

    // Send the register address we want to read
    I2C_Write(I2Cx, reg);

    // Wait for write phase to complete before issuing Repeated START
    // for the READ operation
    I2C_Wait_TC(I2Cx);

    // ================= PHASE 2: READ DATA PAYLOAD =================
    // Issue REPEATED START + Slave Address (Read Mode, 'len' Bytes)
    I2C_Start(I2Cx, slave_addr, I2C_READ, len);

    // Read sequential bytes from the sensor
    for (uint32_t i = 0; i < len; i++)
        dest[i] = I2C_Read(I2Cx);

    // Wait for hardware to complete receiving all NBYTES
	I2C_Wait_TC(I2Cx);

	// Manually issue STOP condition
	I2C_Stop(I2Cx);
}


/////////////////////////// SYSTICK /////////////////////////////

volatile uint32_t msTicks = 0;
void SysTick_Handler(void) {
    msTicks++;
}




/////////////////////////// DEBUG /////////////////////////////

void Debug_Printf(const char *fmt, ...) {
    char buf[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    UART_WriteString(USART6, buf);
}

