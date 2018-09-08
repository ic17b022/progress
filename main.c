#include <assert.h>
#include <unistd.h>
#include "progress.h"

static unsigned int getPercentFromProgress (unsigned int progressAll);

int main(void) {
    int progress = 0;
    int activeInt = 0;
    char activeChar;

    init_io();


    while(progress < 100){
        switch (activeInt){
            case 0: activeChar = '/';
                    break;
            case 1: activeChar = '-';
                    break;
            case 2: activeChar = '\\';
                    break;
            default: assert(0);
        }

        progress = getPercentFromProgress (get_progress());
        progressbar('=', activeChar, ' ', progress);

        activeInt = ++activeInt % 3;

#ifdef DEBUG
        wait_key();
#endif
        usleep(50000);
    }

    shutdown_io();

    return 0;
}

static unsigned int getPercentFromProgress (unsigned int progressAll){
    int progress = 0;

    for (int i = 0; i < 4; i++){
        progress += progressAll & 0xFF;
        progressAll = progressAll >> 8;
    }

    return progress/4;  //rounding down is fine.
}