#include <ncurses.h>
#include <chrono>
#include <thread>

#include "process.h"
#include "priority.h"

void draw_frame();

int main()
{
    initscr();
    noecho();
    cbreak();
    process pr1;
    int ch;
    nodelay(stdscr, TRUE);
    while (1)
    {
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	draw_frame();
	if ((ch = getch()) == ERR)
	{
	}
	else
	{
	    move(10, 10);
	    addstr(pr1.get_id().c_str());
	    move(11, 10);
	    addstr(prtostr(pr1.get_pr()).c_str());
	    move(12, 10);
	    addstr(std::to_string(pr1.get_ttl()).c_str());
	}
    }
    refresh();
    endwin();
    return 0;
}

/*
  Draws the screen frame from the following characters:
  ─ (ACS_HLINE), ┌ (ACS_ULCORNER), └ (ACS_LLCORNER),
  ┐ (ACS_URCORNER), ┘ (ACS_LRCORNER), │ (ACS_VLINE)
*/
void draw_frame()
{
    move(0, 0);
    echochar(ACS_ULCORNER);

    for (int i = 1; i < COLS - 1; i++)
    {
	move(0, i);
	echochar(ACS_HLINE);
	move(LINES - 1, i);
	echochar(ACS_HLINE);
    }

    move(LINES - 1, 0);
    echochar(ACS_LLCORNER);
    move(0, COLS - 1);
    echochar(ACS_URCORNER);

    for (int i = 1; i < LINES - 1; i++)
    {
	move(i, 0);
	echochar(ACS_VLINE);
	move(i, COLS - 1);
	echochar(ACS_VLINE);
    }

    move(LINES - 1, COLS - 1);
    echochar(ACS_LRCORNER);
}
