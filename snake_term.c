#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>

#define ROWS 25
#define COLS 80
#define MID_X COLS/2
#define MID_Y ROWS/2

typedef struct head {
  int x;
  int y;
} head;

typedef struct body {
  int x;
  int y;
} body;

void moveUp(head * head, body * body) {
  body[3].x = body[2].x;
  body[3].y = body[2].y;
  body[2].x = body[1].x;
  body[2].y = body[1].y;
  body[1].x = body[0].x;
  body[1].y = body[0].y;
  body[0].x = head->x;
  body[0].y = head->y;
  if (head->y > 0)
    --head->y;
  else
    head->y = 25;
}

void moveDown(head * head, body * body) {
  body[3].x = body[2].x;
  body[3].y = body[2].y;
  body[2].x = body[1].x;
  body[2].y = body[1].y;
  body[1].x = body[0].x;
  body[1].y = body[0].y;
  body[0].x = head->x;
  body[0].y = head->y;
  if (head->y < ROWS)
    ++head->y;
  else
    head->y = 0;
}

void moveLeft(head * head, body * body) {
  body[3].x = body[2].x;
  body[3].y = body[2].y;
  body[2].x = body[1].x;
  body[2].y = body[1].y;
  body[1].x = body[0].x;
  body[1].y = body[0].y;
  body[0].x = head->x;
  body[0].y = head->y;
  if (head->x > 0)
    --head->x;
  else
    head->x = 80;
}

void moveRight(head * head, body * body) {
  body[3].x = body[2].x;
  body[3].y = body[2].y;
  body[2].x = body[1].x;
  body[2].y = body[1].y;
  body[1].x = body[0].x;
  body[1].y = body[0].y;
  body[0].x = head->x;
  body[0].y = head->y;
  if (head->x < COLS)
    ++head->x;
  else
    head->x = 0;
}

int main(void) {

  WINDOW * mainwin;
  int ch; 
  int time_before_getch, time_after_fetch, elapsed_time;
  
  head head = {MID_X, MID_Y};
  body body[10];
  
  void (*previous_fun_ptr)(struct head *, struct body *) = moveLeft;
  
  body[0].x = MID_X+1;
  body[1].x = MID_X+2;
  body[2].x = MID_X+3;
  body[3].x = MID_X+4;
  body[0].y = MID_Y;
  body[1].y = MID_Y;
  body[2].y = MID_Y;
  body[3].y = MID_Y;
  
  initscr();
  halfdelay(1);
  noecho();
  curs_set(FALSE);
  keypad(stdscr, TRUE);
  refresh();
  
  while (1) {
    previous_fun_ptr(&head, body);
    ch = getch();
    switch (ch) {
      
    case KEY_UP:
      if (previous_fun_ptr == moveUp) {
        break;
      }
      moveUp(&head, body);
      previous_fun_ptr = moveUp;
      break;
      
    case KEY_DOWN:
      if (previous_fun_ptr == moveDown) {
        break;
      }
      moveDown(&head, body);
      previous_fun_ptr = moveDown;
      break;
      
    case KEY_LEFT:
      if (previous_fun_ptr == moveLeft) {
        break;
      }
      moveLeft(&head, body);
      previous_fun_ptr = moveLeft;
      break;
      
    case KEY_RIGHT:
      if (previous_fun_ptr == moveRight) {
        break;
      }
      moveRight(&head, body);
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
    mvprintw(body[1].y, body[1].x, "a");
    mvprintw(body[2].y, body[2].x, "k");
    mvprintw(body[3].y, body[3].x, "e");
    refresh();
  }
}
