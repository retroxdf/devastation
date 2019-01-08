#include "ScriptPCH.h"

enum Spells
{
	SPELL_AMPLIFY_FLAMES = 30053,
	SPELL_BOILING_BLOOD = 50207,
	SPELL_FIREBALL_VOLLEY = 29958
};

class boss_forgotten_justicar : public CreatureScript
{
public:
	boss_forgotten_justicar() : CreatureScript("boss_forgotten_justicar"){}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_forgotten_justicarAI(creature);
	}

	struct boss_forgotten_justicarAI : public ScriptedAI
	{
		boss_forgotten_justicarAI(Creature* creature) : ScriptedAI(creature){}

		uint32 Amplify_flames_timer;
		uint32 Boiling_blood_timer;
		uint32 Fireball_volley_timer;

		void Reset()
		{
			Amplify_flames_timer = 30000;
			Boiling_blood_timer = 2000;
			Fireball_volley_timer = 10000;
		}

		void EnterCombat(Unit * who)
		{
			if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
				DoCast(target, SPELL_AMPLIFY_FLAMES);
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (Amplify_flames_timer <= diff)
			{
				DoCast(me->getVictim(), SPELL_AMPLIFY_FLAMES);

				Amplify_flames_timer = 30000;
			}
			else Amplify_flames_timer -= diff;

			if (Boiling_blood_timer <= diff)
			{
				DoCast(me->getVictim(), SPELL_BOILING_BLOOD);

				Boiling_blood_timer = 2000;
			}
			else Boiling_blood_timer -= diff;

			if (Fireball_volley_timer <= diff)
			{
				DoCast(me->getVictim(), SPELL_FIREBALL_VOLLEY);

				Fireball_volley_timer = 10000;
			}
			else Fireball_volley_timer -= diff;

			DoMeleeAttackIfReady();
		}
	};
};

void AddSC_boss_forgotten_justicar()
{
	new boss_forgotten_justicar();
}