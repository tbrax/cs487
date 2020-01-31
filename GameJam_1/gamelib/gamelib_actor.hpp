#ifndef GAMELIB_ACTOR_HPP
#define GAMELIB_ACTOR_HPP

#include <gamelib_component.hpp>
#include <gamelib_object.hpp>
#include <gamelib_world.hpp>

namespace GameLib {
    class InputComponent;
    class PhysicsComponent;
    class GraphicsComponent;

    class Actor : public Object {
    public:
        Actor(InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics);
        virtual ~Actor();

        using weak_ptr = std::weak_ptr<Actor>;
        using shared_ptr = std::shared_ptr<Actor>;
        using const_weak_ptr = const std::weak_ptr<Actor>;
        using const_shared_ptr = const std::shared_ptr<Actor>;

        virtual char charDesc() const { return charDesc_; }

		virtual void actorCollide() {}

        // Called whenever the object is introduced into the game
        virtual void beginPlay();

        // Called each frame the object needs to update itself before drawing
        virtual void update(float deltaTime, World& world, Graphics& graphics);

        // Called when an object has just started to overlap the bounding box of this object
        virtual void startOverlap(const_weak_ptr otherObject);

        // Called when an object has just ended overlapping the bounding box of this object
        virtual void endOverlap(const_weak_ptr otherObject);

        // Gets the world matrix for this actor which is transform * addlTransform
        glm::mat4 worldMatrix() const { return transform * addlTransform; }

        // Gets column 4 of the world matrix which is the local origin in world space
        glm::vec3 worldPosition() const {
            glm::mat4 w = worldMatrix();
            return glm::vec3{ w[3][0], w[3][1], w[3][2] };
        }

        // Gets the minimum bounds for this actor in world space, bbox is not rotated
        glm::vec3 worldBBoxMin() const { return worldPosition() + bboxMin; }

        // Gets the maximum bounds for this actor in world space, bbox is not rotated
        glm::vec3 worldBBoxMax() const { return worldPosition() + bboxMax; }

        using uint = unsigned;
        using ushort = unsigned short;
        using ubyte = unsigned char;
        using ubool = unsigned short; // using short can avoid character integer issues

        // sprite number for this object
        uint spriteId{ 0 };
        // sprite library number for this object
        uint spriteLibId{ 0 };

        // is object visible for drawing
        ubool visible{ true };
        // is actor active for updating
        ubool active{ true };

        // transform that takes this object to world space
        glm::mat4 transform;
        // additional transform that moves this object in local space
        glm::mat4 addlTransform;
        // minimum coordinates for this bounding box in local space
        glm::vec3 bboxMin;
        // maximum coordinates for this bounding box in world space
        glm::vec3 bboxMax;

        // time elapsed for next update
        float dt;

        // current position
        glm::vec3 position;

        // current velocity
        glm::vec3 velocity;

		// maximum speed
        float speed{ 16.0f };
    protected:
        std::string _updateDesc() override { return { "Actor" }; }
        std::string _updateInfo() override { return { "Actor" }; }
        char charDesc_ = '?';

    private:
        InputComponent* input_{ nullptr };
        PhysicsComponent* physics_{ nullptr };
        GraphicsComponent* graphics_{ nullptr };
    };
}

#endif
