#include <chrono>
#include <thread>

#include "process.h"
#include "priority.h"
#include "screen.h"

int main()
{
    PSAscreen scr;
    process pr1;
    int ch;
    while (1)
    {
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	scr.draw_frame();
	scr.draw_frame_alg();
	scr.draw_frame_prc();
	scr.draw_frame_done();
	scr.draw_frame_legend();
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
	refresh();
    }
    endwin();
    return 0;
}
