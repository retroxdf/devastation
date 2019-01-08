#include "ScriptPCH.h"
 
// Set USE_TOKEN to 1 if you want to have it use tokens in place of gold
#define USE_TOKEN       0
#define TOKEN_ID        29434
 
struct BloodMoneyInfo
{
        uint64 guid;
        uint32 amount;
        bool accepted;
};
 
typedef std::list<BloodMoneyInfo> BloodMoneyList;
typedef std::map<uint64, BloodMoneyList> BloodMoney;
static BloodMoney m_bloodMoney;
 
bool HasBloodMoneyChallenger(uint64 playerGUID)
{
        return m_bloodMoney.find(playerGUID) != m_bloodMoney.end();
}
 
bool HasBloodMoneyChallenger(uint64 targetGUID, uint64 playerGUID)
{
        if (!HasBloodMoneyChallenger(targetGUID))
                return false;
        BloodMoneyList bml = m_bloodMoney[targetGUID];
        for (BloodMoneyList::const_iterator itr = bml.begin(); itr != bml.end(); ++itr)
                if (itr->guid == playerGUID)
                        return true;
        return false;
}
 
void AddBloodMoneyEntry(uint64 targetGUID, uint64 playerGUID, uint32 amount)
{
        BloodMoneyInfo bmi;
        bmi.guid = playerGUID;
        bmi.amount = amount;
        bmi.accepted = false;
        m_bloodMoney[targetGUID].push_back(bmi);
}
 
void RemoveBloodMoneyEntry(uint64 targetGUID, uint64 playerGUID)
{
        if (!HasBloodMoneyChallenger(targetGUID, playerGUID))
                return;
        BloodMoneyList &list = m_bloodMoney[targetGUID];
        BloodMoneyList::iterator itr;
        for (itr = list.begin(); itr != list.end(); ++itr)
                if (itr->guid == playerGUID)
                        break;
        list.erase(itr);
}
 
void SetChallengeAccepted(uint64 targetGUID, uint64 playerGUID)
{
        if (!HasBloodMoneyChallenger(targetGUID, playerGUID))
                return;
        BloodMoneyList &list = m_bloodMoney[targetGUID];
        BloodMoneyList::iterator itr;
        for (itr = list.begin(); itr != list.end(); ++itr)
        {
                if (itr->guid == playerGUID)
                {
                        itr->accepted = true;
                        break;
                }
        }
}
 
class npc_blood_money : public CreatureScript
{
        public :
                npc_blood_money() : CreatureScript("npc_blood_money") {}
 
