/*
<--------------------------------------------------------------------------->
 - Developer(s): Ghostcrawler336
 - Edited: Synth
 - Complete: 100%
 - ScriptName: 'npc_changer' 
 - Comment: Tested.
 - Updated: 9/17/13.
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"

enum  defines
{
 faction_token = 110666, // Faction Change Token
 race_token = 110667, // Race Change Token
 customize_token = 110668,  // Customize Change Token
 rename_token = 110669, // Rename Change Token
};

class npc_changer : public CreatureScript
{
public:
	npc_changer() : CreatureScript("npc_changer"){}

	bool OnGossipHello(Player * pPlayer, Creature * pCreature)
	{


		pPlayer->ADD_GOSSIP_ITEM(4, "Cambiar raza x 2000 de valor ", GOSSIP_SENDER_MAIN, 0);
		pPlayer->ADD_GOSSIP_ITEM(4, "Cambiar de faccion x 4000 de valor", GOSSIP_SENDER_MAIN, 1);
		pPlayer->ADD_GOSSIP_ITEM(4, "Customizar pj x 1000 de valor", GOSSIP_SENDER_MAIN, 2);
		pPlayer->ADD_GOSSIP_ITEM(4, "Cambiar nombre x 500 de valor", GOSSIP_SENDER_MAIN, 3);
		pPlayer->PlayerTalkClass->SendGossipMenu(9425, pCreature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player * Player, Creature * Creature, uint32 sender, uint32 uiAction)
	{
		if (!Player)
			return true;
		if (sender == GOSSIP_SENDER_MAIN)
		{
			uint32 valor_points = Player->GetCurrency(CURRENCY_TYPE_VALOR_POINTS, true);

			switch (uiAction)
			{
			case 0:
				if (valor_points >= 2000)
				{
					Player->CLOSE_GOSSIP_MENU();
					Player->ModifyCurrency(CURRENCY_TYPE_VALOR_POINTS, -2000 * CURRENCY_PRECISION, true, true); //Conquest Points
					Player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
					Player->GetSession()->SendNotification("Necesitas reloguear!");
					Player->PlayerTalkClass->SendCloseGossip();
				}
				else
				{
					Player->GetSession()->SendNotification("No tienes suficientes puntos de Valor!");
					Player->PlayerTalkClass->SendCloseGossip();
				}
				break;
			case 1:
				if (valor_points >= 4000)
				{
					Player->CLOSE_GOSSIP_MENU();
					Player->ModifyCurrency(CURRENCY_TYPE_VALOR_POINTS, -4000 * CURRENCY_PRECISION, true, true); //Conquest Points
					Player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
					Player->GetSession()->SendNotification("Necesitas reloguear!");
					Player->PlayerTalkClass->SendCloseGossip();
				}
				else
				{
					Player->GetSession()->SendNotification("No tienes suficientes puntos de Valor!");
					Player->PlayerTalkClass->SendCloseGossip();
				}
				break;
			case 2:
				if (valor_points >= 1000)
				{
					Player->CLOSE_GOSSIP_MENU();
					Player->ModifyCurrency(CURRENCY_TYPE_VALOR_POINTS, -1000 * CURRENCY_PRECISION, true, true); //Conquest Points
					Player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
					Player->GetSession()->SendNotification("Necesitas reloguear!");
					Player->PlayerTalkClass->SendCloseGossip();

				}

				else
				{
					Player->GetSession()->SendNotification("No tienes suficientes puntos de Valor!");
					Player->PlayerTalkClass->SendCloseGossip();
				}
				break;
			case 3:
				if (valor_points >= 500)
				{
					Player->CLOSE_GOSSIP_MENU();
					Player->ModifyCurrency(CURRENCY_TYPE_VALOR_POINTS, -500 * CURRENCY_PRECISION, true, true); //Conquest Points
					Player->SetAtLoginFlag(AT_LOGIN_RENAME);
					Player->GetSession()->SendNotification("Necesitas reloguear!");
					Player->PlayerTalkClass->SendCloseGossip();

				}

				else
				{
					Player->GetSession()->SendNotification("No tienes suficientes puntos de Valor!");
					Player->PlayerTalkClass->SendCloseGossip();
				}
				break;
			}

			return true;
		}
	}
	};

	void AddSC_npc_changer()
	{
		new npc_changer();
	}
