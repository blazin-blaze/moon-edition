#pragma once
#include "HumanoidMobRenderer.h"

class LunarRenderer : public HumanoidMobRenderer
{
private:
    static ResourceLocation LUNAR_LOCATION;

public:
    LunarRenderer();

protected:
    virtual ResourceLocation* getTextureLocation(shared_ptr<Entity> entity);
};
