#include "start_screen.hh"


void Button::paint(pro2::Window& window, pro2::TextWriter& writer) const {
    if (this->selected(window.mouse_pos())) {
        pro2::paint_rect_fill(window, rect, bg_selected);
        writer.write_text(window, {(rect.left + rect.right)/2, (rect.top + rect.bottom)/2}, text, 2, 2, {1,1});
    }
    else {
        pro2::paint_rect_fill(window, rect, bg_normal);
        writer.write_text(window, {(rect.left + rect.right)/2, (rect.top + rect.bottom)/2}, text, 2, 2, {1,1});
    }
};

StartScreen::StartScreen(int width, int height, pro2::TextWriter TW) : TW_(TW), width_(width), height_(height) {
    buttons = {
        Button({width/2-40, height/2-20, width/2+40, height/2+20}, "START"),
        Button({width/2-40, height/2+30, width/2+40, height/2+70}, "EXIT"),
};
}

void StartScreen::process_keys(pro2::Window& window) {
    if (window.was_key_pressed(pro2::Keys::Escape)) {
        finished_ = true;
        exit_code_= -1;
        return;
    }
    if (window.was_mouse_pressed()) {
        if (buttons[0].selected(window.mouse_pos())) {
            finished_ = true;
            exit_code_= 1;
        }
        else if (buttons[1].selected(window.mouse_pos())) {
            finished_ = true;
            exit_code_= -1;
        }
    }
}

void StartScreen::update(pro2::Window& window) {
    process_keys(window);
}

void StartScreen::paint(pro2::Window& window) {
    window.clear(sky_blue);
    TW_.write_text(window, {window.width()/2, window.height()/2-80}, "SUPER MARIO PRO2", 4, 4, {1,1});
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i].paint(window, TW_);
    }
}

void StartScreen::restart(pro2::Window& window) {
    exit_code_ = 0;
    finished_ = false;
    window.set_camera_topleft({0,0});
}