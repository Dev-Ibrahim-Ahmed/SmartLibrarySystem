#ifndef SMARTLIBRARYSYSTEM_MENUS_H
#define SMARTLIBRARYSYSTEM_MENUS_H

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <iomanip>

using std::cout;
using std::string;
using std::flush;

const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string CYAN = "\033[36m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string boxLine = "=========================================";

inline void clearConsole() { cout << "\033[H\033[2J" << flush; }

inline void printCentered(const string& text, int width = 80) {
    int len = static_cast<int>(text.length());
    if (len >= width) {
        cout << text << "\n";
        return;
    }
    int leftPadding = (width - len) / 2;
    cout << string(leftPadding, ' ') << text << "\n";
}

void showLoadingMenu(const string& taskName, int durationMs = 1200);

#endif // SMARTLIBRARYSYSTEM_MENUS_H