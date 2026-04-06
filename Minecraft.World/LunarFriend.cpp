#include "stdafx.h"

#include "LunarFriend.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.entity.ai.attributes.h"
#include "net.minecraft.world.entity.ai.goal.h"
#include "net.minecraft.world.entity.ai.goal.target.h"
#include "net.minecraft.world.entity.ai.navigation.h"
#include "net.minecraft.world.entity.monster.h"
#include "net.minecraft.world.entity.projectile.h"
#include "net.minecraft.world.phys.h"
#include "net.minecraft.world.level.tile.h"
#include "net.minecraft.world.damagesource.h"
#include "net.minecraft.world.level.biome.h"
#include "net.minecraft.world.item.h"

void LunarFriend::_init()
{
	this->defineSynchedData();
	registerAttributes();
	setHealth(getMaxHealth());

	getNavigation()->setAvoidWater(true);
	goalSelector.addGoal(1, new RandomStrollGoal(this, 1.0));
	goalSelector.addGoal(2, new LookAtPlayerGoal(this, typeid(Player), 6));
	goalSelector.addGoal(3, new RandomLookAroundGoal(this));
}

LunarFriend::LunarFriend(Level* level) : PathfinderMob(level)
{
	_init();
}

LunarFriend::LunarFriend(Level* level, float x, float y, float z) : PathfinderMob(level)
{
	_init();
	setPos(x, y, z);

	xd = 0;
	yd = 0;
	zd = 0;

	xo = x;
	yo = y;
	zo = z;
}

void LunarFriend::registerAttributes()
{
	LivingEntity::registerAttributes();

	getAttributes()->registerAttribute(SharedMonsterAttributes::FOLLOW_RANGE)->setBaseValue(16);

	getAttribute(SharedMonsterAttributes::MAX_HEALTH)->setBaseValue(4);
	getAttribute(SharedMonsterAttributes::MOVEMENT_SPEED)->setBaseValue(0.2f);
}

void LunarFriend::causeFallDamage(float distance)
{
}

int LunarFriend::getAmbientSound()
{
	return -1;
}

int LunarFriend::getHurtSound()
{
	return -1;
}

int LunarFriend::getDeathSound()
{
	return -1;
}

int LunarFriend::getAmbientSoundInterval()
{
	return 20 * 6;
}

bool LunarFriend::removeWhenFarAway()
{
	return false;
}