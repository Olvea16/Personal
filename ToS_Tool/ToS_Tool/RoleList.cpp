#include "stdafx.h"
#include "RoleList.h"

#include "..\..\ADA_PortfolioAssignment_1\ADA_PortfolioAssignment_1\ConsoleMatrix.h"


RoleList::RoleList()
{
}

RoleList::RoleList(std::vector<Role::sRole> roles)
{
	for (Role::sRole r : roles) addRole(r);
}


RoleList::~RoleList()
{
}

void RoleList::addRole(Role::sRole role)
{
	roles.push_back(std::pair<Player, Role::sRole>(Player(), role));
}

void RoleList::confirm(Role::sRole role, Player player)
{
	confirmed.push_back(std::pair<Player, Role::sRole>(player, role));
}

void RoleList::kill(Player player, Role::sRole role)
{
}

void RoleList::claim(Player player, Role::sRole role)
{
}

void RoleList::unclaim(Player player, Role::sRole role)
{
}

Role RoleList::removePlayer(RoleVector list, Player player)
{
	return Role();
}

Player RoleList::removeRole(RoleVector list, Role::sRole role)
{
	return Player();
}

void RoleList::print()
{
	std::cout << "Roles: " << std::endl;
	print(roles);
	std::cout << std::endl;

	std::cout << "Confirmed: " << std::endl;
	print(confirmed);
	std::cout << std::endl;

	std::cout << "Claimed: " << std::endl;
	print(claimed);
	std::cout << std::endl;

	std::cout << "Dead: " << std::endl;
	print(dead);
	std::cout << std::endl;

	std::cout << "Free: " << std::endl;
	print(free);
	std::cout << std::endl;
}

void RoleList::print(RoleVector list)
{
	ConsoleMatrix cM;
	cM.addRow(std::vector<std::string>({ "Role:", "Player:" }));
	for (std::pair<Player, Role::sRole> p : list) cM.addRow(std::vector<std::string>({ p.second.shorthand, p.first.name}));
	cM.print();
}