        bool OnGossipHello(Player * player, Creature * creature)
        {
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Selecciona un jugador", 11, 1000);   
                if (HasBloodMoneyChallenger(player->GetGUID()))
                {
                        BloodMoneyList list = m_bloodMoney[player->GetGUID()];
                        for (BloodMoneyList::const_iterator itr = list.begin(); itr != list.end(); ++itr)
                        {
                                char msg[50];
 
                                if (Player* plr = Player::GetPlayer(*player, itr->guid))
                                {
                                        if (USE_TOKEN)
                                        {
                                                sprintf(msg, "Accept %s's Challenge of %u tokens", plr->GetName().c_str(), itr->amount);
                                                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, msg, GOSSIP_SENDER_MAIN, itr->guid);
                                                sprintf(msg, "Decline %s's Challenge of %u tokens", plr->GetName().c_str(), itr->amount);
                                                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, msg, GOSSIP_SENDER_INFO, itr->guid);
                                        }
                                        else
                                        {
                                                sprintf(msg, "Aceptar %s's duelo de %ug", plr->GetName().c_str(), itr->amount/10000);
                                                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, msg, GOSSIP_SENDER_MAIN, itr->guid);
                                                sprintf(msg, "Rechazar %s's duelo de %ug", plr->GetName().c_str(), itr->amount/10000);
                                                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, msg, GOSSIP_SENDER_INFO, itr->guid);
                                        }
                                       
                                }
                        }
                }
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Al poner el jugador no des ENTER dale click en ACEPTAR", GOSSIP_SENDER_MAIN, 1);
               
                player->SEND_GOSSIP_MENU(80025, creature->GetGUID());
 
                return true;
        }
 
        bool OnGossipSelect(Player * player, Creature * creature, uint32 uiSender, uint32 uiAction)
        {
                player->PlayerTalkClass->ClearMenus();
                if (uiAction == 1)
                {
                        player->CLOSE_GOSSIP_MENU();
                        return true;
                }
                switch(uiSender)
                {
                        case GOSSIP_SENDER_MAIN:
                                if (Player* target = Player::GetPlayer(*player, uiAction))
                                {
                                        SetChallengeAccepted(player->GetGUID(), target->GetGUID());
                                        char msg[60];
                                        sprintf(msg, "%s has aceptado el duelo!", player->GetName().c_str());
                                        creature->MonsterWhisper(msg, target->GetGUID(), true);
                                        player->CLOSE_GOSSIP_MENU();
                                }
                                break;
                        case GOSSIP_SENDER_INFO:
                                if (Player* target = Player::GetPlayer(*player, uiAction))
                                {
                                        char msg[60];
                                        sprintf(msg, "%s has rechazado el duelo!", player->GetName().c_str());
                                        creature->MonsterWhisper(msg, target->GetGUID(), true);
                                        RemoveBloodMoneyEntry(player->GetGUID(), uiAction);
                                        OnGossipHello(player, creature);
                                }
                                break;
                        case 11:
                                if (USE_TOKEN)
                                {
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 5 tokens", GOSSIP_SENDER_MAIN, 5, "", 0, true);
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 10 tokens", GOSSIP_SENDER_MAIN, 10, "", 0, true);
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 15 tokens", GOSSIP_SENDER_MAIN, 15, "", 0, true);
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 25 tokens", GOSSIP_SENDER_MAIN, 25, "", 0, true);
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 50 tokens", GOSSIP_SENDER_MAIN, 50, "", 0, true);
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 100 tokens", GOSSIP_SENDER_MAIN, 100, "", 0, true);
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 150 tokens", GOSSIP_SENDER_MAIN, 150, "", 0, true);
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 200 tokens", GOSSIP_SENDER_MAIN, 200, "", 0, true);
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 250 tokens", GOSSIP_SENDER_MAIN, 250, "", 0, true);
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 500 tokens", GOSSIP_SENDER_MAIN, 500, "", 0, true);
                                }
                                else
                                {
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Apostar 5g", GOSSIP_SENDER_MAIN, 5, "", 0, true);
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Apostar 10g", GOSSIP_SENDER_MAIN, 10, "", 0, true);
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Apostar 15g", GOSSIP_SENDER_MAIN, 15, "", 0, true);
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Apostar 25g", GOSSIP_SENDER_MAIN, 25, "", 0, true);
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Apostar 50g", GOSSIP_SENDER_MAIN, 50, "", 0, true);
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Apostar 100g", GOSSIP_SENDER_MAIN, 100, "", 0, true);
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Apostar 150g", GOSSIP_SENDER_MAIN, 150, "", 0, true);
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Apostar 200g", GOSSIP_SENDER_MAIN, 200, "", 0, true);
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Apostar 250g", GOSSIP_SENDER_MAIN, 250, "", 0, true);
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Apostar 500g", GOSSIP_SENDER_MAIN, 500, "", 0, true);
                                }
                               
                                player->SEND_GOSSIP_MENU(80025, creature->GetGUID());
                                break;
                }
                return true;
        }
 
        bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code)
        {
                if (player->GetName().c_str() == code)
                {
                        ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFAhora por qué querrías desafiarte a ti mismo?");
                        return false;
                }
                if (uint64 targetGUID = sObjectMgr->GetPlayerGUIDByName(code))
                {
                        if (Player* target = Player::GetPlayer(*player, targetGUID))
                        {
                                if (target->GetGUID() == player->GetGUID())
                                {
                                        ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFAhora por qué querrías desafiarte a ti mismo?");
                                        return false;
                                }
                                if (target->GetZoneId() == player->GetZoneId())
                                {
                                        if (USE_TOKEN)
                                        {
                                                if (target->GetItemCount(TOKEN_ID) < action)
                                                {
                                                        ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFEse jugador no tiene suficientes fichas para hacer la apuesta.!");
                                                        player->CLOSE_GOSSIP_MENU();
                                                        return false;
                                                }
                                                if (player->GetItemCount(TOKEN_ID) < action)
                                                {
                                                        ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFNo tienes suficientes tokens para hacer la apuesta.!");
                                                        player->CLOSE_GOSSIP_MENU();
                                                        return false;
                                                }
                                               
                                                bool found = false;
                                                if (HasBloodMoneyChallenger(player->GetGUID()))
                                                {
                                                        BloodMoneyList list = m_bloodMoney[player->GetGUID()];
                                                        for (BloodMoneyList::const_iterator itr = list.begin(); itr != list.end(); ++itr)
                                                                if (itr->guid == target->GetGUID())
                                                                        found = true;
                                                }
                                                if (!found)
                                                {
                                                        if (!HasBloodMoneyChallenger(target->GetGUID(), player->GetGUID()))
                                                        {
                                                                AddBloodMoneyEntry(target->GetGUID(), player->GetGUID(), action);
                                                                char msg[60];
                                                                sprintf(msg, "%s ha solicitado un duelo de dinero por sangre contigo!", player->GetName().c_str());
                                                                creature->MonsterWhisper(msg, target->GetGUID(), true);
                                                        }
                                                        else
                                                                ChatHandler(target->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFNo puedes solicitar un duelo con la misma persona.!");
                                                }
                                                else
                                                        ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFNo puedes solicitar un duelo con alguien que te haya desafiado.!");
                                                player->CLOSE_GOSSIP_MENU();
                                                return true;
                                        }
                                        else
                                        {
                                                uint32 money = action*10000;
                                                if (target->GetMoney() < money)
                                                {
                                                        ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFEse jugador no tiene suficiente dinero para hacer la apuesta.!");
                                                        player->CLOSE_GOSSIP_MENU();
                                                        return false;
                                                }
                                                if (player->GetMoney() < money)
                                                {
                                                        ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFNo tienes suficiente dinero para hacer la apuesta.!");
                                                        player->CLOSE_GOSSIP_MENU();
                                                        return false;
                                                }
 
                                                bool found = false;
                                                if (HasBloodMoneyChallenger(player->GetGUID()))
                                                {
                                                        BloodMoneyList list = m_bloodMoney[player->GetGUID()];
                                                        for (BloodMoneyList::const_iterator itr = list.begin(); itr != list.end(); ++itr)
                                                                if (itr->guid == target->GetGUID())
                                                                        found = true;
                                                }
                                                if (!found)
                                                {
                                                        if (!HasBloodMoneyChallenger(target->GetGUID(), player->GetGUID()))
                                                        {
                                                                AddBloodMoneyEntry(target->GetGUID(), player->GetGUID(), money);
                                                                char msg[60];
                                                                sprintf(msg, "%s ha solicitado un duelo de sangre por dinero contigo!", player->GetName().c_str());
                                                                creature->MonsterWhisper(msg, target->GetGUID(), true);
                                                        }
                                                        else
                                                                ChatHandler(target->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFYou cannot request a duel with the same person!");
                                                }
                                                else
                                                        ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFNo puedes solicitar un duelo con alguien que te haya desafiado.!");
                                                player->CLOSE_GOSSIP_MENU();
                                                return true;
                                        }
                                       
                                }
                                else
                                {
                                        ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFEse jugador no está en tu zona.!");
                                        player->CLOSE_GOSSIP_MENU();
                                        return false;
                                }
                        }
                        else
                        {
                                ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFEse jugador no fue encontrado!");
                                player->CLOSE_GOSSIP_MENU();
                                return false;
                        }
                }
                else
                {
                        ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFEse jugador no fue encontrado!");
                        player->CLOSE_GOSSIP_MENU();
                        return false;
                }
                player->CLOSE_GOSSIP_MENU();
                return true;
        }
 
};
 
class BloodMoneyReward : public PlayerScript
{
 public:
         BloodMoneyReward() : PlayerScript("BloodMoneyReward") {}
         
        void OnDuelEnd(Player* winner, Player* loser, DuelCompleteType type)
        {
                if (type != DUEL_WON)
                        return;
                if (HasBloodMoneyChallenger(winner->GetGUID()) || HasBloodMoneyChallenger(loser->GetGUID()))
                {                        
                        BloodMoneyList list1 = m_bloodMoney[winner->GetGUID()];
                        BloodMoneyList list2 = m_bloodMoney[loser->GetGUID()];
 
                        BloodMoneyList::const_iterator itr;
                        for (itr = list1.begin(); itr != list1.end(); ++itr)
                        {
                                if (itr->guid == loser->GetGUID() && itr->accepted)
                                {
                                        if (USE_TOKEN)
                                        {
                                                if (winner->GetItemCount(TOKEN_ID) < itr->amount)
                                                {
                                                        winner->AddAura(15007, winner);         // Apply Rez sickness for possible cheating
                                                        ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFHas ganado Resurrection Sickness por intentar abusar del sistema.");
                                                        ChatHandler(loser->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFTu oponente trató de engañarte. No te preocupes, no perdiste ninguna ficha por esto.");
                                                        RemoveBloodMoneyEntry(winner->GetGUID(), itr->guid);
                                                        return;
                                                }
                                                if (loser->GetItemCount(TOKEN_ID) >= itr->amount)
                                                {
                                                        winner->AddItem(TOKEN_ID, itr->amount);
                                                        ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFFelicitaciones por ganar %u tokens!", itr->amount);
                                                        Item* item = loser->GetItemByEntry(TOKEN_ID);
                                                        loser->DestroyItemCount(TOKEN_ID, itr->amount, true);
                                                        RemoveBloodMoneyEntry(winner->GetGUID(), itr->guid);
                                                }
                                                else
                                                {
                                                        loser->AddAura(15007, loser);           // Apply Rez sickness for possible cheating
                                                        ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFTu oponente trató de engañarte. No tenía suficientes fichas para pagar la apuesta..");
                                                        ChatHandler(loser->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFHas ganado Resurrection Sickness por intentar abusar del sistema..");
                                                        RemoveBloodMoneyEntry(winner->GetGUID(), itr->guid);
                                                }
                                                return;
                                        }
                                        else
                                        {
                                                if (winner->GetMoney() < itr->amount)
                                                {
                                                        winner->AddAura(15007, winner);         // Apply Rez sickness for possible cheating
                                                        ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFHas ganado Resurrection Sickness por intentar abusar del sistema..");
                                                        ChatHandler(loser->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFYour El oponente trató de engañarte. No te preocupes no perdiste dinero por esto..");
                                                        RemoveBloodMoneyEntry(winner->GetGUID(), itr->guid);
                                                        return;
                                                }
                                                if (loser->GetMoney() >= itr->amount)
                                                {
                                                        winner->ModifyMoney(itr->amount);
                                                        ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFFelicitaciones por ganar %ug!", itr->amount/10000);
                                                        loser->ModifyMoney(-(int32)(itr->amount));
                                                        RemoveBloodMoneyEntry(winner->GetGUID(), itr->guid);
                                                }
                                                else
                                                {
                                                        loser->AddAura(15007, loser);           // Apply Rez sickness for possible cheating
                                                        ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFTu oponente trató de engañarte. No tenía dinero suficiente para pagar la apuesta.");
                                                        ChatHandler(loser->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFHas ganado Resurrection Sickness por intentar abusar del sistema.");
                                                        RemoveBloodMoneyEntry(winner->GetGUID(), itr->guid);
                                                }
                                                return;
                                        }
                                }
                        }
                        for (itr = list2.begin(); itr != list2.end(); ++itr)
                        {
                                if (itr->guid == winner->GetGUID() && itr->accepted)
                                {
                                        if (USE_TOKEN)
                                        {
                                                if (winner->GetItemCount(TOKEN_ID) < itr->amount)
                                                {
                                                        winner->AddAura(15007, winner);         // Apply Rez sickness for possible cheating
                                                        ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFTu oponente trató de engañarte. No tenía dinero suficiente para pagar la apuesta.");
                                                        ChatHandler(loser->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFHas ganado Resurrection Sickness por intentar abusar del sistema.");
                                                        RemoveBloodMoneyEntry(loser->GetGUID(), itr->guid);
                                                        return;
                                                }
                                                if (loser->GetItemCount(TOKEN_ID) >= itr->amount)
                                                {
                                                        winner->AddItem(TOKEN_ID, itr->amount);
                                                        ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFFelicitaciones por ganar %u tokens!", itr->amount);
                                                        Item* item = loser->GetItemByEntry(TOKEN_ID);
                                                        loser->DestroyItemCount(TOKEN_ID, itr->amount, true);
                                                        RemoveBloodMoneyEntry(loser->GetGUID(), itr->guid);
                                                }
                                                else
                                                {
                                                        loser->AddAura(15007, loser);           // Apply Rez sickness for possible cheating
                                                        ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFTu oponente trató de engañarte. No tenía dinero suficiente para pagar la apuesta.");
                                                        ChatHandler(loser->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFHas ganado Resurrection Sickness por intentar abusar del sistema.");
                                                        RemoveBloodMoneyEntry(loser->GetGUID(), itr->guid);
                                                }
                                                return;
                                        }
                                        else
                                        {
                                                if (winner->GetMoney() < itr->amount)
                                                {
                                                        winner->AddAura(15007, winner);         // Apply Rez sickness for possible cheating
                                                        ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFTu oponente trató de engañarte. No tenía dinero suficiente para pagar la apuesta.");
                                                        ChatHandler(loser->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFHas ganado Resurrection Sickness por intentar abusar del sistema.");
                                                        RemoveBloodMoneyEntry(loser->GetGUID(), itr->guid);
                                                        return;
                                                }
                                                if (loser->GetMoney() >= itr->amount)
                                                {
                                                        winner->ModifyMoney(itr->amount);
                                                        ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFFelicitaciones por ganar %ug!", itr->amount/10000);
                                                        loser->ModifyMoney(-(int32)(itr->amount));
                                                        RemoveBloodMoneyEntry(loser->GetGUID(), itr->guid);
                                                }
                                                else
                                                {
                                                        loser->AddAura(15007, loser);           // Apply Rez sickness for possible cheating
                                                        ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFTu oponente trató de engañarte. No tenía dinero suficiente para pagar la apuesta.");
                                                        ChatHandler(loser->GetSession()).PSendSysMessage("|cff800C0C[Destyne] |cffFFFFFFHas ganado Resurrection Sickness por intentar abusar del sistema.");
                                                        RemoveBloodMoneyEntry(loser->GetGUID(), itr->guid);
                                                }
                                                return;
                                        }
                                }
                        }
 
                 }
         }


		 struct gambler_passivesAI : public ScriptedAI
		 {
			 gambler_passivesAI(Creature * c) : ScriptedAI(c){ }

			 uint32 uiAdATimer;
			 uint32 uiAdBTimer;
			 uint32 uiAdCTimer;

			 void Reset()
			 {
				 uiAdATimer = 2000;
				 uiAdBTimer = 46000;
				 uiAdCTimer = 22000;
			 }


			 void UpdateAI(const uint32 diff)
			 {

				 if (uiAdATimer <= diff)
				 {
					 me->MonsterSay("¡Ven demuestra tu destresa en los duelos.!", LANG_UNIVERSAL, NULL);
					 me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
					 me->CastSpell(me, 44940);
					 uiAdATimer = 121000;
				 }
				 else
					 uiAdATimer -= diff;

				 if (uiAdBTimer <= diff)
				 {
					 me->MonsterSay("Apestale a tu amigo un duelo.!", LANG_UNIVERSAL, NULL);
					 me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
					 uiAdBTimer = 121000;
				 }
				 else
					 uiAdBTimer -= diff;

				 if (uiAdCTimer <= diff)
				 {
					 me->MonsterSay("Sangre por dinero.!", LANG_UNIVERSAL, NULL);
					 me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
					 uiAdCTimer = 121000;
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
 
void AddSC_npc_blood_money()
{
        new BloodMoneyReward();
        new npc_blood_money();
}