//
// Created by Ibrahim on 8/31/2026.
//

#ifndef SMARTLIBRARYSYSTEM_MENUS_H
#define SMARTLIBRARYSYSTEM_MENUS_H

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <iomanip>

using std::cout;
using std::string;
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string CYAN = "\033[36m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string boxLine = "=========================================";

void clearConsole() {cout << "\033[H\033[2J" << std::flush;}

void deleteChars(int n) {
    cout << "\b \b";
}
void printCentered(const string& text, int width = 80) {
    int len = static_cast<int>(text.length());
    if (len >= width) {
        cout << text << "\n";
        return;
    }
    int leftPadding = (width - len) / 2;
    cout << string(leftPadding, ' ') << text << "\n";
}

void showLoadingMenu(const string& taskName, int durationMs = 1200) {

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



#endif //SMARTLIBRARYSYSTEM_MENUS_H