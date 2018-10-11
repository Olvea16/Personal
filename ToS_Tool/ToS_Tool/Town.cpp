#include "stdafx.h"
#include "Town.h"


Town::Town()
{
}

Town::Town(eGametype gametype, Player me, Role::eRole myRole) : me(std::pair<Player, Role::sRole>(me, Role::getSRole(myRole)))
{
	if (gametype == standard) {
		std::vector<Role::sRole> roles = { Role::getSRole(Role::Jailor), Role::ti(), Role::ti(), Role::ts(), Role::tp(), Role::tk(), Role::rt(), Role::rt(), Role::rt(), Role::getSRole(Role::Godfather), Role::getSRole(Role::Mafioso), Role::rm(), Role::rm(), Role::ne(), Role::nk() };
		for (Role::sRole r : roles) rL.addRole(r);
		rL.confirm(this->me.second, this->me.first);
	}
}


Town::~Town()
{
}

void Town::confirm(Role::eRole role, Player player)
{
	rL.confirm(Role::getSRole(role), player);
}

void Town::print()
{
	rL.print();
}
