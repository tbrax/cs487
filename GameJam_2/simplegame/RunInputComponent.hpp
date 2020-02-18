#ifndef RUN_INPUT_COMPONENT_HPP
#define RUN_INPUT_COMPONENT_HPP

#include <gamelib_actor.hpp>

namespace GameLib {


	class RunInputComponent : public InputComponent {
	public:
		virtual ~RunInputComponent() {}

		void update(Actor& actor) override;
		void setRun(Actor& actor);
		RunInputComponent():count(0),runActor(nullptr) { 

		}
								
		
	private:
		int count{ 0 };
		Actor* runActor;
	};
}

#endif
