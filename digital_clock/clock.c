#include <stdio.h>
#include <windows.h>

int main()
{
    int h,m,s;
    int d=1000;

    printf("Set time: \n");
    scanf("%d%d%d",&h,&m,&s);
    if(h>24 || m>60 || s>60)
    {
        printf("Invalid time\n");
        Sleep(3*1000);
        exit(1);
    }

    while (1)
    {
        s++;
        if(s>59);
        {
            m++;
            s=0;
        }
        if(m>59)
        {
            h++;
            m=0;
        }
        if(h>24)
        {
            h=1;
        }
        printf("\n Clock :");
        printf("\n %02d:%02d:%02d",h,s,m);
        Sleep(d);
        system("cls");
    }
    return 0;
}