#include "pcd8544.h"

// Frame buffer
uint8_t buffer [LCD_WIDTH * LCD_HEIGHT / 8] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 0x80, 0x00, 0xfe, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xfe, 0xfe, 0x0f, 0x07, 0xfe, 0xfe, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 0x0e, 0x0e, 0xfe, 0xfe, 0xfc, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x7f, 0x7f, 0xf0, 0xe0, 0x7f, 0x7f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x7f, 0x70, 0x70, 0x7f, 0x7f, 0x3f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

// Wait for x ms
void delay(int ms) {
	vTaskDelay(ms / portTICK_PERIOD_MS);
}

// Init the SPI interface
spi_device_handle_t init_lcd() {
    // Create a new device handle
    spi_device_handle_t handle;

    // Bus configuration
    spi_bus_config_t buscfg = {
        .mosi_io_num = MOSI,
        .miso_io_num = -1,
        .sclk_io_num = SCLK,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1
    };

    // SPI interface config
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 4000000, // 4Mhz
        .mode = 0,
        .spics_io_num = -1, // Not using CS
        .queue_size = QUEUE_SIZE
    };

    // Setup and return the spi interface
    ESP_ERROR_CHECK( spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO) );
    ESP_ERROR_CHECK( spi_bus_add_device(SPI2_HOST, &devcfg, &handle) );

    return handle;
}


// Send a command
void send_command(spi_device_handle_t handle, uint8_t command) {
    // Set DC Low
    gpio_set_level(DC, 0);

    // Create a transaction
    spi_transaction_t trans;
    memset( &trans, 0, sizeof( spi_transaction_t ) );
    trans.length = 8;
    trans.tx_buffer = &command;
    ESP_ERROR_CHECK( spi_device_transmit(handle, &trans)  );

}

// Send some data
void send_data(spi_device_handle_t handle, uint8_t data) {
     // Set DC Low
    gpio_set_level(DC, 1);

    // Create a transaction
    spi_transaction_t trans;
    memset( &trans, 0, sizeof( spi_transaction_t ) );
    trans.length = 8;
    trans.tx_buffer = &data;
    ESP_ERROR_CHECK( spi_device_transmit(handle, &trans)  );
}

// Clear the buffer
void clear_frame_buffer(spi_device_handle_t handle) {
    memset(buffer, 0, LCD_WIDTH * LCD_HEIGHT / 8);
}

// Draw a pixel
void set_pixel(spi_device_handle_t handle, uint8_t x, uint8_t y, bool color) {
    if (color)
        buffer[x + (y / 8) * LCD_WIDTH] |= 1 << (y % 8);
    else
        buffer[x + (y / 8) * LCD_WIDTH] &= ~(1 << (y % 8));
}

// Draw a line
void draw_line(spi_device_handle_t handle, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color) {
    int8_t dx = x1 - x0;
    int8_t dy = y1 - y0;
    int8_t sx = dx > 0 ? 1 : -1;
    int8_t sy = dy > 0 ? 1 : -1;
    dx = abs(dx);
    dy = abs(dy);
    int8_t err = dx - dy;

    while (x0 != x1 || y0 != y1) {
        set_pixel(handle, x0, y0, color);
        int8_t err2 = 2 * err;

        if (err2 > -dy) {
            err -= dy;
            x0 += sx;
        }

        if (err2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

// Draw a circle
void draw_circle(spi_device_handle_t handle, uint8_t x0, uint8_t y0, uint8_t r, bool color) {

    // Needs work...

    uint8_t f = 1 - r;
    uint8_t ddF_x = 1;
    uint8_t ddF_y = -2 * r;
    uint8_t x = 0;
    uint8_t y = r;

    set_pixel(handle, x0, y0 + r, color);
    set_pixel(handle, x0, y0 - r, color);
    set_pixel(handle, x0 + r, y0, color);
    set_pixel(handle, x0 - r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        set_pixel(handle, x0 + x, y0 + y, color);
        set_pixel(handle, x0 - x, y0 + y, color);
        set_pixel(handle, x0 + x, y0 - y, color);
        set_pixel(handle, x0 - x, y0 - y, color);
        set_pixel(handle, x0 + y, y0 + x, color);
        set_pixel(handle, x0 - y, y0 + x, color);
        set_pixel(handle, x0 + y, y0 - x, color);
        set_pixel(handle, x0 - y, y0 - x, color);
    }
}

// Draw a rectangle
void draw_rect(spi_device_handle_t handle, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color) {
    draw_line(handle, x0, y0, x1, y0, color);
    draw_line(handle, x1, y0, x1, y1, color);
    draw_line(handle, x1, y1, x0, y1, color);
    draw_line(handle, x0, y0, x0, y1, color);
}

// Drwa the frame buffer
void draw_frame_buffer(spi_device_handle_t handle) {

    send_command(handle, PCD8544_SETYADDR | 0);

    // So there are 6 rows and 84 columns
    for (int page = 0; page < (6 * 84); page++) {
        send_data(handle, buffer[page]);
    }
}