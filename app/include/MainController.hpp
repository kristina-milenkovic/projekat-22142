//
// Created by kristina on 19.10.25..
//

#ifndef MATF_RG_PROJECT_MAINCONTROLLER_HPP
#define MATF_RG_PROJECT_MAINCONTROLLER_HPP
#include "engine/core/Controller.hpp"
#include <glm/glm.hpp>

namespace app {
class MainController : public engine::core::Controller {

    void initialize() override;

    bool loop() override;

    void update() override;

    void update_light();

    void update_mouse();

    void update_camera();

    void begin_draw() override;

    void draw() override;

    void draw_convertible();

    void draw_pyramid();

    void draw_mouse();

    void draw_cube();

    void draw_desert();

    void draw_skybox();

    void end_draw() override;

public:
    glm::vec3 SpotlightDir = glm::vec3(0.35f, -10.0f, 1.35f);

    bool mouseActive = false;
    bool mouseReturning = false;
    float mouseSpawnTime = -1.0f;
    float mouseLifetime = 3.0f;
    float currentTime = 0.0f;
    glm::vec3 mouseStartPos = glm::vec3(10.0f, -4.4f, 5.35f);
    glm::vec3 mouseEndPos = glm::vec3(10.0f, -4.4f, -5.0f);
    glm::vec3 mousePos = mouseStartPos;

    std::string_view name() const override { return "app::MainController"; };
};
}
#endif //MATF_RG_PROJECT_MAINCONTROLLER_HPP