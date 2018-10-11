#include "stdafx.h"
#include "Role.h"


Role::Role()
{
}


Role::~Role()
{
}

Role::eTeam Role::getTeam(sRole role)
{
	return getTeam(role.roles[0]);
}

Role::eTeam Role::getTeam(eRole role)
{
	switch (role) {
	case Godfather:
	case Mafioso:
	case Consiglierge:
	case Consort:
	case Disguiser:
	case Framer:
	case Janitor: return Mafia;

	case Arsonist:
	case SerialKiller:
	case Werewolf:
	case Witch:
	case Jester:
	case Executioner: return Neutral;
	default: return Town;
	}
}

Role::sRole Role::getSRole(eRole role)
{
	return sRole{ std::vector<eRole>({ role }), getShorthand(role) };
}

std::string Role::getShorthand(eRole role)
{
	switch (role) {
	case Bodyguard: return "BG";
	case Jailor: return "JL";
	case Doctor: return "DOC";
	case Sheriff: return "SHF";
	case Spy: return "SPY";
	case Investigator: return "INV";
	case Medium: return "MED";
	case Transporter: return "TP";
	case Retributionist: return "RET";
	case Mayor: return "MAY";
	case Escort: return "ESC";
	case Veteran: return "VET";
	case Vigilante: return "VIG";
	case Godfather: return "GF";
	case Mafioso: return "MAF";
	case Consiglierge: return "CSG";
	case Consort: return "CRT";
	case Disguiser: return "DIS";
	case Framer: return "FRA";
	case Janitor: return "JAN";
	case Arsonist: return "ARS";
	case SerialKiller: return "SK";
	case Werewolf: return "WW";
	case Witch: return "WTC";
	case Jester: return "JES";
	case Executioner: return "EXE";
	default: return "";
	}
}

std::string Role::getShorthand(eTeam team)
{
	switch (team) {
	case Town: return "Town";
	case Mafia: return "Mafia";
	case Neutral: return "Neutral";
	default: return "";
	}
}

Role::sRole Role::rt()
{
	return { std::vector<eRole>({ Bodyguard, Doctor, Spy, Sheriff, Investigator, Veteran, Vigilante }), "RT" };
}

Role::sRole Role::tp()
{
	return { std::vector<eRole>({ Bodyguard, Doctor }), "TP" };
}

Role::sRole Role::ti()
{
	return { std::vector<eRole>({ Spy, Sheriff, Investigator }), "TI" };
}

Role::sRole Role::ts()
{
	return { std::vector<eRole>({ Medium, Transporter, Retributionist, Mayor, Escort }), "TS" };
}

Role::sRole Role::tk()
{
	return { std::vector<eRole>({ Veteran, Vigilante }), "TK" };
}

Role::sRole Role::rm()
{
	return { std::vector<eRole>({ Godfather, Mafioso, Consiglierge, Consort, Disguiser, Framer, Janitor, Blackmailer }), "RM" };
}

Role::sRole Role::ne()
{
	return { std::vector<eRole>({ Witch, Jester, Executioner }), "NE" };
}

Role::sRole Role::nk()
{
	return { std::vector<eRole>({ Arsonist, SerialKiller, Werewolf }), "NK" };
}
