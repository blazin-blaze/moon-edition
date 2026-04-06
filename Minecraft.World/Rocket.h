#pragma once
#include "Entity.h"

class Rocket : public Entity
{
public:
	eINSTANCEOF GetType() { return eTYPE_ROCKET; };
	static Entity* create(Level* level) { return new Rocket(level); }

private:
	// 4J - added for common ctor code
	void _init();
public:
	static const int serialVersionUID = 0;

public:
	Rocket(Level* level);

protected:
	virtual bool makeStepSound();
	virtual void defineSynchedData();

public:
	virtual AABB* getCollideAgainstBox(shared_ptr<Entity> entity);
	virtual AABB* getCollideBox();
	virtual bool isPushable();

	Rocket(Level* level, double x, double y, double z);

	virtual double getRideHeight();
	virtual bool hurt(DamageSource* source, float damage);
	virtual bool isPickable();
	virtual bool getLaunched();
	virtual void setLaunched(bool launched);

private:
	int lSteps;
	double lx, ly, lz, lyr, lxr;
	double lxd, lyd, lzd;
	static const int DATA_HAS_LAUNCHED = 16;
	static const int DATA_ID_DAMAGE = 17;
	int launchingCooldown;

public:
	virtual void tick();
	virtual void positionRider();

protected:
	virtual void addAdditonalSaveData(CompoundTag* base);
	virtual void readAdditionalSaveData(CompoundTag* base);

public:
	virtual void setDamage(float damage);
	virtual float getDamage();
	virtual float getShadowHeightOffs();
	wstring getName();
	virtual bool interact(shared_ptr<Player> player);
};
