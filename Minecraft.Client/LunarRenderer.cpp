#include "stdafx.h"
#include "LunarRenderer.h"
#include "../Minecraft.World/Skeleton.h"

ResourceLocation LunarRenderer::LUNAR_LOCATION = ResourceLocation(TN_MOB_LUNAR);

LunarRenderer::LunarRenderer() : HumanoidMobRenderer(new HumanoidModel(0), 0.5f)
{
}

ResourceLocation* LunarRenderer::getTextureLocation(shared_ptr<Entity> entity)
{
    return &LUNAR_LOCATION;
}