/*
*==============================================*  
*	   _/_/_/  _/_/_/                          *
*     _/        _/   _/   _/                   *
*    _/_/_/    _/     _/_/                     *
*   _/        _/      _/_/                     *
*  _/      _/_/_/   _/   _/                    *
*==============================================*
*           _/_/_/  _/_/_/  _/_/_/   _/_/_/    *
*          _/      _/  _/  _/  _/   _/         *
*         _/      _/  _/  _/_/_/   _/_/_/      *
*        _/_/_/  _/_/_/  _/   _/  _/           *
*    2015 Dev-KM             _/ _/_/_/_/       *
* -------------------------------------------- * 
* - Developer(s): KM                           *
* - Contacto: krizttian@live.com               *
* - Copyright (C) 2014 - 2015 FixCore.         *                                                
*==============================================*
*/
#include "ScriptPCH.h"
#include "Chat.h"

const int PLAYER_QUEUE = 4;
static const Position playerSpawnPoint[PLAYER_QUEUE] = 
{
	{-7473.95f, -1088.11f, 896.78f, 4.38455f},
    {-6379.22f, 1256.77f, 7.18803f, 2.9329f},
    {-775.036f, 1511.92f, 137.398f, 4.71829f},
    {-6414.02f, -3507.6f, 402.778f, 2.03819f},
};

class global_teleporter : public CreatureScript
{
public:
    global_teleporter() : CreatureScript("global_teleporter") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pPlayer->isInCombat())
        {
            pPlayer->GetSession()->SendNotification("ESTAS EN COMBATE!");
            return false;
        }
		pPlayer->ADD_GOSSIP_ITEM(1, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Mimiron_01:24|t|r Equipamiento", GOSSIP_SENDER_MAIN, 1);
		pPlayer->ADD_GOSSIP_ITEM(1, "|cff00ff00|TInterface\\icons\\Spell_Arcane_PortalDalaran:24|t|r Dalaran", GOSSIP_SENDER_MAIN, 3);
		pPlayer->ADD_GOSSIP_ITEM(1, "|cff00ff00|TInterface\\icons\\Achievement_Arena_2v2_4:24|t|r Gurubashi Arena", GOSSIP_SENDER_MAIN, 2);
		pPlayer->ADD_GOSSIP_ITEM(1, "|cff00ff00|TInterface\\icons\\Achievement_Arena_2v2_4:24|t|r Boss tenebroso", GOSSIP_SENDER_MAIN, 4);
		pPlayer->ADD_GOSSIP_ITEM(1, "|cff00ff00|TInterface\\icons\\Spell_Arcane_PortalDalaran:24|t|r Orgrimmar", GOSSIP_SENDER_MAIN, 5);
		pPlayer->ADD_GOSSIP_ITEM(1, "|cff00ff00|TInterface\\icons\\Spell_Arcane_PortalDalaran:24|t|r Ventormenta", GOSSIP_SENDER_MAIN, 6);


		pPlayer->SEND_GOSSIP_MENU(80001, pCreature->GetGUID());        
        return true;
    }

	bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
	{
		pPlayer->PlayerTalkClass->ClearMenus();
		if (pPlayer->getLevel() >= 10){
			switch (uiAction)
			{
			case 1: // Mercado Global
			{
				pCreature->CastSpell(pPlayer, 35517, false);
				pPlayer->TeleportTo(37, -26.347364f, 973.548086f, 348.492828f, 3.810720f);
				ChatHandler(pPlayer->GetSession()).PSendSysMessage("|cffff6060[Destyne]:|r Estas Siendo telestransportado hacia: |cFFFF4500Global Equipamiento Destynepvp|r!", pPlayer->GetName());
			}break;

			case 2: // Gurubashi Arena
			{
				pCreature->CastSpell(pPlayer, 35517, false);
				pPlayer->TeleportTo(0, -13226.437500f, 232.104935f, 33.287682f, 1.133178f);
				ChatHandler(pPlayer->GetSession()).PSendSysMessage("|cffff6060[Destyne]:|r Estas Siendo telestransportado hacia: |cFFFF4500Gurubashi Arena - (ZONA PVP)|r!", pPlayer->GetName());
			}break;

			case 3: // Dalaran
			{
				pCreature->CastSpell(pPlayer, 35517, false);
				pPlayer->TeleportTo(571, 5804.149902f, 624.770996f, 647.767029f, 1.640000f);
				ChatHandler(pPlayer->GetSession()).PSendSysMessage("|cffff6060[Destyne]:|r Estas Siendo telestransportado hacia: |cFFFF4500Dalaran - (SANTUARIO)|r!", pPlayer->GetName());
			}break;

			case 4: // boss
			{
				pCreature->CastSpell(pPlayer, 35517, false);
				pPlayer->TeleportTo(723, -7727.085449f, -410.751129f, 242.850388f, 0.192093f);
				ChatHandler(pPlayer->GetSession()).PSendSysMessage("|cffff6060[Destyne]:|r Estas Siendo telestransportado hacia: |cFFFF4500Boss Tenebroso - (ZONA de PELIGRO)|r!", pPlayer->GetName());
			}break;


			case 5: // orgrimmar
			{
				pCreature->CastSpell(pPlayer, 35517, false);
				pPlayer->TeleportTo(1, 1360.060059f, -4375.950195f, 26.096100f, 0.243312f);
				ChatHandler(pPlayer->GetSession()).PSendSysMessage("|cffff6060[Destyne]:|r Estas Siendo telestransportado hacia: |cFFFF4500Orgrimmar - (HORDA)|r!", pPlayer->GetName());
			}break;

			case 6: // Ventormenta
			{
				pCreature->CastSpell(pPlayer, 35517, false);
				pPlayer->TeleportTo(0, -9117.101563f, 372.650330f, 98.247879f, 0.747003f);
				ChatHandler(pPlayer->GetSession()).PSendSysMessage("|cffff6060[Destyne]:|r Estas Siendo telestransportado hacia: |cFFFF4500Ventormenta - (ALIANZA)|r!", pPlayer->GetName());
			}break;



			{
				OnGossipHello(pPlayer, pCreature);
				return true;
			}break;
			}
			pPlayer->CLOSE_GOSSIP_MENU();
			return true;
		}
		else if (pPlayer->getLevel() <= 9)
		{
			ChatHandler(pPlayer->GetSession()).PSendSysMessage("Tienes que ser nivel 10 para usar el teleport");
			pPlayer->PlayerTalkClass->SendCloseGossip();
			return true;

		}
	}


};

void AddSC_global_teleporter()
{
    new global_teleporter();
}
