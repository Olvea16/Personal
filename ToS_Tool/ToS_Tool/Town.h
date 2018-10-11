#pragma once

#include "Player.h"
#include "Role.h"
#include "RoleList.h"

enum eGametype {
	standard
};

class Town
{
public:
	Town();
	Town(eGametype gametype, Player me, Role::eRole myRole);
	~Town();

	void confirm(Role::eRole role, Player player = Player());
	void print();

private:
	RoleList rL;
	std::pair<Player, Role::sRole> me;
};

