#include "mlx.h"

// Define window dimensions
#define WIDTH 800
#define HEIGHT 600

// Define the struct to hold MiniLibX pointers
typedef struct s_draw {
    void *mlx_ptr;
    void *win_ptr;
} t_draw;

// Function to draw a pixel at (x, y) with color
void draw_pixel(t_draw *data, int x, int y, int color) {
    mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, color);
}

int main() {
    // Initialize MiniLibX and create window
    t_draw data;
    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Draw Pixel Example");

    // Draw a single pixel at coordinates (100, 100) with color 0x00ff00 (green)
    draw_pixel(&data, 100, 100, 0x00ff00);

    // Loop to keep the window open
    mlx_loop(data.mlx_ptr);

    return 0;
}

