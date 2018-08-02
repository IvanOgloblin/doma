#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>

void sig_winch(int signo)
{
struct winsize size;
ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
resizeterm(size.ws_row, size.ws_col);
}

int main(int argc, char ** argv)
{
WINDOW * wnd;
WINDOW * subwnd;

initscr();
keypad(stdscr, true);
signal(SIGWINCH, sig_winch);
cbreak();
noecho();
curs_set(1);
struct winsize size;
ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
wnd = newwin(size.ws_row, size.ws_col,0,0);
attron(A_BOLD);
int wi=0;
int he=0;

bool ex = true;
while(ex)
{
    int c=getch();
    switch(c)
    {
    case 330:
	return 0;
    case 260:
	wi--;
	wmove(wnd,he,wi);
	break;
    case 259:
	he--;
	wmove(wnd,he,wi);
	break;
    case 261:
	wi++;
	wmove(wnd,he,wi);
	break;
    case 258:
	he++;
	wmove(wnd,he,wi);
	break;
    case 269:
	{FILE *fp;
	char name[]="ncurses.s";
	    if((fp = fopen(name, "w"))!=NULL) 
	    {
		putwin(wnd,fp);
		//scr_dump("ncurses.s");
	    }
	    else printf("Не удалось открыть файл");
	    
	    fclose(fp);
	    ex=false;
	break;}
    case 270:
	{FILE *fp;
	char name[]="ncurses.s";
	    if((fp = fopen(name, "r"))!=NULL) 
	    {
		wnd=getwin(fp);
		//scr_init("ncurses.s"); 
		wrefresh(wnd);
	    }
	    else{printf("Не удалось открыть файл");
	    
	    fclose(fp);
	    ex=false;}
	break;}
    case 271:
	{return 0;}
    default:
	if(c>=32&&c<=126)
	{
	    wprintw(wnd,"%c",c);
	    wi++;
	    wrefresh(wnd);
	}
	break;
    }
}
delwin(wnd);
endwin();
exit(EXIT_SUCCESS);
}
