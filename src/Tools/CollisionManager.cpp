#include "Tools/CollisionManager.h"

namespace collisionManager
{
	bool CollisionManager::CheckCollisionRecRec(Entity2D* entityOne, Entity2D* entityTwo)
	{
		bool collisionX = entityOne->getPosition().x + entityOne->getScale().x >= entityTwo->getPosition().x &&
						  entityTwo->getPosition().x + entityTwo->getScale().x >= entityOne->getPosition().x;

		bool collisionY = entityOne->getPosition().y + entityOne->getScale().y >= entityTwo->getPosition().y &&
						  entityTwo->getPosition().y + entityTwo->getScale().y >= entityOne->getPosition().y;

		if (collisionX && collisionY)
		{
			cout << "Sprite :" << entityOne->getScale().x << ", " << entityOne->getScale().y << endl;
			cout << "Box :" << entityTwo->getScale().x << ", " << entityTwo->getScale().y << endl;
		}

		return collisionX && collisionY;
	}
	bool CollisionManager::CheckCollisionTileEntity(Entity2D entity, float posX, float posY, float scaleX, float scaleY)
	{
        float aRight = entity.getPosition().x + glm::abs(entity.getScale().x) / 2;
        float bLeftSide = posX;
        float aLeftSide = entity.getPosition().x - glm::abs(entity.getScale().x) / 2;
        float bRightSide = posX + glm::abs(scaleX);

        // collision x-axis?
        bool collisionX = aRight >= bLeftSide &&
             bRightSide >= aLeftSide;

        float aUpSide = entity.getPosition().y + glm::abs(entity.getScale().y) / 2;
        float bDownSide = posY;
        float bUpSide = posY + glm::abs(scaleY);
        float aDownSide = entity.getPosition().y - glm::abs(entity.getScale().y) / 2;
        
		// collision y-axis?
        bool collisionY = aUpSide >= bDownSide &&
             bUpSide >= aDownSide;

        return collisionX && collisionY;
	}
}