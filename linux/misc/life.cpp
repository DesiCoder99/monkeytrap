#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <csignal>
#include <curses.h>
#include <unistd.h>

int w = 32, h = 24;
char *b[2];
bool running = true;

void signal_handler(int signal) {
    running = false;
}

void lifeNext(char *bnext, const char *bcurr, int w, int h ) {
    memset( bnext, 0, w * h );

    int n, m;
    for (n = 1; n < h - 1; n++) {
        for (m = 1; m < w - 1; m++) {
            const int off = w * n + m;

            const int k = bcurr[ off - w + 1 ] + bcurr[ off - w + 0 ] + bcurr[ off - w - 1 ] +
                          bcurr[ off  + 1 ] + bcurr[ off  - 1 ] +
                          bcurr[ off + w + 1 ] + bcurr[ off + w + 0 ] + bcurr[ off + w - 1 ];

            const int e = bcurr[ off ];
            if ( ( e) && (k == 3 || k == 2) ) bnext[ off ] = 1;
            if ( (!e) && (k == 3        ) ) bnext[ off ] = 1;
        }
    }
}

void dispLife(char * buf, int w, int h) {
    int n, m, i;
    char c;
    // printf("\n");
    for (n = 0; n < h; n++) {
        for (m = 0; m < w; m++) {
            const int off = w * n + m;
            // printf("%c", buf[off] > 0 ? '#':'.');
            c = buf[off] > 0 ? '#' : '.';
            mvaddch(n, m, c);
        }
        // printf("\n");
    }
    refresh();
}

void printLife(char * buf, int w, int h) {
    int n, m, i;
    printf("\n");
    for (n = 0; n < h; n++) {
        for (m = 0; m < w; m++) {
            const int off = w * n + m;
            printf("%c", buf[off] > 0 ? '#' : '.');
        }
        printf("\n");
    }
}

int main(int ac, char*av[]) {
    std::signal(SIGINT, signal_handler);

    int r0 = ac > 1 ? atoi(av[1]):314159;

    initscr();
    keypad(stdscr, TRUE);
    nonl();
    cbreak();
    echo();


    b[0] = new char[w * h];
    b[1] = new char[w * h];

    int n, m;
    for (n = 0; n < h; n++) {
        for (m = 0; m < w; m++) {
            const int off = w * n + m;
            b[0][off] = rand() > (RAND_MAX / 2) ? 1 : 0;
        }
    }

    int i = 0, c = 0;
    while (running) {
        // printf(".");
        lifeNext(b[1 - i], b[i], w, h);

        dispLife(b[1 - i], w, h);

        usleep(33000);
        i = 1 - i;
        c++;
    }

    endwin();

    // printLife(b[1-i], w, h);

    delete [] b[0];
    delete [] b[1];
    return 0;
}
