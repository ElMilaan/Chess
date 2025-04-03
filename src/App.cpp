#include "headers/App.hpp"

App::App(unsigned int board_size)
    : turn(Color::WHITE), board(Board(board_size)), info(Info()), end_game(false) {}

void App::init()
{
    board.init();
    ImGui::CreateContext();
    loadCustomFont();
};

void App::update()
{
    info.update(board, info.history);
    board.update(info.history);
    render_app();
};

void App::render_app() {
};

void App::render_info()
{
    info.render();
}

void App::loadCustomFont()
{
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontDefault();
    io.Fonts->AddFontFromFileTTF("assets/fonts/tt_usual.ttf", 64.0f);
}

void App::run()
{
    ImGui::Begin("Board");

    update();

    ImGui::End();

    ImGui::Begin("Infos");

    render_info();

    ImGui::End();
}