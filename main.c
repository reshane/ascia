#include <stdio.h>
#include <float.h>
#include <sys/time.h>
#include <math.h>
#include <unistd.h>

#define WIDTH 32
#define HEIGHT 32

#define D_SCL (((WIDTH*WIDTH)/4) + ((HEIGHT*HEIGHT)/4))
#define C_SCL 8

typedef struct {
  int x;
  int y;
} Point;

static Point center = {WIDTH/2, HEIGHT/2};

static char display[WIDTH * HEIGHT];

static char table[C_SCL+1] = "_.xX0Xx._";

void fill(float seed)
{
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      float dx = center.x - x;
      float dy = center.y - y;
      int c_ind = (sin(seed)) * (((dx*dx + dy*dy) / D_SCL) * (C_SCL/2)) + (C_SCL/2);
      display[y * WIDTH + x] = table[c_ind];
    }
  }
}

void show()
{
  for (int y = 0; y < HEIGHT; ++y) {
    fwrite(&display[y * WIDTH], WIDTH, 1, stdout);
    printf("\n");
  }
}

void back()
{
  printf("\x1b[%dD", WIDTH);
  printf("\x1b[%dA", HEIGHT);
}

#define FPS 128

int main(void)
{
  float seed = 0.0f;
  while (1) {
    fill(seed);
    show();
    back();

    seed += 0.1;
    if (seed > M_PI*2) seed = 0;

    int dt = (20 * 1000 * 1000 / FPS);
    usleep(dt);
  }
  return 0;
}
