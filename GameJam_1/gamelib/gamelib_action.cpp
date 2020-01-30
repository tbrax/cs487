#include "pch.h"
#include <gamelib_action.hpp>

namespace GameLib {
    Actor Action::nullActor(nullptr, nullptr, nullptr);

    void Action::update(float timeStep) {
        dt = timeStep;
        act();
    }

    void Action::move(glm::vec3 position) {
        glm::mat4 transform = getActor()->addlTransform;
        transform = glm::translate(transform, { dt * position.x, dt * position.y, dt * position.z });
        getActor()->addlTransform = transform;
    }

    glm::vec3 Action::position() const { return getActor()->worldPosition(); }

    void MoveAction::act() { move({ axis1X, axis1Y, 0.0f }); }
}
