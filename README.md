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

```bash
git submodule https://github.com/mattboan/pcd8544.git
```

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

5. Setup the pins in the pcd8544.h header file <b>Warning:</b> If you encounter errors this is likely the best place to start.
6. Initialize the PCD8544 display using the provided functions:

```c
init_pcd8544();

```

5. Use the available functions to control the display, such as:

```c
clear_frame_buffer();
draw_line(0, 0, 20, 20, true);
set_pixel(30, 30, true);
draw_frame_buffer();
```

6. Build and flash your ESP-IDF project to see the output on the PCD8544 display.

Please refer to the header file `pcd8544.h` for detailed documentation on each function and its usage, aswell as changing some config options; pin outs, defualt buffer init, frame buffer size, and queue size.

## License

This component is licensed under the [Apache License](LICENSE).
