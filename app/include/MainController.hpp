//
// Created by kristina on 19.10.25..
//

#ifndef MATF_RG_PROJECT_MAINCONTROLLER_HPP
#define MATF_RG_PROJECT_MAINCONTROLLER_HPP
#include "engine/core/Controller.hpp"

namespace app {
class MainController : public engine::core::Controller {
    void initialize() override;

public:
    std::string_view name() const override { return "app::MainControlle"; };
};
}
#endif //MATF_RG_PROJECT_MAINCONTROLLER_HPP