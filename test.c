#include "mlx.h"
#include <unistd.h>
#include <stdio.h>

typedef struct s_pixels{
  void *mlx_ptr;
  void *win_ptr;
  int key_druck;
}t_pixels;

int shift_color(int key, t_pixels *ptr)
{
  write(1, "c", 1);
  (*ptr).key_druck = 5;
  return (0);
}

int main()
{
  /*void *mlx_ptr;
  void *win_ptr;*/
  t_pixels ptr;
  ptr.key_druck = 0;
  ptr.mlx_ptr = mlx_init();
  ptr.win_ptr = mlx_new_window(ptr.mlx_ptr, 500, 500, "new window");
  mlx_pixel_put(ptr.mlx_ptr, ptr.win_ptr, 200, 100, 1266);
  mlx_key_hook(ptr.win_ptr, &shift_color, &ptr);
  if (ptr.key_druck == 5)
    write (1, "color has been changed\n", 23);
  else
    write (1, "hi\n", 3);
  printf("%d\n", ptr.key_druck);
  mlx_loop(ptr.mlx_ptr);
}
