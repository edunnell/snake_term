#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

#define ROWS 25
#define COLS 80
#define MID_X COLS/2
#define MID_Y ROWS/2

typedef struct coordinate {
  int x;
  int y;
} coordinate;

void moveBody(coordinate * head, coordinate * body, int body_length) {
  int i;
  for(i = body_length-1; i > 0; --i) {
    body[i].x = body[i-1].x;
    body[i].y = body[i-1].y;
  }
  body[0].x = head->x;
  body[0].y = head->y;
}

void moveUp(coordinate * head, coordinate * body, int body_length) {
  moveBody(head, body, body_length);
  if (head->y > 0)
    --head->y;
  else
    head->y = 25;
}

void moveDown(coordinate * head, coordinate * body, int body_length) {
  moveBody(head, body, body_length);
  if (head->y < ROWS)
    ++head->y;
  else
    head->y = 0;
}

void moveLeft(coordinate * head, coordinate * body, int body_length) {
  moveBody(head, body, body_length);
  if (head->x > 0)
    --head->x;
  else
    head->x = 80;
}

void moveRight(coordinate * head, coordinate * body, int body_length) {
    moveBody(head, body, body_length);
  if (head->x < COLS)
    ++head->x;
  else
    head->x = 0;
}

int main(void) {
  int ch;
  coordinate head = {MID_X, MID_Y};
  coordinate body[10];
  int body_length = 4;
  
  void (*previous_fun_ptr)(struct coordinate *, struct coordinate *, int) = moveLeft;

  int i;
  for(i = 0; i < body_length; ++i) {
    body[i].x = MID_X+i+1;
    body[i].y = MID_Y;
  }
  
  initscr();
  halfdelay(1);
  noecho();
  curs_set(FALSE);
  keypad(stdscr, TRUE);
  refresh();
  
  while (1) {
    previous_fun_ptr(&head, body, body_length);
    ch = getch();
    switch (ch) {
      
    case KEY_UP:
      if (previous_fun_ptr == moveUp) {
        break;
      }
      moveUp(&head, body, body_length);
      previous_fun_ptr = moveUp;
      break;
      
    case KEY_DOWN:
      if (previous_fun_ptr == moveDown) {
        break;
      }
      moveDown(&head, body, body_length);
      previous_fun_ptr = moveDown;
      break;
      
    case KEY_LEFT:
      if (previous_fun_ptr == moveLeft) {
        break;
      }
      moveLeft(&head, body, body_length);
      previous_fun_ptr = moveLeft;
      break;
      
    case KEY_RIGHT:
      if (previous_fun_ptr == moveRight) {
        break;
      }
      moveRight(&head, body, body_length);
      previous_fun_ptr = moveRight;
      break;

    case -1:
      break;

    case 'Q':
    case 'q':
      endwin();
      exit(EXIT_SUCCESS);
    }

    clear();
    mvprintw(head.y, head.x, "s");
    mvprintw(body[0].y, body[0].x, "n");

    int i;
    for(i = 1; i < body_length-2; ++i)
      mvprintw(body[i].y, body[i].x, "a");

    mvprintw(body[body_length-2].y, body[body_length-2].x, "k");
    mvprintw(body[body_length-1].y, body[body_length-1].x, "e");

    refresh();
  }
}
