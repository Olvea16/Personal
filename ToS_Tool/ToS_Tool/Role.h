#pragma once

#include <string>
#include <vector>

class Role
{

public:
	enum eRole {
		//TOWN
		Jailor,
		//TP
		Bodyguard, Doctor,
		//TI
		Spy, Sheriff, Investigator,
		//TS
		Medium, Transporter, Retributionist, Mayor, Escort,
		//TK
		Veteran, Vigilante,

		//MAFIA
		Godfather, Mafioso,
		Consiglierge, Consort,
		Disguiser, Framer,
		Janitor, Blackmailer,

		//NEUTRAL
		//Killing
		Arsonist, SerialKiller, Werewolf,

		//Evil
		Witch, Jester, Executioner
	};

	enum eTeam { Town, Neutral, Mafia };

	struct sRole {
		std::vector<eRole> roles;
		std::string shorthand;
	};

	Role();
	~Role();

	static eTeam getTeam(sRole role);
	static eTeam getTeam(eRole role);

	static sRole getSRole(eRole role);
	static std::string getShorthand(eRole role);
	static std::string getShorthand(eTeam team);

	static sRole rt();
	static sRole tp();
	static sRole ti();
	static sRole ts();
	static sRole tk();
	static sRole rm();
	static sRole ne();
	static sRole nk();


	sRole RT{ std::vector<eRole>({ Bodyguard, Doctor, Spy, Sheriff, Investigator, Veteran, Vigilante }), "RT" };
	sRole TP{ std::vector<eRole>({ Bodyguard, Doctor }), "TP" };
	sRole TI{ std::vector<eRole>({ Spy, Sheriff, Investigator }), "TI" };
	sRole TS{ std::vector<eRole>({ Medium, Transporter, Retributionist, Mayor, Escort }), "TS" };
	sRole TK{ std::vector<eRole>({ Veteran, Vigilante }), "TK" };

	sRole RM{ std::vector<eRole>({ Mafioso, Consiglierge, Consort, Disguiser, Framer, Janitor, Blackmailer }), "RM" };

	sRole NE{ std::vector<eRole>({ Witch, Jester, Executioner }), "NE" };
	sRole NK{ std::vector<eRole>({ Arsonist, SerialKiller, Werewolf }), "NK" };
};

