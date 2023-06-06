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

#define CHAR_OFFSET 32

static uint8_t font[96][5] = {
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },// (space)
	{ 0x00, 0x00, 0x5F, 0x00, 0x00 },// !
	{ 0x00, 0x07, 0x00, 0x07, 0x00 },// "
	{ 0x14, 0x7F, 0x14, 0x7F, 0x14 },// #
	{ 0x24, 0x2A, 0x7F, 0x2A, 0x12 },// $
	{ 0x23, 0x13, 0x08, 0x64, 0x62 },// %
	{ 0x36, 0x49, 0x55, 0x22, 0x50 },// &
	{ 0x00, 0x05, 0x03, 0x00, 0x00 },// '
	{ 0x00, 0x1C, 0x22, 0x41, 0x00 },// (
	{ 0x00, 0x41, 0x22, 0x1C, 0x00 },// )
	{ 0x08, 0x2A, 0x1C, 0x2A, 0x08 },// *
	{ 0x08, 0x08, 0x3E, 0x08, 0x08 },// +
	{ 0x00, 0x50, 0x30, 0x00, 0x00 },// ,
	{ 0x08, 0x08, 0x08, 0x08, 0x08 },// -
	{ 0x00, 0x60, 0x60, 0x00, 0x00 },// .
	{ 0x20, 0x10, 0x08, 0x04, 0x02 },// /
	{ 0x3E, 0x51, 0x49, 0x45, 0x3E },// 0
	{ 0x00, 0x42, 0x7F, 0x40, 0x00 },// 1
	{ 0x42, 0x61, 0x51, 0x49, 0x46 },// 2
	{ 0x21, 0x41, 0x45, 0x4B, 0x31 },// 3
	{ 0x18, 0x14, 0x12, 0x7F, 0x10 },// 4
	{ 0x27, 0x45, 0x45, 0x45, 0x39 },// 5
	{ 0x3C, 0x4A, 0x49, 0x49, 0x30 },// 6
	{ 0x01, 0x71, 0x09, 0x05, 0x03 },// 7
	{ 0x36, 0x49, 0x49, 0x49, 0x36 },// 8
	{ 0x06, 0x49, 0x49, 0x29, 0x1E },// 9
	{ 0x00, 0x36, 0x36, 0x00, 0x00 },// :
	{ 0x00, 0x56, 0x36, 0x00, 0x00 },// ;
	{ 0x00, 0x08, 0x14, 0x22, 0x41 },// <
	{ 0x14, 0x14, 0x14, 0x14, 0x14 },// =
	{ 0x41, 0x22, 0x14, 0x08, 0x00 },// >
	{ 0x02, 0x01, 0x51, 0x09, 0x06 },// ?
	{ 0x32, 0x49, 0x79, 0x41, 0x3E },// @
	{ 0x7E, 0x11, 0x11, 0x11, 0x7E },// A
	{ 0x7F, 0x49, 0x49, 0x49, 0x36 },// B
	{ 0x3E, 0x41, 0x41, 0x41, 0x22 },// C
	{ 0x7F, 0x41, 0x41, 0x22, 0x1C },// D
	{ 0x7F, 0x49, 0x49, 0x49, 0x41 },// E
	{ 0x7F, 0x09, 0x09, 0x01, 0x01 },// F
	{ 0x3E, 0x41, 0x41, 0x51, 0x32 },// G
	{ 0x7F, 0x08, 0x08, 0x08, 0x7F },// H
	{ 0x00, 0x41, 0x7F, 0x41, 0x00 },// I
	{ 0x20, 0x40, 0x41, 0x3F, 0x01 },// J
	{ 0x7F, 0x08, 0x14, 0x22, 0x41 },// K
	{ 0x7F, 0x40, 0x40, 0x40, 0x40 },// L
	{ 0x7F, 0x02, 0x04, 0x02, 0x7F },// M
	{ 0x7F, 0x04, 0x08, 0x10, 0x7F },// N
	{ 0x3E, 0x41, 0x41, 0x41, 0x3E },// O
	{ 0x7F, 0x09, 0x09, 0x09, 0x06 },// P
	{ 0x3E, 0x41, 0x51, 0x21, 0x5E },// Q
	{ 0x7F, 0x09, 0x19, 0x29, 0x46 },// R
	{ 0x46, 0x49, 0x49, 0x49, 0x31 },// S
	{ 0x01, 0x01, 0x7F, 0x01, 0x01 },// T
	{ 0x3F, 0x40, 0x40, 0x40, 0x3F },// U
	{ 0x1F, 0x20, 0x40, 0x20, 0x1F },// V
	{ 0x7F, 0x20, 0x18, 0x20, 0x7F },// W
	{ 0x63, 0x14, 0x08, 0x14, 0x63 },// X
	{ 0x03, 0x04, 0x78, 0x04, 0x03 },// Y
	{ 0x61, 0x51, 0x49, 0x45, 0x43 },// Z
	{ 0x00, 0x00, 0x7F, 0x41, 0x41 },// [
	{ 0x02, 0x04, 0x08, 0x10, 0x20 },// "\"
	{ 0x41, 0x41, 0x7F, 0x00, 0x00 },// ]
	{ 0x04, 0x02, 0x01, 0x02, 0x04 },// ^
	{ 0x40, 0x40, 0x40, 0x40, 0x40 },// _
	{ 0x00, 0x01, 0x02, 0x04, 0x00 },// `
	{ 0x20, 0x54, 0x54, 0x54, 0x78 },// a
	{ 0x7F, 0x48, 0x44, 0x44, 0x38 },// b
	{ 0x38, 0x44, 0x44, 0x44, 0x20 },// c
	{ 0x38, 0x44, 0x44, 0x48, 0x7F },// d
	{ 0x38, 0x54, 0x54, 0x54, 0x18 },// e
	{ 0x08, 0x7E, 0x09, 0x01, 0x02 },// f
	{ 0x08, 0x14, 0x54, 0x54, 0x3C },// g
	{ 0x7F, 0x08, 0x04, 0x04, 0x78 },// h
	{ 0x00, 0x44, 0x7D, 0x40, 0x00 },// i
	{ 0x20, 0x40, 0x44, 0x3D, 0x00 },// j
	{ 0x00, 0x7F, 0x10, 0x28, 0x44 },// k
	{ 0x00, 0x41, 0x7F, 0x40, 0x00 },// l
	{ 0x7C, 0x04, 0x18, 0x04, 0x78 },// m
	{ 0x7C, 0x08, 0x04, 0x04, 0x78 },// n
	{ 0x38, 0x44, 0x44, 0x44, 0x38 },// o
	{ 0x7C, 0x14, 0x14, 0x14, 0x08 },// p
	{ 0x08, 0x14, 0x14, 0x18, 0x7C },// q
	{ 0x7C, 0x08, 0x04, 0x04, 0x08 },// r
	{ 0x48, 0x54, 0x54, 0x54, 0x20 },// s
	{ 0x04, 0x3F, 0x44, 0x40, 0x20 },// t
	{ 0x3C, 0x40, 0x40, 0x20, 0x7C },// u
	{ 0x1C, 0x20, 0x40, 0x20, 0x1C },// v
	{ 0x3C, 0x40, 0x30, 0x40, 0x3C },// w
	{ 0x44, 0x28, 0x10, 0x28, 0x44 },// x
	{ 0x0C, 0x50, 0x50, 0x50, 0x3C },// y
	{ 0x44, 0x64, 0x54, 0x4C, 0x44 },// z
	{ 0x00, 0x08, 0x36, 0x41, 0x00 },// {
	{ 0x00, 0x00, 0x7F, 0x00, 0x00 },// |
	{ 0x00, 0x41, 0x36, 0x08, 0x00 },// }
	{ 0x08, 0x08, 0x2A, 0x1C, 0x08 },// ->
	{ 0x08, 0x1C, 0x2A, 0x08, 0x08 } // <-
};


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
 * @param color The color of the pixel (true = black, false = white)
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
 * @param color The color of the line (true = black, false = white)
 */
