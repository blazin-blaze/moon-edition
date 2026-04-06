#include "stdafx.h"
#include "com.mojang.nbt.h"
#include "net.minecraft.world.entity.h"
#include "net.minecraft.world.entity.player.h"
#include "net.minecraft.world.item.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.level.material.h"
#include "net.minecraft.world.level.tile.h"
#include "net.minecraft.world.phys.h"
#include "net.minecraft.world.damagesource.h"
#include "Rocket.h"

// 4J - added for common ctor code
void Rocket::_init()
{
	// 4J Stu - This function call had to be moved here from the Entity ctor to ensure that
	// the derived version of the function is called
	this->defineSynchedData();
	launchingCooldown = 0;
}



Rocket::Rocket(Level* level) : Entity(level)
{
	_init();
}


bool Rocket::makeStepSound()
{
	return false;
}

void Rocket::defineSynchedData()
{
	entityData->define(DATA_HAS_LAUNCHED, false);
	entityData->define(DATA_ID_DAMAGE, false);
}


AABB* Rocket::getCollideAgainstBox(shared_ptr<Entity> entity)
{
	return entity->bb;
}

AABB* Rocket::getCollideBox()
{
	return bb;
}

bool Rocket::isPushable()
{
	return !getLaunched();
}

Rocket::Rocket(Level* level, double x, double y, double z) : Entity(level)
{
	_init();
	//setPos(x, y + heightOffset, z);
	setPos(x, y, z);

	xd = 0;
	yd = 0;
	zd = 0;

	xo = x;
	yo = y;
	zo = z;
}

double Rocket::getRideHeight()
{
	return heightOffset + 0.6F;
}

bool Rocket::isPickable()
{
	return !removed;
}

void Rocket::tick()
{
	Entity::tick();

	if (getDamage() > 0) setDamage(getDamage() - 1);

	if (getLaunched() && launchingCooldown == 0) {
		absMoveTo(x, y + 20, z, yRot, xRot); //2.5
		launchingCooldown = 10;
	}

	if (getLaunched()) {
		level->addParticle(eParticleType_smokeBig, x, y + 0.3f, z, 0,-1.5f,0);
	}

	if (launchingCooldown > 0) launchingCooldown--;

	if (rider.lock() != nullptr)
	{
		if (rider.lock()->removed) {
			rider = weak_ptr<Entity>();
			setLaunched(false);
		}
	}

	int tileUnder = level->getTile(Mth::floor(x), Mth::floor(y - 0.15), Mth::floor(z));
	if (tileUnder == 0 && !onGround && !getLaunched())
	{
		yd -= 0.04f;
	}
	move(xd, yd, zd);
}

void Rocket::positionRider()
{
	if (rider.lock() == nullptr) return;
	// We minus 0.4 to ensure that the player is not hovering above the Rocket.
	rider.lock()->setPos(x, y + getRideHeight() + rider.lock()->getRidingHeight() - 0.4, z);
}


void Rocket::addAdditonalSaveData(CompoundTag* base)
{
	base->putBoolean(L"hasLaunched", getLaunched());
}

void Rocket::readAdditionalSaveData(CompoundTag* base)
{
	setLaunched(base->getBoolean(L"hasLaunched"));
}


float Rocket::getShadowHeightOffs()
{
	return 0;
}

wstring Rocket::getName()
{
	return L"Rocket";
}

bool Rocket::interact(shared_ptr<Player> player)
{
	if ((rider.lock() != nullptr) && rider.lock()->instanceof(eTYPE_PLAYER) && (rider.lock() != player)) return true;
	if (!level->isClientSide)
	{
		// 4J HEG - Fixed issue with player not being able to dismount Rocket (issue #4446)
		player->ride(rider.lock() == player ? nullptr : shared_from_this());
		setLaunched(true);
	}
	return true;
}

void Rocket::setLaunched(bool launched) {
	entityData->set(DATA_HAS_LAUNCHED, launched);
}

bool Rocket::getLaunched() {
	return entityData->getInteger(DATA_HAS_LAUNCHED);
}

bool Rocket::hurt(DamageSource* source, float hurtDamage)
{
	if (isInvulnerable()) return false;
	if (rider.lock() != nullptr && rider.lock() == source->getEntity()) return false;
	if (level->isClientSide || removed) return true;

	// 4J-JEV: Fix for #88212,
	// Untrusted players shouldn't be able to damage minecarts or boats.
	if (dynamic_cast<EntityDamageSource*>(source) != nullptr)
	{
		shared_ptr<Entity> attacker = source->getDirectEntity();

		if (attacker->instanceof(eTYPE_PLAYER) && !dynamic_pointer_cast<Player>(attacker)->isAllowedToHurtEntity(shared_from_this()))
		{
			return false;
		}
	}

	setDamage(getDamage() + hurtDamage * 10);
	markHurt();

	// 4J Stu - Brought froward from 12w36 to fix #46611 - TU5: Gameplay: Minecarts and boat requires more hits than one to be destroyed in creative mode
	// 4J-PB - Fix for XB1 #175735 - [CRASH] [Multi-Plat]: Code: Gameplay: Placing a boat on harmful surfaces causes the game to crash
	bool creativePlayer = (source->getEntity() != nullptr) && source->getEntity()->instanceof(eTYPE_PLAYER) && dynamic_pointer_cast<Player>(source->getEntity())->abilities.instabuild;

	if (creativePlayer || getDamage() > 20 * 2)
	{
		if (rider.lock() != nullptr) rider.lock()->ride(shared_from_this());
		if (!creativePlayer) spawnAtLocation(Item::rocket_Id, 1, 0);
		remove();
	}
	return true;
}

void Rocket::setDamage(float damage)
{
	entityData->set(DATA_ID_DAMAGE, damage);
}

float Rocket::getDamage()
{
	return entityData->getFloat(DATA_ID_DAMAGE);
}