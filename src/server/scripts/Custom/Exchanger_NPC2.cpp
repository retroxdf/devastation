#include "ScriptPCH.h"
 
class Exchanger_NPC2 : public CreatureScript
{
public:
    Exchanger_NPC2() : CreatureScript("Exchanger_NPC2") { }
 
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
            player->ADD_GOSSIP_ITEM_EXTENDED(5, "100 puntos de conquista para 1000 honor", GOSSIP_SENDER_MAIN, 1, "¿Seguro que quieres intercambiar 100 Puntos de conquista por 1000 de Honor?", 0, false);
            player->ADD_GOSSIP_ITEM_EXTENDED(5, "4000 honor por 200 puntos de conquista", GOSSIP_SENDER_MAIN, 2, "¿Seguro que quieres intercambiar 4000 Honor por 200 puntos de conquista?", 0, false);
			player->ADD_GOSSIP_ITEM_EXTENDED(5, "4000 honor por 4000 de oro", GOSSIP_SENDER_MAIN, 3, "¿Seguro que quieres intercambiar 4000 Honor por 4000 de oro?", 0, false);
			player->ADD_GOSSIP_ITEM_EXTENDED(5, "4000 honor por 200 puntos de valor", GOSSIP_SENDER_MAIN, 4, "¿Seguro que quieres intercambiar 4000 Honor por 200 puntos de valor?", 0, false);
			player->ADD_GOSSIP_ITEM_EXTENDED(5, "4000 honor por 4000 puntos de justicia", GOSSIP_SENDER_MAIN, 5, "¿Seguro que quieres intercambiar 4000 Honor por 4000 puntos de justicia?", 0, false);
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
                if (conquest_points >= 100)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->ModifyCurrency(CURRENCY_TYPE_CONQUEST_POINTS, -100 * CURRENCY_PRECISION, true, true); //Conquest Points
                    player->ModifyCurrency(CURRENCY_TYPE_HONOR_POINTS, +1000 * CURRENCY_PRECISION, true, true); //Honor Points
                    creature->MonsterWhisper("|c00077766|r Has intercambiado 100 puntos de conquista por 1000 puntos de honor con éxito.!", player->GetGUID(), true);
 
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterWhisper("|c00077766|r No tienes suficientes puntos de conquista.!", player->GetGUID(), true);
 
                    return false;
                }
                break;
 
            case 2:
                if (honor_points >= 4000)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->ModifyCurrency(CURRENCY_TYPE_CONQUEST_POINTS, +200 * CURRENCY_PRECISION, true, true); //Conquest Points
                    player->ModifyCurrency(CURRENCY_TYPE_HONOR_POINTS, -4000 * CURRENCY_PRECISION, true, true); //Honor Points
                    creature->MonsterWhisper("|c00077766|r Intercambiaste 4000 puntos de honor por 200 puntos de conquista exitosamente.!", player->GetGUID(), true);
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterWhisper("|c00077766|r No tienes suficientes puntos de honor!", player->GetGUID(), true);
                    return false;
                }
                break;
			case 3:
				if (honor_points >= 4000)
				{
					player->CLOSE_GOSSIP_MENU();
					player->ModifyMoney(player->GetMoney() + 40000000);
					player->ModifyCurrency(CURRENCY_TYPE_HONOR_POINTS, -4000 * CURRENCY_PRECISION, true, true); //Honor Points
					creature->MonsterWhisper("|c00077766|r Intercambiaste 4000 puntos de honor por 4000 de oro.!", player->GetGUID(), true);
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					creature->MonsterWhisper("|c00077766|r No tienes suficientes puntos de honor!", player->GetGUID(), true);
					return false;
				}
				break;
			case 4:
				if (honor_points >= 4000)
				{
					player->CLOSE_GOSSIP_MENU();
					player->ModifyCurrency(CURRENCY_TYPE_VALOR_POINTS, +200 * CURRENCY_PRECISION, true, true); //Conquest Points
					player->ModifyCurrency(CURRENCY_TYPE_HONOR_POINTS, -4000 * CURRENCY_PRECISION, true, true); //Honor Points
					creature->MonsterWhisper("|c00077766|r Intercambiaste 4000 puntos de honor por 200 puntos de valor exitosamente.!", player->GetGUID(), true);
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					creature->MonsterWhisper("|c00077766|r No tienes suficientes puntos de honor!", player->GetGUID(), true);
					return false;
				}
				break;
			case 5:
				if (honor_points >= 4000)
				{
					player->CLOSE_GOSSIP_MENU();
					player->ModifyCurrency(CURRENCY_TYPE_JUSTICE_POINTS, +4000 * CURRENCY_PRECISION, true, true); //Conquest Points
					player->ModifyCurrency(CURRENCY_TYPE_HONOR_POINTS, -4000 * CURRENCY_PRECISION, true, true); //Honor Points
					creature->MonsterWhisper("|c00077766|r Intercambiaste 4000 puntos de honor por 4000 puntos de justicia exitosamente.!", player->GetGUID(), true);
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					creature->MonsterWhisper("|c00077766|r No tienes suficientes puntos de honor!", player->GetGUID(), true);
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
				me->MonsterSay("¡Cambia tu honor aqui.!", LANG_UNIVERSAL, NULL);
				me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
				me->CastSpell(me, 44940);
				uiAdATimer = 61000;
			}
			else
				uiAdATimer -= diff;

			if (uiAdBTimer <= diff)
			{
				me->MonsterSay("Te sobra honor acercate para ver las opciones que destyne tiene para ti.!", LANG_UNIVERSAL, NULL);
				me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
				uiAdBTimer = 61000;
			}
			else
				uiAdBTimer -= diff;

			if (uiAdCTimer <= diff)
			{
				me->MonsterSay("Cambia tu honor por oro.!", LANG_UNIVERSAL, NULL);
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
 
void AddSC_Exchanger_NPC2()
{
    new Exchanger_NPC2();
}