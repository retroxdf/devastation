#include "ScriptPCH.h"
 
class Exchanger_NPC : public CreatureScript
{
public:
    Exchanger_NPC() : CreatureScript("Exchanger_NPC") { }
 
    bool OnGossipHello(Player *player, Creature * creature)
    {
        if (player->isInCombat())
        {
            player->CLOSE_GOSSIP_MENU();
            creature->MonsterWhisper("You are in combat already!", player->GetGUID());
            return true;
        }
        else
        {
            player->ADD_GOSSIP_ITEM_EXTENDED(5, "100 puntos de valor para 1000 justicia", GOSSIP_SENDER_MAIN, 1, "¿Seguro que quieres intercambiar 100 Puntos de valor por 1000 de justicia?", 0, false);
            player->ADD_GOSSIP_ITEM_EXTENDED(5, "4000 justicia por 200 puntos de valor", GOSSIP_SENDER_MAIN, 2, "¿Seguro que quieres intercambiar 4000 de justicia por 200 puntos de valor?", 0, false);
			player->ADD_GOSSIP_ITEM_EXTENDED(5, "4000 justicia por 8000 de oro", GOSSIP_SENDER_MAIN, 3, "¿Seguro que quieres intercambiar 4000 de justicia por 8000 de oro?", 0, false);
			player->ADD_GOSSIP_ITEM_EXTENDED(5, "4000 justicia por 200 puntos de conquista", GOSSIP_SENDER_MAIN, 4, "¿Seguro que quieres intercambiar 4000 de justicia por 200 puntos de conquista?", 0, false);
        }
 
        player->SEND_GOSSIP_MENU(60040, creature->GetGUID());
        return true;
    }
 
    bool OnGossipSelect(Player * player, Creature * creature, uint32 sender, uint32 uiAction)
    {
        if (sender == GOSSIP_SENDER_MAIN)
        {
            player->PlayerTalkClass->ClearMenus();
            uint32 honor_points = player->GetCurrency(CURRENCY_TYPE_HONOR_POINTS, true);
            uint32 conquest_points = player->GetCurrency(CURRENCY_TYPE_CONQUEST_POINTS, true);
			uint32 valor_points = player->GetCurrency(CURRENCY_TYPE_VALOR_POINTS, true);
			uint32 justice_points = player->GetCurrency(CURRENCY_TYPE_JUSTICE_POINTS, true);
            switch (uiAction)
            {
            case 1:
                /*Note: Normally the value you use its value / 100 = ingame value but if we use * CURRENCY_PRECISION it will use exactly that amount*/
                if (valor_points >= 200)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->ModifyCurrency(CURRENCY_TYPE_VALOR_POINTS, -200 * CURRENCY_PRECISION, true, true); //Conquest Points
                    player->ModifyCurrency(CURRENCY_TYPE_JUSTICE_POINTS, +1000 * CURRENCY_PRECISION, true, true); //Honor Points
                    creature->MonsterWhisper("|c00077766|r Has intercambiado 100 puntos de valor por 1000 puntos de justicia con éxito.!", player->GetGUID(), true);
 
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterWhisper("|c00077766|r No tienes suficientes puntos de valor.!", player->GetGUID(), true);
 
                    return false;
                }
                break;
				
            case 2:
				if (justice_points >= 4000)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->ModifyCurrency(CURRENCY_TYPE_VALOR_POINTS, +200 * CURRENCY_PRECISION, true, true); //Conquest Points
                    player->ModifyCurrency(CURRENCY_TYPE_JUSTICE_POINTS, -4000 * CURRENCY_PRECISION, true, true); //Honor Points
                    creature->MonsterWhisper("|c00077766|r Intercambiaste 4000 puntos de justicia por 200 puntos de valor exitosamente.!", player->GetGUID(), true);
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterWhisper("|c00077766|r No tienes suficientes puntos de justicia!", player->GetGUID(), true);
                    return false;
                }
                break;
				
			case 3:
				if (justice_points >= 4000)
				{
					player->CLOSE_GOSSIP_MENU();
					player->ModifyMoney(player->GetMoney() + 40000000);
					player->ModifyCurrency(CURRENCY_TYPE_JUSTICE_POINTS, -4000 * CURRENCY_PRECISION, true, true); //Honor Points
					creature->MonsterWhisper("|c00077766|r Intercambiaste 4000 puntos de justica por 4000 de oro.!", player->GetGUID(), true);
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					creature->MonsterWhisper("|c00077766|r No tienes suficientes puntos de justicia!", player->GetGUID(), true);
					return false;
				}
				break;
				
			case 4:
				if (justice_points >= 4000)
				{
					player->CLOSE_GOSSIP_MENU();
					player->ModifyCurrency(CURRENCY_TYPE_CONQUEST_POINTS, +200 * CURRENCY_PRECISION, true, true); //Conquest Points
					player->ModifyCurrency(CURRENCY_TYPE_JUSTICE_POINTS, -4000 * CURRENCY_PRECISION, true, true); //Honor Points
					creature->MonsterWhisper("|c00077766|r Intercambiaste 4000 puntos de justicia por 200 puntos de conquista exitosamente.!", player->GetGUID(), true);
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					creature->MonsterWhisper("|c00077766|r No tienes suficientes puntos de justicia!", player->GetGUID(), true);
					return false;
				}
				break;
			

            }





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
				me->MonsterSay("¡Cambia tus puntos de justicia aqui.!", LANG_UNIVERSAL, NULL);
				me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
				me->CastSpell(me, 44940);
				uiAdATimer = 61000;
			}
			else
				uiAdATimer -= diff;

			if (uiAdBTimer <= diff)
			{
				me->MonsterSay("Te sobra puntos de justicias acercate para ver las opciones que destyne tiene para ti.!", LANG_UNIVERSAL, NULL);
				me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
				uiAdBTimer = 61000;
			}
			else
				uiAdBTimer -= diff;

			if (uiAdCTimer <= diff)
			{
				me->MonsterSay("Cambia tu justicia por 8k de oro.!", LANG_UNIVERSAL, NULL);
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
 
void AddSC_Exchanger_NPC()
{
    new Exchanger_NPC();
}