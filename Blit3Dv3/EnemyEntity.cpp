#include "EnemyEntity.h"

extern b2World* world;
extern std::vector<Sprite*> enemySprites;

EnemyEntity *MakeEnemy(EnemyType btype, MaterialEnemyType mtype, b2Vec2 pixelCoords,
	float angleInDegrees, int maximumHP)
{
	EnemyEntity * enemyEntity = new EnemyEntity();
	enemyEntity->enemyType = btype;
	enemyEntity->materialEnemyType = mtype;

	b2BodyDef bodyDef;

	bodyDef.type = b2_dynamicBody; //make it a dynamic body i.e. one moved by physics
	bodyDef.position = Pixels2Physics(pixelCoords); //set its position in the world
	bodyDef.angle = deg2rad(angleInDegrees);

	bodyDef.angularDamping = 1.8f;

	bodyDef.userData.pointer = reinterpret_cast<uintptr_t> (enemyEntity);

	enemyEntity->body = world->CreateBody(&bodyDef); //create the body and add it to the world

	b2FixtureDef fixtureDef;

	// Define a shape for our body.
	b2PolygonShape polygon;	

	switch (btype)
	{
	case EnemyType::SQUARE:
	{
		polygon.SetAsBox(70 / (2.f * PTM_RATIO), 70 / (2.f * PTM_RATIO));
		fixtureDef.shape = &polygon;
	}
	break;

	default:
		assert(false);
	}//end switch(btype)

	//Verifies the enemy's color and apply the characteristics
	switch (mtype)
	{
	case MaterialEnemyType::BLUE:
		fixtureDef.density = 0.8f;
		fixtureDef.restitution = 0.10;
		fixtureDef.friction = 0.3;
		break;
	case MaterialEnemyType::GREEN:
		fixtureDef.density = 0.8f;
		fixtureDef.restitution = 0.10;
		fixtureDef.friction = 0.3;
		break;
	case MaterialEnemyType::YELLOW:
		fixtureDef.density = 0.8f;
		fixtureDef.restitution = 0.10;
		fixtureDef.friction = 0.3;
		break;
	default:
		assert(false);
	}//end switch(mtype)

	enemyEntity->body->CreateFixture(&fixtureDef);

	int numEnemyTypesToSkip = (int)btype;
	int numMaterials = (int)MaterialEnemyType::END;
	int numSpritesToSkip = numEnemyTypesToSkip * numMaterials * 2; //2 sprites per material/shape

	//add sprites
	enemyEntity->sprite = enemySprites[numSpritesToSkip + (int)mtype * 2];
	enemyEntity->spriteList.push_back(enemySprites[numSpritesToSkip + (int)mtype * 2 + 1]);

	enemyEntity->maxHP = enemyEntity->hp = maximumHP;

	return enemyEntity;
}