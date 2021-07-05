#include "Entity.h"

void Entity::Update()
{
	if (!pause) {

		//if()
		//velocity.y = -9.78;
		//if floor collision stop falling
		if (pos.y <= 0 && velocity.y <= 0) {
			velocity.y = 0;
			pos.y = 0;
			canJump = true;
		}
		else {
			velocity.y -= gravity;
		}
		//if (world->getChunk(floor(pos.x / 16), floor(pos.y / 16), floor(pos.z / 16))->getBlock((int)pos.x % 16, (int)pos.y % 16, (int)pos.z % 16)->GetID() != 0) {
		//	velocity.x += (int)pos.x % 16;
		//	velocity.y += (int)pos.y % 16;
		//	velocity.z += (int)pos.z % 16;
		//}

		//move based on velocity
		pos += velocity;

		//decrease velocity
		if (velocity.x > 0) {
			velocity.x -= .01;
		}if (velocity.y > 0) {
			velocity.y -= .01;
		}if (velocity.z > 0) {
			velocity.z -= .01;
		}

		//ci::app::console() << "velocity: vec3(" << velocity.x << "," << velocity.y << "," << velocity.z << ")\n";
	}
}

Entity::Entity(World* wrld)
{
	world = wrld;
	velocity = ci::vec3(0);
	canJump = true;
	gravity = .02;
	speed = 0;
}
