#include <cstdio>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>

#include <curses.h>

int main()
{
    initscr();
    cbreak();
    noecho();

    int c;

    while (1)
    {
 c = getch();

 if (c == 27)
     break;

 printw("%d ", c);
    }

    endwin();

    return 0;
}
