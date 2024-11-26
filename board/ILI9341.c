
#include "ILI9341.h"
#include "fsl_gpio.h"
#include "fsl_spi.h"
#include "fsl_clock.h"
#include "fsl_common.h"
#include "fsl_flexcomm.h"

// Delay utility
static void ILI9341_DelayMs(uint32_t ms) {
    SDK_DelayAtLeastUs(ms * 1000, CLOCK_GetFreq(kCLOCK_CoreSysClk));
}

// Initialize the display
void ILI9341_Init(ILI9341_t *display) {
    // Configure SPI
    spi_master_config_t spi_config;
    SPI_MasterGetDefaultConfig(&spi_config);
    spi_config.baudRate_Bps = 10000000U;  // 10 MHz
    SPI_MasterInit(display->spi_base, &spi_config, CLOCK_GetFreq(kCLOCK_Flexcomm0));

    // Reset the display
    GPIO_PinWrite(GPIO, 0, display->rst_pin, 0);  // Pull reset low
    ILI9341_DelayMs(200);                        // Wait 200ms
    GPIO_PinWrite(GPIO, 0, display->rst_pin, 1);  // Release reset
    ILI9341_DelayMs(200);                        // Wait 200ms
}

// Send a command to the display
void ILI9341_SendCommand(ILI9341_t *display, uint8_t command) {
    GPIO_PinWrite(GPIO, 0, display->dc_pin, 0);  // DC low for command
    GPIO_PinWrite(GPIO, 0, display->cs_pin, 0);  // CS low
    SPI_WriteBlocking(display->spi_base, &command, 1);
    GPIO_PinWrite(GPIO, 0, display->cs_pin, 1);  // CS high
}

// Write data to the display
void ILI9341_WriteData(ILI9341_t *display, uint8_t data) {
    GPIO_PinWrite(GPIO, 0, display->dc_pin, 1);  // DC high for data
    GPIO_PinWrite(GPIO, 0, display->cs_pin, 0);  // CS low
    SPI_WriteBlocking(display->spi_base, &data, 1);
    GPIO_PinWrite(GPIO, 0, display->cs_pin, 1);  // CS high
}
