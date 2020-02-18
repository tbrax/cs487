#ifndef FLY_PHYSICS_COMPONENT_HPP
#define FLY_PHYSICS_COMPONENT_HPP

#include <gamelib_actor.hpp>

namespace GameLib {
	class FlyPhysicsComponent : public SimplePhysicsComponent {
	public:
		void update(Actor& a, World& world) override;
		float direction;
	};
} // namespace GameLib

#endif
