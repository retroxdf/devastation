#include "ScriptPCH.h"
#include "Language.h"
 
// not used atm
enum ProfMenus
{
    MAIN_MENU = 0,
    ALCHEMY = 1,
    BLACKSMITHING = 2,
    LEATHERWROKING = 3,
    TAILORING = 4,
    ENGINEERING = 5,
    ENCHANTING = 6,
    JEWELCRAFTING = 7,
    INSCRIPTION = 8,
    FIRST_AID = 9
};
 
bool PlayerAlreadyHasTwoProfessions(const Player *player) /*const*/
{
    uint32 skillCount = 0;
	uint32 accountID = player->GetSession()->GetAccountId();
	QueryResult result = CharacterDatabase.PQuery("SELECT COUNT(`guid`) FROM `characters` WHERE `account`=%u", accountID);
	Field *fields = result->Fetch();
	uint32 personajes = fields[0].GetUInt32();
 
    if (player->HasSkill(SKILL_MINING))
        skillCount++;
    if (player->HasSkill(SKILL_SKINNING))
        skillCount++;
    if (player->HasSkill(SKILL_HERBALISM))
        skillCount++;
 
    if (skillCount >= 1)
        return true;
 
    for (uint32 i = 1; i < sSkillLineStore.GetNumRows(); ++i)
    {
        SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(i);
        if (!SkillInfo)
            continue;
 
        if (SkillInfo->categoryId == SKILL_CATEGORY_SECONDARY)
            continue;
 
        if ((SkillInfo->categoryId != SKILL_CATEGORY_PROFESSION) || !SkillInfo->canLink)
            continue;
 
        const uint32 skillID = SkillInfo->id;
        if (player->HasSkill(skillID))
            skillCount++;
 
        if (skillCount >= 2)
            return true;

	   if (player->getLevel() <= 84)
		{
		   return true;

		}

    }
    return false;
}
 
 
void LearnSkillRecipesHelper(Player *player, uint32 skill_id)
{
    uint32 classmask = player->getClassMask();
 
    for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
    {
        SkillLineAbilityEntry const *skillLine = sSkillLineAbilityStore.LookupEntry(j);
        if (!skillLine)
            continue;
 
        // wrong skill
        if (skillLine->skillId != skill_id)
            continue;
 
        // not high rank
        if (skillLine->forward_spellid)
            continue;
 
        // skip racial skills
        if (skillLine->racemask != 0)
            continue;
 
        // skip wrong class skills
        if (skillLine->classmask && (skillLine->classmask & classmask) == 0)
            continue;
 
        SpellEntry const* spellInfo = sSpellStore.LookupEntry(skillLine->spellId);
        player->learnSpell(skillLine->spellId, false);
    }
}
 
bool LearnAllRecipesInProfession(Player *player, SkillType skill)
{
    ChatHandler handler(player->GetSession());
 
    SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(skill);
 
    std::string skill_name = SkillInfo->name;
    if (!SkillInfo)
        return false;
 
    LearnSkillRecipesHelper(player, SkillInfo->id);
    player->SetSkill(SkillInfo->id, player->GetSkillStep(SkillInfo->id), 525, 525);
    if (skill_name.empty())
        return false;
 
    handler.PSendSysMessage(LANG_COMMAND_LEARN_ALL_RECIPES, skill_name.c_str());
    return true;
}
 
bool IsSecondarySkill(SkillType skill) /* const */
{
    return skill == SKILL_COOKING || skill == SKILL_FIRST_AID || skill == SKILL_FISHING || skill == SKILL_ARCHAEOLOGY;
}
 
void CompleteLearnProfession(Player *pPlayer, SkillType skill)
{
    if (PlayerAlreadyHasTwoProfessions(pPlayer) && !IsSecondarySkill(skill))
        pPlayer->GetSession()->SendNotification("Lo siento pero no eres nivel 85 o ya tienes 2 profesion primaria!");
    else
    {
        if (!LearnAllRecipesInProfession(pPlayer, skill))
            pPlayer->GetSession()->SendNotification("Error #1: Internal code failiure");
    }
}
 
