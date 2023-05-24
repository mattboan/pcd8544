# PCD8544 Component for ESP-IDF

This is an ESP-IDF component for controlling a PCD8544-based LCD display. The PCD8544 is commonly used with Nokia 5110 LCD displays and provides a simple interface for displaying text and graphics.

Currently a work in progress, but we can draw lines, set pixels, and started the implementation for rectangles, and circles.

After that I will start working on drawing bitmaps and characters.

[See more.](https://www.voidstudios.com.au/projects/3)

Check out the splash screen:

![Example Image](https://www.voidstudios.com.au/_next/image?url=https%3A%2F%2Fxovjhtjkytzursvsbvbp.supabase.co%2Fstorage%2Fv1%2Fobject%2Fpublic%2Fheader_img%2Fproject-b89c1cc6-cffa-44ba-a650-d4ba90e11770.undefined&w=1080&q=75)

## Getting Started

To use this component in your ESP-IDF project, follow these steps:

1. Clone or download this repository into the `components` directory of your ESP-IDF project.

2. In your project's main folder `CMakeLists.txt` file, add the following line to include the component:

    ```cmake
    idf_component_register(SRCS "<your-main and other files>.c"
                       INCLUDE_DIRS "."
                       REQUIRES pcd8544)
    ```

3. In your application code, include the PCD8544 header file:

    ```c
    #include "pcd8544.h"
    ```

4. Initialize the PCD8544 display using the provided functions:

    ```c
    spi_device_handle_t handle = init_lcd();

    // Setup the pins for output mode
    gpio_set_direction(RESET, GPIO_MODE_OUTPUT);
    gpio_set_direction(DC, GPIO_MODE_OUTPUT);

    // Reset the dispaly
    gpio_set_level(RESET, 1);
    gpio_set_level(RESET, 0);
    gpio_set_level(RESET, 1);

    // Set the contrast
    send_command(handle, PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION);
    send_command(handle, PCD8544_SETVOP | 30); // Contrast
    send_command(handle, PCD8544_FUNCTIONSET);

    // Set the Voltage Bias
    send_command(handle, PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION);
    send_command(handle, PCD8544_SETBIAS | 0x07); // Bias
    send_command(handle, PCD8544_FUNCTIONSET);

    // Sets the LCD to normal mode
    send_command(handle, PCD8544_FUNCTIONSET);

    // Set the display to Normal mode
    send_command(handle, PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL);

    // Draws the first frame
    draw_frame_buffer(handle);

    ```

5. Use the available functions to control the display, such as:

    ```c
    clear_frame_buffer(handle);

    draw_line(handle, 0, 0, 20, 20);

    set_pixel(handle, 30, 30);
    ```

6. Build and flash your ESP-IDF project to see the output on the PCD8544 display.

Please refer to the header file `pcd8544.h` for detailed documentation on each function and its usage, aswell as changing some config options; pin outs, defualt buffer init, frame buffer size, and queue size.

## License

This component is licensed under the [Apache License](LICENSE).
