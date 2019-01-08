# Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

file(GLOB_RECURSE scripts_Custom Custom/*.cpp Custom/*.h)
source_group(Custom FILES ${scripts_Custom})

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  ${scripts_Custom}
  Custom/Skirmish_npc.cpp
  Custom/soloqueue_npc.cpp
  Custom/CdReset.cpp
  Custom/Npc_Beastmaster.cpp
  Custom/Professions_NPC.cpp
  Custom/Exchanger_NPC.cpp
  Custom/Exchanger_NPC2.cpp
  Custom/npc_blood_money.cpp
  Custom/World_chat.cpp
  Custom/npc_changer.cpp
  Custom/boss_darksaw.cpp

  Custom/Gossip_CheckCombat.cpp
  Custom/arena_top_teams.cpp

  Custom/vanilla_title_npc.cpp

  Custom/chat_censure.cpp


  Custom/npc_teleporter.cpp

  Custom/npc_promo.cpp
  Custom/npc_incansable_km.cpp
  Custom/killstreak.cpp
  Custom/npc_pve_km.cpp
  Custom/Trainer.cpp
  Custom/VisualWeapon.cpp
  Custom/top_class_killers.cpp
  Custom/tokenconverter.cpp
  Custom/npc_top10_arena.cpp
  Custom/npc_enchant.cpp
  Custom/gurubashi_theme.cpp
  Custom/clear_combat_bug.cpp

  Custom/login_announce.cpp
  Custom/casino_1.cpp
  Custom/casino_2.cpp
  Custom/simple_pvp_title_system.cpp
  Custom/Npcmorph.cpp
  Custom/Npcmorph2.cpp
  Custom/Npcmorph3.cpp
  
  Custom/npc_goku.cpp
  Custom/TeLe_gossip_codebox.cpp



 
)

message("  -> Prepared: Custom")
