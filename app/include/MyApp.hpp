#ifndef MY_APP_H
#define MY_APP_H

#include <engine/core/App.hpp>

namespace app {
class MyApp : public engine::core::App {
    void app_setup() override;
};

}
#endif