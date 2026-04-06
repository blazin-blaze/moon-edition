#pragma once
#include "EntityRenderer.h"

class RocketModel;

class RocketRenderer : public EntityRenderer
{
private:
	RocketModel* rocketModel;
	static ResourceLocation ROCKET_LOCATION;

public:
	RocketRenderer();
	virtual void render(shared_ptr<Entity> mob, double x, double y, double z, float rot, float a);
	virtual ResourceLocation* getTextureLocation(shared_ptr<Entity> mob);
};