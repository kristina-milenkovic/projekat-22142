//
// Created by krisitna on 20.10.25..
//

#ifndef MATF_RG_PROJECT_GUICONTROLLER_HPP
#define MATF_RG_PROJECT_GUICONTROLLER_HPP
#include <engine/core/Controller.hpp>
#include <spdlog/fmt/bundled/core.h>

namespace app {
class GUIController : public engine::core::Controller {
public:
    std::string_view name() const override { return "app::GUIController"; }

private:
    void initialize() override;

    void poll_events() override;

    void draw() override;
};
}// app

#endif //MATF_RG_PROJECT_GUICONTROLLER_HPP