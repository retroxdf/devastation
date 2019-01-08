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

#define MSG_PLACE "Bienvenido a Destynepvp: Promocion 3 personajes Nivel 85 + 15k de Oro"

class npc_shop : public CreatureScript
{
public:
    npc_shop() : CreatureScript("npc_shop") { }
  
	bool OnGossipHello(Player* pPlayer, Creature* pCreature)
{
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_PLACE, GOSSIP_SENDER_MAIN,1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "No mejor no..", GOSSIP_SENDER_MAIN,2);
            pPlayer->SEND_GOSSIP_MENU(1, pCreature->GetGUID());
            return true;
}
	
	bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 Sender, uint32 Action)
        {
				if (Sender != GOSSIP_SENDER_MAIN)
					return false;
		
				pPlayer->PlayerTalkClass->ClearMenus();
								if (Action == 1)
									{
                        	   // QueryResult pResult = LoginDatabase.PQuery("select last_ip from account where id = %u", pPlayer->GetSession()->GetAccountId()); 																
								//Field * pFields = pResult->Fetch();
								//pFields[0].GetString();
								QueryResult Result = LoginDatabase.PQuery("select count(*) from account where last_ip = %u", pPlayer->GetSession()->GetRemoteAddress()); 	
								Field * rFields = Result->Fetch();
								int64 ip2 = rFields[0].GetInt64();
								if (ip2 > 1)
								{
										ChatHandler(pPlayer->GetSession()).PSendSysMessage("Bienvenido a Destyne donde tu escoges si levear o ser instant(puedes escoger hasta 3 personajes 85)");
										pPlayer->PlayerTalkClass->SendCloseGossip();
										return true;
								}
										QueryResult result = CharacterDatabase.PQuery("SELECT COUNT(*) FROM characters WHERE account = %u AND LEVEL = 85",pPlayer->GetSession()->GetAccountId());
										Field* field = result->Fetch();
										int8 chars = field[0].GetInt8();
									 if (chars > 2 && pPlayer->getLevel() != 85 )
										{
										ChatHandler(pPlayer->GetSession()).PSendSysMessage("Ya tienes 3 pjs 85 en esta cuenta.");
										pPlayer->PlayerTalkClass->SendCloseGossip();
										return true;
										}
										
									
										
								
								
								else if (pPlayer->getLevel() == 85)
									{
							 ChatHandler(pPlayer->GetSession()).PSendSysMessage("Ya eres Nivel 85");
                                   pPlayer->PlayerTalkClass->SendCloseGossip();
								   return true;
								   
								   }
								   }
								   //else if(Sender == GOSSIP_SENDER_MAIN)
								   
								
											switch(Action)
												{
														case 1:
                
														pPlayer->SetMoney(150000000);
														pPlayer->GiveLevel(85);
														pPlayer->UpdateSkillsToMaxSkillsForLevel();
				
														if(pPlayer->GetTeam() == ALLIANCE){ //ID DEL SPELL QUE LLEVE A SHOP ALIANZA
															pPlayer->TeleportTo(37, -26.347364f, 973.548086f, 348.492828f, 3.810720f);
														//pPlayer->CastSpell(pPlayer,61420,true,NULL,NULL,pPlayer->GetGUID());
																							}
														else { //ID DEL SPELL QUE LLEVE A SHOP HORDA
															pPlayer->TeleportTo(37, -26.347364f, 973.548086f, 348.492828f, 3.810720f);
														//pPlayer->CastSpell(pPlayer,34673,true,NULL,NULL,pPlayer->GetGUID());
																}
														pPlayer->PlayerTalkClass->SendCloseGossip();
														pPlayer->SaveToDB();
														break;
														case 2:
														pPlayer->PlayerTalkClass->SendCloseGossip();
														break;
												}
				
													
			return true;
		
		}


	struct gambler_passivesAI : public ScriptedAI
	{
		gambler_passivesAI(Creature * c) : ScriptedAI(c){ }

		uint32 uiAdATimer;
		uint32 uiAdBTimer;
		uint32 uiAdCTimer;

		void Reset()
		{
			uiAdATimer = 1000;
			uiAdBTimer = 23000;
			uiAdCTimer = 11000;
		}


		void UpdateAI(const uint32 diff)
		{

			if (uiAdATimer <= diff)
			{
				me->MonsterSay("¡Hoy me siento tan feliz de tenerte en Destynepvp.!", LANG_UNIVERSAL, NULL);
				me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
				me->CastSpell(me, 44940);
				uiAdATimer = 61000;
			}
			else
				uiAdATimer -= diff;

			if (uiAdBTimer <= diff)
			{
				me->MonsterSay("Ey tu.!", LANG_UNIVERSAL, NULL);
				me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
				uiAdBTimer = 61000;
			}
			else
				uiAdBTimer -= diff;

			if (uiAdCTimer <= diff)
			{
				me->MonsterSay("Acercate hablar conmigo para recibir tu promocion de Destyne.!", LANG_UNIVERSAL, NULL);
				me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
				uiAdCTimer = 61000;
			}
			else
				uiAdCTimer -= diff;
		}
	};

	CreatureAI * GetAI(Creature * pCreature) const
	{
		return new gambler_passivesAI(pCreature);
	}




};
	
	
void AddSC_npc_shop()
{
    new npc_shop();
}