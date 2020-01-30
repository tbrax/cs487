#include "pch.h"
#include <gamelib_actor.hpp>
#include <gamelib_locator.hpp>

namespace GameLib {
    Actor::Actor(InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics)
        : transform(1.0f)
        , addlTransform(1.0f)
        , input_(input)
        , physics_(physics)
        , graphics_(graphics) {}

    Actor::~Actor() {
        delete input_;
        delete physics_;
        delete graphics_;
    }

    void Actor::beginPlay() {}

    void Actor::update(float deltaTime, World& world, Graphics& graphics) {
        dt = deltaTime;
        if (input_)
            input_->update(*this);
        if (physics_)
            physics_->update(*this, world);
        if (graphics_)
            graphics_->update(*this, graphics);
    }

    void Actor::startOverlap(const_weak_ptr otherObject) {}

    void Actor::endOverlap(const_weak_ptr otherObject) {}
}
