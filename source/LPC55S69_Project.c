#include "board.h"
#include "pin_mux.h"
#include "fsl_flexcomm.h"
#include "fsl_gpio.h"
#include "fsl_iocon.h"
#include "fsl_spi.h"
#include "ILI9341.h"
#include "peripherals.h"
#include "fsl_clock.h"
#include "clock_config.h"

// Dedicated SPI Pin Definitions
#define HS_MOSI_PIN   26  // PIO0_26 = MOSI
#define HS_SSEL_PIN   1   // PIO1_1  = CS (Manual GPIO control)
#define HS_SCK_PIN    2   // PIO1_2  = SCK
#define HS_MISO_PIN   3   // PIO1_3  = MISO

// GPIO for Data/Command (DC) and RESET
#define TFT_DC_PIN    10  // GPIO pin for DC
#define TFT_RST_PIN   11  // GPIO pin for RESET

// SPI instance
#define SPI_INSTANCE  8   // Flexcomm 8 SPI

// Prototypes
void InitPins(void);
void ConfigureSPIPins(void);
void ConfigureSPI(void);

spi_master_handle_t spiHandle;
volatile bool spiTransferCompleted = false;

void SPI_Callback(SPI_Type *base, spi_master_handle_t *handle, status_t status, void *userData) {
    if (status == kStatus_Success) {
        spiTransferCompleted = true;
    }
}

int main(void) {
    // Initialize board and peripherals
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    // Initialize GPIO pins and configure SPI
    InitPins();
    ConfigureSPIPins();
    ConfigureSPI();

    // Create ILI9341 display struct
    ILI9341_t myDisplay = {
        .cs_pin = HS_SSEL_PIN,
        .dc_pin = TFT_DC_PIN,
        .rst_pin = TFT_RST_PIN,
        .spi_base = SPI8,  // Flexcomm 8 SPI instance
    };

    // Initialize the display
    ILI9341_Init(&myDisplay);

    // Fill the screen with black
    ILI9341_SendCommand(&myDisplay, 0x2A);  // Column address set
    ILI9341_WriteData(&myDisplay, 0x00);
    ILI9341_WriteData(&myDisplay, 0x00);
    ILI9341_WriteData(&myDisplay, 0x00);
    ILI9341_WriteData(&myDisplay, 0xEF);  // 240 pixels width

    ILI9341_SendCommand(&myDisplay, 0x2B);  // Page address set
    ILI9341_WriteData(&myDisplay, 0x00);
    ILI9341_WriteData(&myDisplay, 0x00);
    ILI9341_WriteData(&myDisplay, 0x01);
    ILI9341_WriteData(&myDisplay, 0x3F);  // 320 pixels height

    ILI9341_SendCommand(&myDisplay, 0x2C);  // Memory write

    for (int i = 0; i < 320 * 240; i++) {
        ILI9341_WriteData(&myDisplay, 0x00);  // Black pixel
        ILI9341_WriteData(&myDisplay, 0x00);
    }

    while (1) {
        // Infinite loop
    }

    return 0;
}

void InitPins(void) {
    // Initialize GPIO for DC and RESET
    gpio_pin_config_t gpio_config = {
        kGPIO_DigitalOutput,
        1,  // Default high
    };

    GPIO_PinInit(GPIO, 0, TFT_DC_PIN, &gpio_config);
    GPIO_PinInit(GPIO, 0, TFT_RST_PIN, &gpio_config);

    // Initialize GPIO for manual CS control
    GPIO_PinInit(GPIO, 1, HS_SSEL_PIN, &gpio_config);
}

void ConfigureSPIPins(void) {
    // Configure pin muxing for SPI pins
    CLOCK_EnableClock(kCLOCK_Iocon);

    // Configure PIO0_26 as SPI_MOSI
    IOCON_PinMuxSet(IOCON, 0, HS_MOSI_PIN, IOCON_PIO_FUNC1 | IOCON_PIO_MODE_INACT);

    // Configure PIO1_1 as GPIO for CS
    IOCON_PinMuxSet(IOCON, 1, HS_SSEL_PIN, IOCON_PIO_FUNC0 | IOCON_PIO_MODE_INACT);

    // Configure PIO1_2 as SPI_SCK
    IOCON_PinMuxSet(IOCON, 1, HS_SCK_PIN, IOCON_PIO_FUNC1 | IOCON_PIO_MODE_INACT);

    // Configure PIO1_3 as SPI_MISO
    IOCON_PinMuxSet(IOCON, 1, HS_MISO_PIN, IOCON_PIO_FUNC1 | IOCON_PIO_MODE_INACT);
}

void ConfigureSPI(void) {
    spi_master_config_t spiConfig;

    // Get default SPI master configuration
    SPI_MasterGetDefaultConfig(&spiConfig);

    // Update configuration
    spiConfig.baudRate_Bps = 10000000U;  // 10 MHz
    spiConfig.sselNum = kSPI_Ssel0;     // SSEL0 is not used in this case
    spiConfig.sselPol = kSPI_SpolActiveAllLow;

    // Initialize Flexcomm 8 SPI
//    SPI_MasterInit(SPI8, &spiConfig, CLOCK_GetFlexcommClkFreq(SPI_INSTANCE));

    // Create a handle for SPI transfers
    SPI_MasterTransferCreateHandle(SPI8, &spiHandle, SPI_Callback, NULL);
}
