#pragma once

#include "Packet.h"

class LevelRocketSoundRemovePacket : public Packet, public enable_shared_from_this<LevelRocketSoundRemovePacket>
{

private:
	int rocketId;

public:
	LevelRocketSoundRemovePacket();
	LevelRocketSoundRemovePacket(int rocketId);

	virtual void read(DataInputStream* dis);
	virtual void write(DataOutputStream* dos);
	int getRocketId();
	virtual void handle(PacketListener* listener);
	virtual int getEstimatedSize();

public:
	static shared_ptr<Packet> create() { return std::make_shared<LevelRocketSoundRemovePacket>(); }
	virtual int getId() { return 213; }
};
