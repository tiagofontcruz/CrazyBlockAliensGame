#pragma once

#include "Entity.h"
//Defines the enemy's shape (there is only one shape, but you can add more)
enum class EnemyType { SQUARE = 0, END };
//Defines the enemy's color
enum class MaterialEnemyType { BLUE = 0, GREEN, YELLOW, END };

class EnemyEntity : public Entity
{
public:
	EnemyType enemyType;
	MaterialEnemyType materialEnemyType;
	int hp;
	int maxHP;
	std::vector<Sprite*> spriteList;

	EnemyEntity()
	{
		//typeID is implemented apart from the blocks
		typeID = ENTITYALIEN;
		enemyType = EnemyType::SQUARE;
		materialEnemyType = MaterialEnemyType::BLUE;
		maxHP = hp = 200;
	}

	//Damage() returns true if we should kill this object
	bool Damage(int damage)
	{
		hp -= damage;
		if (hp < 1) return true;
		//Verifies if actual hp is less then a half of maximum hp to change the sprite
		if (hp < maxHP / 2) sprite = spriteList[0]; 		
		return false;
	}
};

EnemyEntity* MakeEnemy(EnemyType btype, MaterialEnemyType mtype, b2Vec2 pixelCoords,
	float angleInDegrees, int maximumHP);
