#include "pcd8544.h"

const char *PCD_TAG = "PCD8544";

// Frame buffer
uint8_t buffer [LCD_WIDTH * LCD_HEIGHT / 8] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 0x80, 0x00, 0xfe, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xfe, 0xfe, 0x0f, 0x07, 0xfe, 0xfe, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 0x0e, 0x0e, 0xfe, 0xfe, 0xfc, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x7f, 0x7f, 0xf0, 0xe0, 0x7f, 0x7f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x7f, 0x70, 0x70, 0x7f, 0x7f, 0x3f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

spi_device_handle_t handle;
int x_cursor = 0;
int y_cursor = 0;

// Wait for x ms
void delay(int ms) {
	vTaskDelay(ms / portTICK_PERIOD_MS);
}

// Init the LCD
void init_pcd8544() {
    esp_log_level_set(PCD_TAG, ESP_LOG_INFO);

    // Init SPI
    handle = init_spi();

     // Setup the pins for output mode
    gpio_set_direction(RESET, GPIO_MODE_OUTPUT);
    gpio_set_direction(DC, GPIO_MODE_OUTPUT);

    // Reset the dispaly
    gpio_set_level(RESET, 1);
    gpio_set_level(RESET, 0);
    gpio_set_level(RESET, 1);

    // Set the contrast
    send_command(PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION);
    send_command(PCD8544_SETVOP | 30); // Contrast
    send_command(PCD8544_FUNCTIONSET);

    // Set the Voltage Bias
    send_command(PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION);
    send_command(PCD8544_SETBIAS | 0x07); // Bias
    send_command(PCD8544_FUNCTIONSET);

    // Sets the LCD to normal mode
    send_command( PCD8544_FUNCTIONSET);

    // Set the display to Normal mode
    send_command( PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL);

    // Draws the first frame
    draw_frame_buffer();
}

// Init the SPI interface
spi_device_handle_t init_spi() {
    // Create a new device handle
    spi_device_handle_t temp;

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
    ESP_ERROR_CHECK( spi_bus_add_device(SPI2_HOST, &devcfg, &temp) );

    return temp;
}


// Send a command
void send_command(uint8_t command) {
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
void send_data(uint8_t data) {
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
void clear_frame_buffer() {
    memset(buffer, 0, LCD_WIDTH * LCD_HEIGHT / 8);
}

// Draw a pixel
void set_pixel(uint8_t x, uint8_t y, bool color) {
    // Check if out of bounds
    if (x >= LCD_WIDTH || y >= LCD_HEIGHT) return;

    if (color)
        buffer[x + (y / 8) * LCD_WIDTH] |= 1 << (y % 8);
    else
        buffer[x + (y / 8) * LCD_WIDTH] &= ~(1 << (y % 8));
}


void draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color) {
    int8_t dx =  abs(x1 - x0);
    int8_t dy = -abs(y1 - y0);
    int8_t sx = x0 < x1 ? 1 : -1;
    int8_t sy = y0 < y1 ? 1 : -1; 
    int8_t err = dx + dy; 
    int16_t err2;   // Have to use int16_t because:  err2_max = 2 * (dx_max + dy_max) = 2 * (84 + 48) = 2 * 132 = 264     


    while (1) {
        set_pixel(x0,y0, color);
        
        if (x0 == x1 && y0 == y1) break;
        
        err2 = 2 * err;
        
        if (err2 >= dy) { 
            err += dy; 
            x0 += sx; 

            if (x0 > LCD_WIDTH) break;
        } 
        
        if (err2 <= dx) { 
            err += dx;
            y0 += sy; 

            if (y0 > LCD_HEIGHT) break; 
        }
    }

}

// Draw a circle
void draw_circle(int xc, int yc, int r, bool color) {
    int x = -r;
    int y = 0; 
    int err = 2 - 2 * r; /* II. Quadrant */ 
    
    do {
        // Draw the 4 quadrants
        set_pixel(xc-x, yc+y, color); /*   I. Quadrant */
        set_pixel(xc-y, yc-x, color); /*  II. Quadrant */
        set_pixel(xc+x, yc-y, color); /* III. Quadrant */
        set_pixel(xc+y, yc+x, color); /*  IV. Quadrant */
        
        r = err;
        
        if (r >  x){
            ++x; 
            err = err + x * 2 + 1;   
        }

        if (r <= y) {
            ++y;
            err = err + y * 2 + 1;
        }
    } while (x < 0);
}

// Draw a rectangle
void draw_rect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color) {
    draw_line( x0, y0, x1, y0, color);
    draw_line( x1, y0, x1, y1, color);
    draw_line( x1, y1, x0, y1, color);
    draw_line( x0, y1, x0, y0, color);
}

// Drwa the frame buffer
void draw_frame_buffer() {
    send_command(PCD8544_SETYADDR | 0);

    // So there are 6 rows and 84 columns
    for (int page = 0; page < (6 * 84); page++) {
        send_data(buffer[page]);
    }
}

// Draw a bitmap
void draw_bitmap(int x, int y, int w, int h, uint8_t bitmap[], bool color) {
    int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t b = 0;

    for (int16_t j = 0; j < h; j++, y++) {
        
        for (int16_t i = 0; i < w; i++) {

            if (i & 7)
                b <<= 1;
            else
                b = bitmap[j * byteWidth + i / 8];

            if (b & 0x80) {
                set_pixel(x + i, y, color);
            } 
        }
    }
}


// Draw a character to the screen
void draw_char(int x, int y, char c, bool color) {
    // Check if out of bounds
    if (x >= LCD_WIDTH || y >= LCD_HEIGHT) return;

    // Check if character is out of bounds
    if ((x + 5) >= LCD_WIDTH || (y + 7) >= LCD_HEIGHT) return;

    // Check if character is printable
    if (c < 32 || c > 127) return;

    for (int i = 0; i < 5; i++) {
        int line = font[c - 32][i];

        for (int j = 0; j < 7; j++) {
            set_pixel(x + i, y + j, line & (1 << j));
        }
    }
}


void write_string(char * text, bool color, int d) {    
    for (int i = 0; i < strlen(text); i++) {
        draw_char(x_cursor, y_cursor, text[i], color);

        if (d > 0) {
            draw_frame_buffer();
            delay(d);
        }

        x_cursor += 6;

        if (x_cursor > LCD_WIDTH - 6) {
            x_cursor = 0;
            y_cursor += 10;
        }

        if (y_cursor > LCD_HEIGHT) {
            scroll_y(1);
            y_cursor -= 10;
            x_cursor = 0;
            draw_frame_buffer();
        }

        ESP_LOGI(PCD_TAG, "x_cursor: %d - y_cursor: %d.", x_cursor, y_cursor);
    }
}


void scroll_y(uint8_t pages) {
    // Loop over the pages from start to end -> end defined as height (6 pages) - pages NOTE: A page is 8 bits
    for (int i = 0; i < (LCD_WIDTH * (LCD_HEIGHT / 8 - pages)); i++) {
        buffer[i] = buffer[i + LCD_WIDTH];
    }

    // For the remainding old pages, we can set that too 0 or off -> This wont work with colouring.
    for (int i = (LCD_WIDTH * (LCD_HEIGHT / 8 - pages)); i < LCD_WIDTH * LCD_HEIGHT / 8; i++) {
        buffer[i] = 0x00;
    }
}