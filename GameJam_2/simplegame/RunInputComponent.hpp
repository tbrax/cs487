#ifndef RUN_INPUT_COMPONENT_HPP
#define RUN_INPUT_COMPONENT_HPP

#include <gamelib_actor.hpp>

namespace GameLib {


	class RunInputComponent : public InputComponent {
	public:
		virtual ~RunInputComponent() {}
		void update(Actor& actor) override;
	};
}

#endif
