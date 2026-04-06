#pragma once

#include "PathfinderMob.h"
#include "Creature.h"

class Level;
class CompoundTag;

class LunarFriend : public PathfinderMob, public Creature
{
private:
	void _init();
public:
	eINSTANCEOF GetType() { return eTYPE_LUNAR; }
	static Entity* create(Level* level) { return new LunarFriend(level); }
public:
	LunarFriend(Level* level);
	LunarFriend(Level* level, float x, float y, float z);
protected:
	virtual void causeFallDamage(float distance);
	virtual int getAmbientSound();
	virtual int getHurtSound();
	virtual int getDeathSound();
	virtual void registerAttributes();

public:
	virtual int getAmbientSoundInterval();

protected:
	virtual bool removeWhenFarAway();
}; 
