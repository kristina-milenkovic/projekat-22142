#include "../../engine/test/app/include/app/GUIController.hpp"

#include <GuiController.hpp>
#include <MainController.hpp>
#include <engine/graphics/GraphicsController.hpp>
#include <engine/graphics/OpenGL.hpp>
#include <engine/platform/PlatformController.hpp>
#include <engine/resources/ResourcesController.hpp>
#include <spdlog/spdlog.h>

namespace app {

class MainPlatformEventObserver : public engine::platform::PlatformEventObserver {
public:
    void on_mouse_move(engine::platform::MousePosition position) override;
};

void MainPlatformEventObserver::on_mouse_move(engine::platform::MousePosition position) {
    auto gui_controller = engine::core::Controller::get<GUIController>();
    if (!gui_controller->is_enabled()) {
        auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();
        camera->rotate_camera(position.dx, position.dy);
    }
}

void MainController::initialize() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    platform->register_platform_event_observer(std::make_unique<MainPlatformEventObserver>());
    engine::graphics::OpenGL::enable_depth_testing();
}

bool MainController::loop() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    if (platform->key(engine::platform::KeyId::KEY_ESCAPE).is_down()) { return false; }
    return true;
}

void MainController::draw_mouse() {
    if (!mouseActive) return;
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    engine::resources::Model *mouse = resources->model("Mouse");
    //Shader
    engine::resources::Shader *shader = resources->shader("basic");

    shader->use();
    shader->set_mat4("projection", graphics->projection_matrix());
    shader->set_mat4("view", graphics->camera()->view_matrix());
    shader->set_mat4("model", glm::mat4(1.0f));
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, mousePos);
    if (!mouseReturning) { model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0)); }
    model = glm::scale(model, glm::vec3(0.05f));
    shader->set_mat4("model", model);
    mouse->draw(shader);
}

void MainController::draw_convertible() {
    //Model
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    engine::resources::Model *convertible = resources->model("Convertible");
    //Shader
    engine::resources::Shader *shader = resources->shader("basic");

    shader->use();
    shader->set_mat4("projection", graphics->projection_matrix());
    shader->set_mat4("view", graphics->camera()->view_matrix());
    shader->set_mat4("model", glm::mat4(1.0f));
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(12.0f, -4.4f, 1.0f));
    model = glm::scale(model, glm::vec3(0.15f));
    shader->set_mat4("model", model);
    convertible->draw(shader);
}

void MainController::draw_pyramid() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    engine::resources::Model *pyramid = resources->model("Pyramid");
    //Shader
    engine::resources::Shader *shader = resources->shader("basic");

    shader->use();
    shader->set_mat4("projection", graphics->projection_matrix());
    shader->set_mat4("view", graphics->camera()->view_matrix());
    shader->set_mat4("model", glm::mat4(1.0f));
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(10.0f, -3.2f, -2.5f));
    model = glm::scale(model, glm::vec3(4.0f));
    shader->set_mat4("model", model);
    pyramid->draw(shader);
}

void MainController::draw_cube() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    engine::resources::Model *cube = resources->model("Ball");
    //Shader
    engine::resources::Shader *shader = resources->shader("basic");

    shader->use();
    shader->set_mat4("projection", graphics->projection_matrix());
    shader->set_mat4("view", graphics->camera()->view_matrix());
    shader->set_mat4("model", glm::mat4(1.0f));
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(10.0f, -2.9f, -1.35f));
    model = glm::scale(model, glm::vec3(0.001f));
    shader->set_mat4("model", model);

    cube->draw(shader);
}

void MainController::draw_desert() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    engine::resources::Model *desert = resources->model("Desert");
    //Shader
    engine::resources::Shader *shader = resources->shader("basic");

    shader->use();
    shader->set_mat4("projection", graphics->projection_matrix());
    shader->set_mat4("view", graphics->camera()->view_matrix());
    shader->set_mat4("model", glm::mat4(1.0f));
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(10.0f, -6.0f, -9.0f));
    model = glm::scale(model, glm::vec3(0.03f));
    shader->set_mat4("model", model);

    desert->draw(shader);
}

