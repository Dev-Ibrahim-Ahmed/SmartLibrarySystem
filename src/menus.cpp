#include "menus.h"

void showLoadingMenu(const string& taskName, int durationMs) {
    cout << "\n\n";
    printCentered(CYAN + BOLD + boxLine + RESET);
    printCentered(BOLD + "SMART LIBRARY SYSTEM" + RESET);
    printCentered(CYAN + BOLD + boxLine + RESET);
    cout << "\n";

    const char spinner[] = {'|', '/', '-', '\\'};
    int frameCount = 15;
    int delayPerFrame = durationMs / frameCount;

    for (int i = 0; i < frameCount; ++i) {
        string statusText = YELLOW + string(1, spinner[i % 4]) + " " + taskName + "..." + RESET;
        printCentered(statusText);
        std::this_thread::sleep_for(std::chrono::milliseconds(delayPerFrame));
        cout << "\033[1A\033[2K" << flush;
    }

    printCentered(GREEN + BOLD + "[SUCCESS] " + taskName + " Complete!" + RESET);
    printCentered(CYAN + BOLD + boxLine + RESET);
    cout << "\n";
}