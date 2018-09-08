#include <assert.h>
#include <unistd.h>
#include "progress.h"

int main(void) {
    unsigned int progressAll = 0;
    unsigned int percent = 0;
    int activeInt = 0;
    char activeChar;

    init_io();


    while(percent < 100){
        switch (activeInt){
            case 0: activeChar = '/';
                    break;
            case 1: activeChar = '-';
                    break;
            case 2: activeChar = '\\';
                    break;
            default: assert(0);
        }

        progressAll = get_progress();
        percent = 0;

        for (int i = 0; i < 4; i++){
            percent += progressAll & 0xFF;
            progressAll = progressAll >> 8;
        }

        percent = percent * 100 / 255; //scale from 255 to 100 to get percent.
        percent = percent / 4; //average over the 4 processes.          Both lines round down. Should be fine.

        progressbar('=', activeChar, ' ', percent);

        activeInt = (activeInt + 1) % 3;

#ifdef DEBUG
        wait_key();
#endif
        usleep(50000);
    }

    shutdown_io();

    return 0;
}