void MainController::draw_skybox() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto skybox = resources->skybox("penguins");
    auto shader = resources->shader("skybox");
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    graphics->draw_skybox(shader, skybox);
}

void MainController::update_camera() {
    auto gui_controller = engine::core::Controller::get<GUIController>();
    if (gui_controller->is_enabled()) { return; }
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    auto camera = graphics->camera();
    float dt = platform->dt();

    if (platform->key(engine::platform::KeyId::KEY_W).is_down()) { camera->move_camera(engine::graphics::Camera::Movement::FORWARD, dt); }

    if (platform->key(engine::platform::KeyId::KEY_S).is_down()) { camera->move_camera(engine::graphics::Camera::Movement::BACKWARD, dt); }

    if (platform->key(engine::platform::KeyId::KEY_A).is_down()) { camera->move_camera(engine::graphics::Camera::Movement::LEFT, dt); }

    if (platform->key(engine::platform::KeyId::KEY_D).is_down()) { camera->move_camera(engine::graphics::Camera::Movement::RIGHT, dt); }
}

void MainController::update_light() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    if (platform->key(engine::platform::KeyId::KEY_1).is_down()) { if (SpotlightDir.y > 1.5f) { SpotlightDir.y = 1.5f; } else { SpotlightDir.y += 0.05f; } }
    if (platform->key(engine::platform::KeyId::KEY_2).is_down()) { if (SpotlightDir.y < -10.0f) { SpotlightDir.y = -10.0f; } else { SpotlightDir.y -= 0.05f; } }
}

void MainController::update_mouse() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();

    if ((platform->key(engine::platform::KeyId::KEY_M).state() == engine::platform::Key::State::JustPressed) && !mouseActive) {
        mouseActive = true;
        mouseReturning = false;
        mousePos = mouseStartPos;
    }

    if (mouseActive) {
        float speedZ = 0.003f;

        if (!mouseReturning) {
            mousePos.z -= speedZ * platform->frame_time().current;

            if (mousePos.z <= mouseEndPos.z) { mouseReturning = true; }
        } else {
            mousePos.z += speedZ * platform->frame_time().current;

            if (mousePos.z >= mouseStartPos.z) { mouseActive = false; }
        }
    }
}

void MainController::update() {
    update_mouse();
    update_light();
    update_camera();
}

void MainController::begin_draw() { engine::graphics::OpenGL::clear_buffers(); }

void MainController::draw() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    auto shader = resources->shader("basic");
    shader->use();

    //Directional
    shader->set_vec3("dirLightDirection", glm::vec3(-0.8f, -1.0f, -0.4f));
    shader->set_vec3("dirLightColor", glm::vec3(0.3f, 0.3f, 0.3f));

    //Spotlight
    shader->set_vec3("spotLightPos", glm::vec3(10.0f, -2.9f, -1.35f));
    shader->set_vec3("spotLightDir", glm::normalize(SpotlightDir));
    shader->set_vec3("spotLightColor", glm::vec3(0.7f, 0.7f, 0.3f));
    shader->set_float("spotCutOff", glm::cos(glm::radians(40.5f)));
    shader->set_float("spotOuterCutOff", glm::cos(glm::radians(50.5f)));

    //Camera
    shader->set_vec3("viewPos", graphics->camera()->Position);
    shader->set_float("shininess", 32.0f);
    shader->set_vec3("ambientStrength", glm::vec3(0.1f));
    shader->set_vec3("specularColor", glm::vec3(0.5f));

    //Draw
    draw_mouse();
    draw_convertible();
    draw_pyramid();
    draw_cube();
    draw_desert();
    draw_skybox();
}

void MainController::end_draw() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    platform->swap_buffers();
}
}