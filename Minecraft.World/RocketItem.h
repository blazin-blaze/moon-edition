#pragma once
#include "Item.h"

class Player;
class Level;

class RocketItem : public Item
{
public:

	RocketItem(int id);

	virtual bool TestUse(shared_ptr<ItemInstance> itemInstance, Level* level, shared_ptr<Player> player);
	virtual shared_ptr<ItemInstance> use(shared_ptr<ItemInstance> itemInstance, Level* level, shared_ptr<Player> player);
};