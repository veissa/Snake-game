#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

void start_game();

int main() {
    initscr();
    noecho();
    cbreak();

    int choice;
    while (1) {
        clear();
        mvprintw(0, 0, "Choose an option:\n");
        mvprintw(1, 0, "1 - Start\n");
        mvprintw(2, 0, "2 - About\n");
        mvprintw(3, 0, "3 - Hall of Fame\n");
        mvprintw(4, 0, "4 - Rules\n");
        mvprintw(5, 0, "5 - Exit\n");
        mvprintw(6, 0, "Please enter your choice: ");
        refresh();
        scanw("%d", &choice);

        if (choice == 1) {
            start_game();
        } else if (choice == 5) {
            break;
        } else {
            mvprintw(8, 0, "Option not implemented yet.");
            refresh();
            sleep(2);
        }
    }

    endwin();
    return 0;
}

void start_game() {
    WINDOW* win = newwin(20, 40, 1, 1);
    keypad(win, true);
    nodelay(win, true);
    int posX = 0, posY = 0;
    int foodX = rand() % 20, foodY = rand() % 20;
    int dirX = 1, dirY = 0;
    int score = 0;

    while (true) {
        int pressed = wgetch(win);
        if (pressed == KEY_LEFT) {
            dirX = -1;
            dirY = 0;
        }
        if (pressed == KEY_RIGHT) {
            dirX = 1;
            dirY = 0;
        }
        if (pressed == KEY_UP) {
            dirX = 0;
            dirY = -1;
        }
        if (pressed == KEY_DOWN) {
            dirX = 0;
            dirY = 1;
        }

        posX += dirX;
        posY += dirY;

        if (posX < 0) posX = 19;
        if (posX > 19) posX = 0;
        if (posY < 0) posY = 19;
        if (posY > 19) posY = 0;

        werase(win);
        usleep(100000);
        mvwaddch(win, posY, posX, '🐍');
        mvwaddch(win, foodY, foodX, 'X');
        mvwprintw(win, 0, 0, "Score: %d", score);

        if (foodX == posX && foodY == posY) {
            score++;
            foodX = rand() % 20;
            foodY = rand() % 20;
        }

        wrefresh(win);
    }
}
