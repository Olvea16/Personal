#pragma once

#include "Role.h"
#include "Player.h"

#include <iostream>

#define DEFAULT_ROLE std::vector<Role::eRole>(Role::eRole())

class RoleList
{
public:
	typedef std::vector<std::pair<Player, Role::sRole>> RoleVector;

	RoleList();
	RoleList(std::vector<Role::sRole> roles);
	~RoleList();

	void addRole(Role::sRole role);
	void confirm(Role::sRole role, Player player = Player());
	void kill(Player player, Role::sRole role = Role::sRole{ DEFAULT_ROLE, "" });
	void claim(Player player, Role::sRole role);
	void unclaim(Player player, Role::sRole role);

	Role removePlayer(RoleVector list, Player player);
	Player removeRole(RoleVector list, Role::sRole role);

	void print();
	void print(RoleVector list);

private:
	RoleVector roles;
	RoleVector confirmed;
	RoleVector claimed;
	RoleVector dead;
	RoleVector free;
};

