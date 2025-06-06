#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define HEIGHT 20
#define WIDTH 60

enum Direction { UP, DOWN, LEFT, RIGHT, STOP };
enum Direction dir;

int score;
int tail_length;
int tail_x[100];
int tail_y[100];
int fruit_x, fruit_y;
int head_x, head_y;

void clear_screen();
void draw();
void input();
void setup();
void game_play();

struct termios old_props;
void set_terminal_attribute();
void reset_terminal_attribute();

int input_available();

int main() {

  srand(time(NULL));

  set_terminal_attribute();

  setup();

  while (1) {

    draw();

    input();

    game_play();

    long sleep_time = 3000000 / (score != 0 ? (score / 2) : 5);

    usleep(sleep_time);
  }
}

void clear_screen() {
#if defined(_WIN32) // #ifdef _Win32
  system("cls");
#else
  system("clear");
#endif
}

void set_terminal_attribute() {
  // change terminal Properties

  tcgetattr(STDIN_FILENO, &old_props);
  atexit(reset_terminal_attribute);
  struct termios new_props = old_props;
  new_props.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_props);
}

void reset_terminal_attribute() {
  tcsetattr(STDIN_FILENO, TCSANOW, &old_props);
}

void draw() {
  clear_screen();

  printf("\n\n\t\tWELCOME TO SNAKE-GAME !!\n\n");

  printf("\n");

  for (int i = 0; i < WIDTH + 2; i++) {
    printf("#");
  }

  for (int i = 0; i < HEIGHT; i++) {
    printf("\n#");
    for (int j = 0; j < WIDTH; j++) {
      if (i == head_y && j == head_x) {
        printf("O");
      } else if (i == fruit_y && j == fruit_x) {
        printf("F");
      } else {

        int tail_found = 0;

        for (int k = 0; k < tail_length; k++) {
          if (tail_x[k] == j && tail_y[k] == i) {
            printf("o");
            tail_found = 1;
            break;
          }
        }
        if (!tail_found) {
          printf(" ");
        }
      }
    }
    printf("#");
  }

  printf("\n");

  for (int i = 0; i < WIDTH + 2; i++) {
    printf("#");
  }

  printf("\n\n Score: %d\n", score);
}

void setup() {
  head_x = WIDTH / 2;
  head_y = HEIGHT / 2;

  fruit_x = rand() % WIDTH;
  fruit_y = rand() % HEIGHT;

  dir = STOP;

  score = 0;
  tail_length = 0;
}

// Is Input available from the keyboard ?
int input_available() {
  struct timeval tv = {0L, 0L};

  fd_set fds;

  FD_SET(0, &fds);

  return select(1, &fds, NULL, NULL, &tv);
}

void game_play() {

  int x = head_x, y = head_y;

  for (int i = tail_length - 1; i > 0; i--) {
    tail_x[i] = tail_x[i - 1];
    tail_y[i] = tail_y[i - 1];
  }

  tail_x[0] = head_x;
  tail_y[0] = head_y;

  switch (dir) {
  case UP:
    head_y--;
    break;
  case DOWN:
    head_y++;
    break;
  case LEFT:
    head_x--;
    break;
  case RIGHT:
    head_x++;
    break;
  case STOP:
    // do nothing
    break;
  }

  if (head_x < 0) {
    head_x = WIDTH - 1;
  } else if (head_x >= WIDTH) {
    head_x = 0;
  }
  if (head_y < 0) {
    head_y = HEIGHT - 1;
  } else if (head_y >= HEIGHT) {
    head_y = 0;
  }

  for (int i = 0; i < tail_length; i++) {
    if (tail_x[i] == head_x && tail_y[i] == head_y) {
      printf("\n GAME OVER !!\n");
      printf("\n You Hit Your Tail\n");
      exit(0);
    }
  }

  if (head_x == fruit_x && head_y == fruit_y) {
    score += 10;
    tail_length++;

    fruit_x = rand() % WIDTH;
    fruit_y = rand() % HEIGHT;
  }
}

void input() {
  if (input_available()) {
    char ch = getchar();

    switch (ch) {
    case 'a':
      dir = LEFT;
      break;
    case 's':
      dir = DOWN;
      break;
    case 'd':
      dir = RIGHT;
      break;
    case 'w':
      dir = UP;
      break;
    case 'x':
      exit(0);
      break;
    default:
      break;
    }
  }
}
