#include "FlyPhysicsComponent.hpp"
#include<stdio.h>
#include <math.h>
namespace GameLib {
	bool touching(Actor& a, World& w) {
		glm::vec3 pcenter = a.position + a.size * 0.5f;
		pcenter.y = a.position.y + a.size.y;
		int x = (int)pcenter.x;
		int aboveHead = (int)(a.position.y - 0.01f);
		int topOfHead = (int)(a.position.y);
		int aboveFoot = (int)(pcenter.y);
		int belowFoot = (int)(pcenter.y + 0.01f);
		// collision?
		auto tileAboveHead = w.getTile(x, aboveHead);
		auto tileBelowHead = w.getTile(x, topOfHead);
		auto tilePlayer = w.getTile(x, aboveFoot);
		auto tileBelow = w.getTile(x, belowFoot);
		if (tileAboveHead.solid())
			return true;
		if (tileBelow.solid()) {
			return true;
		}
		return false;
	}

	void FlyPhysicsComponent::update(Actor& a, World& w) {
		glm::vec3 pdiff = a.position - a.lastPosition;
		float plength = std::abs(pdiff.y);
		if (touching(a, w) && plength < 0.0001f) {
			a.physicsInfo.v.y = 0.0f;
		}
		float speed = 5;
		// update acceleration
		glm::vec3 acceleration = -w.worldPhysicsInfo.d / a.physicsInfo.mass * a.velocity;
		/*if (a.physicsInfo.v.y > 0.0f)
			acceleration += 5.0f * w.worldPhysicsInfo.g;
		else
			acceleration += 3.0f * w.worldPhysicsInfo.g;

		if (a.velocity.y != 0.0f && a.physicsInfo.v.y == 0.0f) {
			a.physicsInfo.v.y = -2.0f * w.worldPhysicsInfo.g.y;
		}*/
		glm::vec3 vold = a.physicsInfo.v;
		//vold.x = a.velocity.x;
		//vold.y = a.velocity.y;
		direction += a.velocity.x/200;
		float pi = 3.1415926;
		int deg = int(direction * (180 / pi));
		deg = deg % 360;
		a.setSprite(0, 8);
		vold.x = cos(direction)*a.speed;
		vold.y = sin(direction)*a.speed;
		glm::vec3 vnew = vold + a.dt * acceleration;
		// float vlength = glm::length(vnew);
		a.physicsInfo.v = vnew;
		a.position += 0.5f * (vold + vnew) * a.dt;

		if (a.clipToWorld) {
			a.position.x = clamp<float>(a.position.x, 1, (float)w.worldSizeX - a.size.x);
			a.position.y = clamp<float>(a.position.y, 1, (float)w.worldSizeY - a.size.y - 1);
		}
	}
} // namespace GameLib
