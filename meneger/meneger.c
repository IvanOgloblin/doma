#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
void sig_winch(int signo)
{
struct winsize size;
ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
resizeterm(size.ws_row, size.ws_col);
}



char* concat(char *s1, char *s2) 
{
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    if (!result)
    {
	fprintf(stderr, "malloc() failed: insufficient memory!\n");
	return NULL;
	memcpy(result, s1, len1);
	memcpy(result + len1, s2, len2 + 1);
	return result;
    }
}



int main(int argc, char ** argv)
{
WINDOW * wndr;
WINDOW * wndl;
DIR * dirr;
DIR * dirl;
struct dirent *dpr;
struct dirent *dpl;
WINDOW * subwnd;
initscr();
keypad(stdscr,true);
signal(SIGWINCH, sig_winch);
cbreak();
curs_set(0);
refresh();
struct winsize size;
ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
wndl = newwin(size.ws_row, size.ws_col/2, 0, 0);
wndr = newwin(size.ws_row, size.ws_col/2, 0, size.ws_col/2);

subwnd = derwin(wndr, 4, 16, 1, 1);
wmove(wndr,1,1);
wmove(wndl,1,1);
int countr=1;
int countl=1;
char *pathl=calloc(strlen(get_current_dir_name())+1,1);
pathl=get_current_dir_name();
char *pathr=calloc(strlen(get_current_dir_name())+1,1);
pathr=get_current_dir_name();


char namel[30]=".";
char namer[30]=".";
short rl=0;
int row=1;
if ((dirl = opendir(namel)) == NULL) 
{
    perror("couldn't open '.'");
    return 1;
}
do{
if ((dpl = readdir(dirl)) != NULL)
{
    wmove(wndl,countl,1);
    if(rl==0&&row==countl)
    {
	wprintw(wndl, "%s<-\n",dpl->d_name);
	strcpy(namel,dpl->d_name);
    }
    else
    wprintw(wndl, "%s\n",dpl->d_name);
    countl++;
}


}while(dpl!=NULL);

if ((dirr = opendir(namer)) == NULL) 
{
    perror("couldn't open '.'");
    return 1;
}
do{
if ((dpr = readdir(dirr)) != NULL)
{
    wmove(wndr,countr,1);
    if(rl==1&&row==countr)
    {
	wprintw(wndr, "%s<-\n",dpr->d_name);
	strcpy(namer,dpr->d_name);
    }
    else
    wprintw(wndr, "%s\n",dpr->d_name);
    countr++;
}
}while(dpr!=NULL);



box(wndr, '|', '-');
box(wndl, '|', '-');
wrefresh(wndr);
wrefresh(wndl);
bool ex =true;
while(ex)
{
    rewinddir(dirr);
    rewinddir(dirl);
    int ch = getch();
    switch(ch)
    {
	case 259:
	    if(row>1)
	    row--;
	    break;
	case 258:
	    row++;
	    break;
	case 9:
	    if(rl==0)
	    {rl=1;free(pathl);pathl=calloc(strlen(get_current_dir_name()) + 1, 1);strcat(pathl,get_current_dir_name());chdir(pathr);}
	    else
	    {rl=0;free(pathr);pathr=calloc(strlen(get_current_dir_name()) + 1, 1);strcat(pathr,get_current_dir_name());chdir(pathl);}
	    row=1;
	    break;
	case 27:{
	    delwin(wndl);
	    delwin(wndr);
	    move(9, 0);
	    refresh();
	    endwin();
	    free(pathr);
	    free(pathl);
	    exit(EXIT_SUCCESS);
	    exit(0);}
	case 10:
	if(rl==0)
	{
	    char* buff = calloc(strlen(pathl) + strlen("/") + 1, 1);
	    strcat(buff, pathl);
	    strcat(buff, "/");
	    char *path = calloc(strlen(buff) + strlen(namel) + 1, 1);
	    strcat(path, buff);
	    strcat(path, namel);
	    free(buff);
	                
	if(!chdir(path))
	{if ((dirl = opendir(path)) == NULL) 
	    {
		perror("couldn't open");		
		return 1;
	    }char *temp=pathl;pathl=path;free(temp);}}
	    
	    
	if(rl==1)
	{
	    char* buff = calloc(strlen(pathr) + strlen("/") + 1, 1);
	    strcat(buff,pathr);
	    strcat(buff, "/");
	    char* path = calloc(strlen(buff) + strlen(namer) + 1, 1);
	    strcat(path, buff);
	    strcat(path, namer);
	    free(buff);
	if(!chdir(path))
	{if ((dirr = opendir(path)) == NULL&&chdir(namer)) 
	{
	    perror("couldn't open");
	    return 1;
	}char *temp=pathr;pathr=path;free(temp);}}
	clear();
	refresh();
	break;
	    
    }
    countl=1;
    countr=1;
    /*if ((dirl = opendir(namel)) == NULL) 
{
    perror("couldn't open '.'");
    return 1;
}*/
do{
    if ((dpl = readdir(dirl)) != NULL)
    {
	wmove(wndl,countl,1);
	if(rl==0&&row==countl)
	{
	    wprintw(wndl, "%s<-\n",dpl->d_name);
	    strcpy(namel,dpl->d_name);
	}
	else
	wprintw(wndl, "%s\n",dpl->d_name);
	countl++;
    }
}while(dpl!=NULL);

/*if ((dirr = opendir(namer)) == NULL) 
{
    perror("couldn't open '.'");
    return 1;
}*/
do{
if ((dpr = readdir(dirr)) != NULL)
{
    wmove(wndr,countr,1);
    if(rl==1&&row==countr)
    {
	wprintw(wndr, "%s<-\n",dpr->d_name);
	strcpy(namer,dpr->d_name);
    }
    else
    wprintw(wndr, "%s\n",dpr->d_name);
    countr++;
}
}while(dpr!=NULL);
box(wndr, '|', '-');
box(wndl, '|', '-');
wrefresh(wndr);
wrefresh(wndl);
}




delwin(subwnd);
delwin(wndr);
move(9, 0);
printw("Press any key to continue...");
refresh();
getch();
endwin();
exit(EXIT_SUCCESS);
}