class Professions_NPC : public CreatureScript
{
public: Professions_NPC() : CreatureScript("Professions_NPC") {}
 
        bool OnGossipHello(Player* player, Creature* creature)
        {
            // Primary
            if (!player->HasSkill(SKILL_ALCHEMY))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Trade_Alchemy:30|t Alquimia|r", GOSSIP_SENDER_MAIN, 1);
            if (!player->HasSkill(SKILL_BLACKSMITHING))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Trade_BlackSmithing:30|t Herreria|r", GOSSIP_SENDER_MAIN, 2);
            if (!player->HasSkill(SKILL_LEATHERWORKING))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/INV_Misc_ArmorKit_17:30|t Peletero|r", GOSSIP_SENDER_MAIN, 3);
            if (!player->HasSkill(SKILL_TAILORING))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Trade_Tailoring:30|t Sastre|r", GOSSIP_SENDER_MAIN, 4);
            if (!player->HasSkill(SKILL_ENGINEERING))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Trade_Engineering:30|t Ingeniero|r", GOSSIP_SENDER_MAIN, 5);
            if (!player->HasSkill(SKILL_ENCHANTING))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Trade_Engraving:30|t Encantamiento|r", GOSSIP_SENDER_MAIN, 6);
            if (!player->HasSkill(SKILL_JEWELCRAFTING))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/INV_Misc_Gem_01:30|t Joyero|r", GOSSIP_SENDER_MAIN, 7);
            if (!player->HasSkill(SKILL_INSCRIPTION))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/INV_Inscription_Tradeskill01:30|t Inscripcion|r", GOSSIP_SENDER_MAIN, 8);
            if (!player->HasSkill(SKILL_HERBALISM))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Spell_Nature_NatureTouchGrow:30|t Herbosteria|r", GOSSIP_SENDER_MAIN, 19);
            if (!player->HasSkill(SKILL_MINING))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Trade_Mining:30|t Minero|r", GOSSIP_SENDER_MAIN, 20);
            if (!player->HasSkill(SKILL_SKINNING))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/INV_Misc_Pelt_Wolf_01:30|t Desuello|r", GOSSIP_SENDER_MAIN, 21);
            player->PlayerTalkClass->SendGossipMenu(907, creature->GetGUID());
            return true;
        }
 
        bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
        {
            player->PlayerTalkClass->ClearMenus();
 
            if (uiSender == GOSSIP_SENDER_MAIN)
            {
                switch (uiAction)
                {
                case 0:
                    OnGossipHello(player, creature);
                    break;
 
                case 1: CompleteLearnProfession(player, SKILL_ALCHEMY); break;
                case 2: CompleteLearnProfession(player, SKILL_BLACKSMITHING); break;
                case 3: CompleteLearnProfession(player, SKILL_LEATHERWORKING); break;
                case 4: CompleteLearnProfession(player, SKILL_TAILORING); break;
                case 5: CompleteLearnProfession(player, SKILL_ENGINEERING); break;
                case 6: CompleteLearnProfession(player, SKILL_ENCHANTING); break;
                case 7: CompleteLearnProfession(player, SKILL_JEWELCRAFTING); break;
                case 8: CompleteLearnProfession(player, SKILL_INSCRIPTION); break;
                case 15: CompleteLearnProfession(player, SKILL_FIRST_AID); break;
                case 16: CompleteLearnProfession(player, SKILL_FISHING); break;
                case 17: CompleteLearnProfession(player, SKILL_COOKING); break;
                case 18: CompleteLearnProfession(player, SKILL_ARCHAEOLOGY); break;
                case 19: CompleteLearnProfession(player, SKILL_HERBALISM); break;
                case 20: CompleteLearnProfession(player, SKILL_MINING); break;
                case 21: CompleteLearnProfession(player, SKILL_SKINNING); break;
                }
            }



            player->CLOSE_GOSSIP_MENU();
            return true;
        }
};
 
void AddSC_Professions_NPC()
{
    new Professions_NPC();
}