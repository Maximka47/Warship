#include <iostream>
#include <cstdlib>
#include <time.h>
#include <windows.h>

void clear(char fill = ' ') {
    COORD tl = { 0,0 };
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
};

int main()
{
    clear();
    int choice;
    std::cout << "~~WARSHIPS~~\n\n";
    std::cout << "1. Single Player\n";
    std::cout << "2. PvP\n";
    std::cout << "Choose a game mode:";
    std::cin >> choice;
    clear();
    std::cout << "~~WARSHIPS~~\n\n";
    
    srand(time(0));

    int field[4][4] = {
        { 0, 1, 0, 1 },
        { 0, 1, 0, 0 },
        { 0, 1, 0, 1 },
        { 1, 0, 1, 0 }
    };
    int pchitslanded[16][2];

    if (choice == 2) {
        int hits1p = 0;
        int hits2p = 0;
        int hitsum = 0;
        int turns1p = 0;
        int turns2p = 0;
        int turnsum = 0;

        while (hitsum < 7) {
            int x, y;

            //P1 Selecting coordinates
            std::cout << "<Player 1 Select coordinates>\n";

            //P1 x input
            std::cout << "Choose a row number between 1 and 4: ";
            std::cin >> x;
            --x;
            //P1 y input
            std::cout << "Choose a column number between 1 and 4: ";
            std::cin >> y;
            --y;
            //Checking for P1 hits
            if (field[x][y]) {
                field[x][y] = 0;

                ++hits1p;
                ++hitsum;

                std::cout << "Hit! " << 7 - (hitsum) << " hits left. \n\n";
            }
            else {
                std::cout << "Miss\n\n";
            }
            turns1p++;
            if (hitsum < 7) {
                //P2 Selecting coordinates
                std::cout << "<Player 2 Select coordinates>\n\n";

                //P2 x input
                std::cout << "Choose a row number between 1 and 4: ";
                std::cin >> x;
                --x;
                //P2 y input
                std::cout << "Choose a column number between 1 and 4: ";
                std::cin >> y;
                --y;
                //Checking for P1 hits
                if (field[x][y]) {
                    field[x][y] = 0;

                    ++hits2p;
                    ++hitsum;

                    std::cout << "Hit! " << 7 - (hitsum) << " hits left. \n\n";
                }
                else {
                    std::cout << "Miss\n\n";
                }
                turns2p++;
            }
        }
        std::cout << "Victory!\n";
        if (hits1p > hits2p) {
            std::cout << "Player 1 won in " << turns1p << " turns.\n";
        }
        else if (hits2p > hits1p) {
            std::cout << "Player 2 won in " << turns2p << " turns.\n\n";
        }

        std::cout << "Type q to quit, or type <r> to restart: ";
        char outcome;
        std::cin >> outcome;
        if (outcome == 'q') {
            exit(0);
        }
        else if (outcome == 'r') {
            main();
        }

    }
    else if (choice == 1) {
        int p1hits = 0;
        int p1turns = 0;
        int pchits = 0;
        int pcturns = 0;

        while (p1hits + pchits < 7) {
            int x, y;

            //Player Turn

            //Selecting coordinates
            std::cout << "<Player Selecting coordinates>\n\n";

            //x input
            std::cout << "Choose a row number between 1 and 4: ";
            std::cin >> x;
            --x;

            //y input
            std::cout << "Choose a column number between 1 and 4: ";
            std::cin >> y;
            --y;

            //Hit check
            if (field[x][y]) {
                field[x][y] = 0;

                ++p1hits;
                std::cout << "Hit! " << 7 - p1hits - pchits << " hits left. \n\n";
            }
            else {
                std::cout << "Miss\n\n";
            }
            p1turns++;

            int x1, y1, sleeptime;
            if (7 - p1hits - pchits > 0) {
                //PC Turn
                x1 = rand() % 4 + 1;
                y1 = rand() % 4 + 1;

                //Selecting coordinates
                std::cout << "<PC Selecting coordinates>\n\n";

                //x input
                std::cout << "PC chooses a row number between 1 and 4: ";
                x1 = rand() % 4 + 1;
                sleeptime = rand() % 1000;
                Sleep(sleeptime);
                std::cout << x1 << "\n";
                --x1;

                //y input
                std::cout << "PC chooses a column number between 1 and 4: ";
                y1 = rand() % 4 + 1;
                sleeptime = rand() % 1000;
                Sleep(sleeptime);
                std::cout << y1 << "\n";
                --y1;

                //Hit check
                if (field[x1][y1]) {
                    field[x1][y1] = 0;

                    ++pchits;

                    std::cout << "Hit! " << 7 - pchits - p1hits << " hits left. \n\n";
                }
                else {
                    std::cout << "Miss\n\n";
                }
                pcturns++;
            }
        }
        if (p1hits > pchits) {
            std::cout << "Victory!\n";
            std::cout << "You won in " << p1turns << " turns.\n\n";
        }
        else {
            std::cout << "Victory!\n";
            std::cout << "PC won in " << pcturns << " turns.\n\n";
        }
    }

    std::cout << "Type <q> to quit, or type <r> to restart: ";
    char outcome;
    std::cin >> outcome;
    if (outcome == 'q') {
        exit(0);
    }
    else if (outcome == 'r') {
        main();
    }
    return 0;
}