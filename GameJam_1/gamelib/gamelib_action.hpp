#ifndef GAMELIB_ACTION_HPP
#define GAMELIB_ACTION_HPP

#include <gamelib_base.hpp>
#include <gamelib_actor.hpp>

namespace GameLib {
    class Action {
    public:
        virtual ~Action() {}

        void setActor(Actor* actor) { actor_ = actor; }
        Actor* getActor() {
            if (!actor_)
                return &nullActor;
            return actor_;
        }
        const Actor* getActor() const {
            if (!actor_)
                return &nullActor;
            return actor_;
        }

		void update(float timeStep);

		float axis1X{ 0.0f };
        float axis1Y{ 0.0f };
    protected:
        virtual void act() = 0;

        // define member variables here
        void move(glm::vec3 position);
        glm::vec3 position() const;

		// time step
		float dt;
    private:
        Actor* actor_{ nullptr };
        static Actor nullActor;
    };

    class MoveAction : public Action {
    public:
        virtual ~MoveAction() {}

    protected:
        void act() override;
    };
}

#endif
