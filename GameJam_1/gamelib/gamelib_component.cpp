#include "pch.h"
#include <gamelib_random.hpp>
#include <gamelib_locator.hpp>
#include <gamelib_component.hpp>

namespace GameLib {
    void SimpleInputComponent::update(Actor& actor) {
        auto axis1 = Locator::getInput()->axis1X;
        if (axis1)
            actor.velocity.x = axis1->getAmount();
        auto axis2 = Locator::getInput()->axis1Y;
        if (axis2)
            actor.velocity.y = axis2->getAmount();
    }

    void RandomInputComponent::update(Actor& actor) {
        actor.velocity.x = random.normal();
        actor.velocity.y = random.normal();
        glm::normalize(actor.velocity);
    }

    void SimplePhysicsComponent::update(Actor& actor, World& world) {
        float ground = 400;
        actor.position += actor.dt * actor.speed * actor.velocity;
        if (actor.position.y > ground)
            actor.position.y = ground;
    }

    void SimpleGraphicsComponent::update(Actor& actor, Graphics& graphics) {
        glm::vec3 tileSize{ graphics.getTileSizeX(), graphics.getTileSizeY(), 0 };
        glm::vec3 pos = actor.position * tileSize;
        graphics.draw(actor.spriteLibId, actor.spriteId, pos.x, pos.y);
    }
}
