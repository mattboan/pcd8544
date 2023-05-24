#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_log.h"


// Function set, Power down mode
#define PCD8544_POWERDOWN 0x04 

// Function set, Entry mode
#define PCD8544_ENTRYMODE 0x02 

//Function set, Extended instruction set control
#define PCD8544_EXTENDEDINSTRUCTION 0x01 

// Display control, blank
#define PCD8544_DISPLAYBLANK 0x0    
// Display control, normal mode
#define PCD8544_DISPLAYNORMAL 0x4
// Display control, all segments on   
#define PCD8544_DISPLAYALLON 0x1    
// Display control, inverse mode
#define PCD8544_DISPLAYINVERTED 0x5 
// Basic instruction set
#define PCD8544_FUNCTIONSET 0x20
// Basic instruction set - Set display configuration 
#define PCD8544_DISPLAYCONTROL 0x08
// Basic instruction set - Set Y address of RAM, 0 <= Y <= 5 
#define PCD8544_SETYADDR 0x40 
// Basic instruction set - Set X address of RAM, 0 <= X <= 83
#define PCD8544_SETXADDR0x80 
// Extended instruction set - Set temperature coefficient
#define PCD8544_SETTEMP 0x04 
// Extended instruction set - Set bias system
#define PCD8544_SETBIAS 0x10 
// Extended instruction set - Write Vop to register
#define PCD8544_SETVOP 0x80  

// LCD Width and Height
#define LCD_WIDTH 84
#define LCD_HEIGHT 48

// Pin Selection
#define DC 4
#define RESET 2
#define MOSI 23
#define SCLK 18

// SPI Config
#define FRAME_BUFFER_SIZE 504
#define QUEUE_SIZE 32



/**
 * @brief Delays execution for the specified number of milliseconds.
 * 
 * TODO: Move this to another component: esp32-time
 *
 * @param ms The delay duration in milliseconds.
 */
void delay(int ms);


/**
 * @brief Initializes the SPI interface for the LCD.
 *
 * @return The SPI device handle for the LCD.
 */
spi_device_handle_t init_lcd();


/**
 * @brief Sends a command to the LCD.
 *
 * @param handle The SPI device handle for the LCD.
 * @param command The command to be sent.
 */
void send_command(spi_device_handle_t handle, uint8_t command);


/**
 * @brief Sends data to the LCD.
 *
 * @param handle The SPI device handle for the LCD.
 * @param data The data to be sent.
 */
void send_data(spi_device_handle_t handle, uint8_t data);


/**
 * @brief Clears the frame buffer.
 *
 * @param handle The SPI device handle for the LCD.
 */
void clear_frame_buffer(spi_device_handle_t handle);


/**
 * @brief Sets the color of a pixel at the specified coordinates.
 *
 * @param handle The SPI device handle for the LCD.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color of the pixel (true for white, false for black).
 */
void set_pixel(spi_device_handle_t handle, uint8_t x, uint8_t y, bool color);


/**
 * @brief Draws a line between two points. Using Bresenham's Line Algorithm
 *
 * @param handle The SPI device handle for the LCD.
 * @param x0 The x-coordinate of the starting point.
 * @param y0 The y-coordinate of the starting point.
 * @param x1 The x-coordinate of the ending point.
 * @param y1 The y-coordinate of the ending point.
 * @param color The color of the line (true for white, false for black).
 */
void draw_line(spi_device_handle_t handle, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color);


/**
 * @brief Draws a circle with the specified center, radius, and color.
 *
 * @param handle The SPI device handle for the LCD.
 * @param x0 The x-coordinate of the center of the circle.
 * @param y0 The y-coordinate of the center of the circle.
 * @param r The radius of the circle.
 * @param color The color of the circle (true for white, false for black).
 */
void draw_circle(spi_device_handle_t handle, uint8_t x0, uint8_t y0, uint8_t r, bool color);


/**
 * @brief Draws a rectangle with the specified coordinates and color.
 *
 * @param handle The SPI device handle for the LCD.
 * @param x0 The x-coordinate of the top-left corner of the rectangle.
 * @param y0 The y-coordinate of the top-left corner of the rectangle.
 * @param x1 The x-coordinate of the bottom-right corner of the rectangle.
 * @param y1 The y-coordinate of the bottom-right corner of the rectangle.
 * @param color The color of the rectangle (true for white, false for black).
 */
void draw_rect(spi_device_handle_t handle, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color);


/**
 * @brief Draws the frame buffer on the LCD.
 *
 * @param handle The SPI device handle for the LCD.
 */
void draw_frame_buffer(spi_device_handle_t handle);
