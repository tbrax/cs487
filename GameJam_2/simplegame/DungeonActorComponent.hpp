#ifndef DUNGEON_ACTOR_COMPONENT_HPP
#define DUNGEON_ACTOR_COMPONENT_HPP

#include <gamelib_actor_component.hpp>

namespace GameLib {
	class DungeonActorComponent : public ActorComponent {
	public:
		virtual ~DungeonActorComponent() {}

		void update(Actor& actor, World& world) override;
		void beginPlay(Actor& actor) override;
		void handleCollisionStatic(Actor& a, Actor& b) override;
		void handleCollisionDynamic(Actor& a, Actor& b) override;
		void handleCollisionWorld(Actor& actor, World& world) override;
		void beginOverlap(Actor& a, Actor& b) override;
		void endOverlap(Actor& a, Actor& b) override;
		void beginTriggerOverlap(Actor& a, Actor& b) override;
		void endTriggerOverlap(Actor& a, Actor& b) override;
		void setPlayerType(int a) override;
		int getPlayerType() override;
		void setPlayerHealth(int a) override;
		int getPlayerHealth() override;
		void setPlayerScore(int a) override;
		int getPlayerScore() override;

	private:
		int playerType{ 0 };
		int playerScore{ 0 };
		int playerHealth{ 5 };
		struct STATICINFO {
			bool horizontal{false};
			float movement{2.0f};
			glm::vec3 position;
			float t{0.0f};
		} staticInfo;

		struct TRIGGERINFO {
			glm::vec3 position;
			float t{0.0f};
		} triggerInfo;
	};
} // namespace GameLib
#endif
