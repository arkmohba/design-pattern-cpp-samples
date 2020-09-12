#include "classes.hpp"

#include <iostream>
#include <string>

using namespace std;

Banner::Banner(std::string message) : my_message(message) {}

void Banner::showWithParen() { cout << "(" << my_message << ")" << endl; }

void Banner::showWithAster() { cout << "*" << my_message << "*" << endl; }

PrintBanner::PrintBanner(string my_message) : Banner(my_message) {}

void PrintBanner::printWeak() { showWithParen(); }

void PrintBanner::printStrong() { showWithAster(); }

PrintBannerTransfer::PrintBannerTransfer(string my_message)
    : banner(my_message) {}

void PrintBannerTransfer::printWeak() { banner.showWithParen(); }

void PrintBannerTransfer::printStrong() { banner.showWithAster(); }
