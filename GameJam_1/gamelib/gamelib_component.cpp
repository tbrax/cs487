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

    void SimpleInputComponent::collide() {}

    void RandomInputComponent::update(Actor& actor) {
        // actor.velocity.x = random.normal();
        // actor.velocity.y = random.normal();
        // glm::normalize(actor.velocity);
        actor.velocity.x = 0;
        actor.velocity.y = 0;
    }

    void RandomInputComponent::collide() {}

    void LinearInputComponent::collide() {
        int newDirection = rand() % 4;
        while (newDirection == moveDirection) {
            newDirection = rand() % 4;
        }
        moveDirection = newDirection;
    }
    void LinearInputComponent::update(Actor& actor) {
        if (moveDirection == 0) {
            actor.velocity.x = 1;
        } else if (moveDirection == 1) {
            actor.velocity.x = -1;
        } else if (moveDirection == 2) {
            actor.velocity.y = 1;
        } else if (moveDirection == 3) {
            actor.velocity.y = -1;
        }
        // actor.velocity.x = random.normal();
        // actor.velocity.y = random.normal();
        // glm::normalize(actor.velocity);
    }

    void SimplePhysicsComponent::update(Actor& actor, World& world) {
        float ground = 400;
        actor.position += actor.dt * actor.speed * actor.velocity;
        if (actor.position.y > ground)
            actor.position.y = ground;
    }

    void BoxPhysicsComponent::update(Actor& actor, World& world) {
        float ground = 400;
        actor.position += actor.dt * actor.speed * actor.velocity;
        int boxSize = 1;
        std::vector<bool> sidesTouching = { false, false, false, false };
        for (auto i : world.actors) {
            if (i != &actor) {
                bool touching = false;
                if (actor.position.x < i->position.x + boxSize) {
                    sidesTouching[0] = true;
                }
                if (actor.position.x > i->position.x - boxSize) {
                    sidesTouching[1] = true;
                }
                if (actor.position.y > i->position.y - boxSize) {
                    sidesTouching[2] = true;
                }
                if (actor.position.y < i->position.y + boxSize) {
                    sidesTouching[3] = true;
                }

                //std::cout << (sidesTouching[0]) << (sidesTouching[1]) << (sidesTouching[2]) << (sidesTouching[3]) << std::endl;
                if (sidesTouching[0] && sidesTouching[1] && sidesTouching[2] && sidesTouching[3]) {
                    touching = true;
                    
                    if (actor.position.x > i->position.x) {
                        actor.position.x = i->position.x + boxSize;
                    }
                    else if (actor.position.x < i->position.x) {
                        actor.position.x = i->position.x - boxSize;
                    }
                    if (actor.position.y > i->position.y) {
                        actor.position.y = i->position.y + boxSize;
                    }
                    else if (actor.position.y < i->position.y) {
                        actor.position.y = i->position.y - boxSize;
                    }
                    actor.actorCollide();
                }
            }
        }

        if (actor.position.y > ground)
            actor.position.y = ground;
    }

    void SimpleGraphicsComponent::update(Actor& actor, Graphics& graphics) {
        glm::vec3 tileSize{ graphics.getTileSizeX(), graphics.getTileSizeY(), 0 };
        glm::vec3 pos = actor.position * tileSize;
        graphics.draw(actor.spriteLibId, actor.spriteId, pos.x, pos.y);
    }
}
