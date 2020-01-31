#ifndef GAMELIB_COMPONENT_HPP
#define GAMELIB_COMPONENT_HPP

#include <gamelib_graphics.hpp>
#include <gamelib_actor.hpp>
#include <gamelib_world.hpp>

namespace GameLib {
    class InputComponent {
    public:
        virtual ~InputComponent() {}
        virtual void update(Actor& actor) = 0;
        virtual void collide() = 0;
    };

    class PhysicsComponent {
    public:
        virtual ~PhysicsComponent() {}
        virtual void update(Actor& actor, World& world) = 0;
    };

    class GraphicsComponent {
    public:
        virtual ~GraphicsComponent() {}
        virtual void update(Actor& actor, Graphics& graphics) = 0;
    };

	class SimpleInputComponent : public InputComponent {
    public:
        virtual ~SimpleInputComponent() {}
        void update(Actor& actor) override;
        void collide() override;
    };

	class RandomInputComponent : public InputComponent {
    public:
        virtual ~RandomInputComponent() {}
        void update(Actor& actor) override;
        void collide() override;
    };

	class LinearInputComponent : public InputComponent {
    public:
        virtual ~LinearInputComponent() {}
        void update(Actor& actor) override;
        void collide() override;

    private:
        int moveDirection = 0;
    };

    class SimplePhysicsComponent : public PhysicsComponent {
    public:
        virtual ~SimplePhysicsComponent() {}

        void update(Actor& actor, World& world);
    };

	class BoxPhysicsComponent : public PhysicsComponent {
    public:
        virtual ~BoxPhysicsComponent() {}

        void update(Actor& actor, World& world);
    };

    class SimpleGraphicsComponent : public GraphicsComponent {
    public:
        virtual ~SimpleGraphicsComponent() {}
        virtual void update(Actor& actor, Graphics& graphics);
    };
}

#endif // GAMELIB_COMPONENT_HPP
