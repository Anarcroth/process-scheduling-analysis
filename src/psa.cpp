#include <ncurses.h>

int main()
{
    initscr();
    noecho();
    cbreak();
    int h, w;
    getmaxyx(stdscr, h, w);
    endwin();
    return 0;
}