void draw_line(spi_device_handle_t handle, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color);

/**
 * @brief Draws a circle with the specified center, radius, and color.
 *
 * @param handle The SPI device handle for the LCD.
 * @param x0 The x-coordinate of the center of the circle.
 * @param y0 The y-coordinate of the center of the circle.
 * @param r The radius of the circle.
 * @param color The color of the circle (true = black, false = white)
 */
void draw_circle(spi_device_handle_t handle, int xc, int yc, int r, bool color);

/**
 * @brief Draws a rectangle with the specified coordinates and color.
 *
 * @param handle The SPI device handle for the LCD.
 * @param x0 The x-coordinate of the top-left corner of the rectangle.
 * @param y0 The y-coordinate of the top-left corner of the rectangle.
 * @param x1 The x-coordinate of the bottom-right corner of the rectangle.
 * @param y1 The y-coordinate of the bottom-right corner of the rectangle.
 * @param color The color of the rectangle (true = black, false = white)
 */
void draw_rect(spi_device_handle_t handle, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color);


/**
 * @brief Draws the frame buffer on the LCD.
 *
 * @param handle The SPI device handle for the LCD.
 */
void draw_frame_buffer(spi_device_handle_t handle);


/**
 * @brief Draw a bitmap to the screen
 * 
 */
void draw_bitmap(spi_device_handle_t handle, int x, int y, int w, int h, uint8_t bitmap[], bool color);

/**
 * @brief Draw a character to the screen
 * 
 * @param handle 
 * @param x 
 * @param y 
 * @param c 
 * @param color 
 */
void draw_char(spi_device_handle_t handle, int x, int y, char c, bool color);

/**
 * @brief Write a string to the screen
 * 
 * @param handle 
 * @param cursor 
 * @param string 
 * @param color 
 * @param d For delaying the output old school terminal output
 */
void write_string(spi_device_handle_t handle, int*cursor, char* string, bool color, bool d);