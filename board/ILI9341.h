
#ifndef ILI9341_H
#define ILI9341_H

#include "fsl_gpio.h"
#include "fsl_spi.h"

// Define the ILI9341 struct
typedef struct {
    uint8_t cs_pin;      // Chip Select GPIO pin
    uint8_t dc_pin;      // Data/Command GPIO pin
    uint8_t rst_pin;     // Reset GPIO pin
    SPI_Type *spi_base;  // SPI peripheral base address
} ILI9341_t;

// Function declarations
void ILI9341_Init(ILI9341_t *display);
void ILI9341_SendCommand(ILI9341_t *display, uint8_t command);
void ILI9341_WriteData(ILI9341_t *display, uint8_t data);

#endif // ILI9341_H
