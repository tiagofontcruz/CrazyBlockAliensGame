#include "BlockEntity.h"

extern b2World *world;
extern std::vector<Sprite *> blockSprites;

BlockEntity * MakeBlock(BlockType btype, MaterialType mtype, b2Vec2 pixelCoords,
	float angleInDegrees, int maximumHP)
{
	BlockEntity * blockEntity = new BlockEntity();
	blockEntity->blockType = btype;
	blockEntity->materialType = mtype;

	b2BodyDef bodyDef;
	
	bodyDef.type = b2_dynamicBody; //make it a dynamic body i.e. one moved by physics
	bodyDef.position = Pixels2Physics(pixelCoords); //set its position in the world
	bodyDef.angle = deg2rad(angleInDegrees);

	bodyDef.angularDamping = 1.8f;

	bodyDef.userData.pointer = reinterpret_cast<uintptr_t> (blockEntity);

	blockEntity->body = world->CreateBody(&bodyDef); //create the body and add it to the world

	b2FixtureDef fixtureDef;

	// Define a shape for our body.
	b2PolygonShape polygon;
	b2CircleShape circle;

	switch (btype)
	{
	case BlockType::LARGE_TRIANGLE:
	{
		// This defines a triangle in CCW order.
		b2Vec2 vertices[3];
		
		float cx = 580 + 140 / 2;
		float cy = 1840 + 70 / 2;

		vertices[0].Set((650.f - cx) / PTM_RATIO, (cy - 1841.0f) / PTM_RATIO);
		vertices[1].Set((581.0f - cx) / PTM_RATIO, (cy - 1909.0f) / PTM_RATIO);
		vertices[2].Set((719.0f - cx) / PTM_RATIO, (cy - 1909.0f) / PTM_RATIO);

		int32 count = 3;		
		polygon.Set(vertices, count);
		fixtureDef.shape = &polygon;
	}
		break;

	case BlockType::MEDIUM_BLOCK:
	{
		polygon.SetAsBox(68 / (2.f * PTM_RATIO), 220 / (2.f * PTM_RATIO));
		fixtureDef.shape = &polygon;
	}
		break;

	case BlockType::SMALL_CIRCLE: 
	{
		circle.m_radius = 70.f / (2 * PTM_RATIO);
		fixtureDef.shape = &circle;
	}
		break;

	case BlockType::LARGE_BLOCK:
	{
		polygon.SetAsBox(140 / (2.f * PTM_RATIO), 220 / (2.f * PTM_RATIO));
		fixtureDef.shape = &polygon;
	}
	break;

	default:
		assert(false);
	}//end switch(btype)

	switch (mtype)
	{
	case MaterialType::WOOD:
		fixtureDef.density = 0.3f;
		fixtureDef.restitution = 0.05;
		fixtureDef.friction = 0.5;
		break;
	case MaterialType::METAL:
		fixtureDef.density = 0.8f;
		fixtureDef.restitution = 0.10;
		fixtureDef.friction = 0.3;
		break;
	case MaterialType::ICE:
		fixtureDef.density = 0.5f;
		fixtureDef.restitution = 0.03;
		fixtureDef.friction = 0.1;
		break;
	case MaterialType::ROCK:
		fixtureDef.density = 0.10f;
		fixtureDef.restitution = 0.07;
		fixtureDef.friction = 0.7;
		break;
	default:
		assert(false);
	}//end switch(mtype)

	blockEntity->body->CreateFixture(&fixtureDef);

	int numBlockTypesToSkip = (int) btype;
	int numMaterials = (int) MaterialType::END;
	int numSpritesToSkip = numBlockTypesToSkip * numMaterials * 3; //3 sprites per material/shape

	//add sprites
	blockEntity->sprite = blockSprites[numSpritesToSkip + (int)mtype *3];
	blockEntity->spriteList.push_back(blockSprites[numSpritesToSkip + (int)mtype * 3 + 1]);
	blockEntity->spriteList.push_back(blockSprites[numSpritesToSkip + (int)mtype * 3 + 2]);

	blockEntity->maxHP = blockEntity->hp = maximumHP;

	return blockEntity;	
}