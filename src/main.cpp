#include <stdio.h>
#include <fstream>
#include <iostream>
#include <quick_imgui/quick_imgui.hpp>
#include "headers/App.hpp"

int main()
{
    App* app = new App(8);

    quick_imgui::loop("Chess", {
                                   .init = [&]() { app->init(); },
                                   .loop = [&]() { app->run(); },
                               });
    return 0;
}