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
 
class Morph2_npc : public CreatureScript
{
public:
    Morph2_npc() : CreatureScript("Morph2_npc") { }
 
 
    bool OnGossipHello(Player* player, Creature* creature)
    {
                if (player->isInCombat())
                {
                                        player->GetSession()->SendNotification("Estas en Combate!");
                                        player->CLOSE_GOSSIP_MENU();
                                        return false;
                }
 
								/*player->ADD_GOSSIP_ITEM(6, "Broken", GOSSIP_SENDER_MAIN, 1);
                                player->ADD_GOSSIP_ITEM(6, "Fel Orc", GOSSIP_SENDER_MAIN, 2);
                                player->ADD_GOSSIP_ITEM(6, "Goblin", GOSSIP_SENDER_MAIN, 3);
                                player->ADD_GOSSIP_ITEM(6, "Pandaren", GOSSIP_SENDER_MAIN, 4);
                                player->ADD_GOSSIP_ITEM(6, "Worgen", GOSSIP_SENDER_MAIN, 5);
								player->ADD_GOSSIP_ITEM(6, "Worgen 1", GOSSIP_SENDER_MAIN, 6);
								player->ADD_GOSSIP_ITEM(6, "Velen The Prophet", GOSSIP_SENDER_MAIN, 7);
								player->ADD_GOSSIP_ITEM(6, "Illidan", GOSSIP_SENDER_MAIN, 8);
								player->ADD_GOSSIP_ITEM(6, "Exanime", GOSSIP_SENDER_MAIN, 9);
								player->ADD_GOSSIP_ITEM(6, "Felguar", GOSSIP_SENDER_MAIN, 10);
								player->ADD_GOSSIP_ITEM(6, "Elemental de Sangre", GOSSIP_SENDER_MAIN, 11);
								player->ADD_GOSSIP_ITEM(6, "Tigerman", GOSSIP_SENDER_MAIN, 12);
								player->ADD_GOSSIP_ITEM(6, "Babosa de Cloaca", GOSSIP_SENDER_MAIN, 13);
								player->ADD_GOSSIP_ITEM(6, "Sucubo", GOSSIP_SENDER_MAIN, 14);
								player->ADD_GOSSIP_ITEM(6, "Necrofago", GOSSIP_SENDER_MAIN, 15);
								player->ADD_GOSSIP_ITEM(6, "Fantasma", GOSSIP_SENDER_MAIN, 16);
								player->ADD_GOSSIP_ITEM(6, "Fantasma 1", GOSSIP_SENDER_MAIN, 17);
								player->ADD_GOSSIP_ITEM(6, "Undead Male", GOSSIP_SENDER_MAIN, 18);
								player->ADD_GOSSIP_ITEM(6, "Undead Female", GOSSIP_SENDER_MAIN, 19);
								player->ADD_GOSSIP_ITEM(6, "Troll Female", GOSSIP_SENDER_MAIN, 20);*/
								player->ADD_GOSSIP_ITEM(6, "Troll Male", GOSSIP_SENDER_MAIN, 21);
								player->ADD_GOSSIP_ITEM(6, "Orc Female", GOSSIP_SENDER_MAIN, 22);
								player->ADD_GOSSIP_ITEM(6, "Orc Male", GOSSIP_SENDER_MAIN, 23);
								player->ADD_GOSSIP_ITEM(6, "Tauren Male", GOSSIP_SENDER_MAIN, 24);
								player->ADD_GOSSIP_ITEM(6, "Tauren Female", GOSSIP_SENDER_MAIN, 25);
								player->ADD_GOSSIP_ITEM(6, "Night Elf Female", GOSSIP_SENDER_MAIN, 26);
								player->ADD_GOSSIP_ITEM(6, "Night Elf male", GOSSIP_SENDER_MAIN, 27);
								player->ADD_GOSSIP_ITEM(6, "Gnome Female", GOSSIP_SENDER_MAIN, 28);
								player->ADD_GOSSIP_ITEM(6, "Gnome Male", GOSSIP_SENDER_MAIN, 29);
								player->ADD_GOSSIP_ITEM(6, "Dwarf Male", GOSSIP_SENDER_MAIN, 30);
								player->ADD_GOSSIP_ITEM(6, "Dwarf Female", GOSSIP_SENDER_MAIN, 31);
								player->ADD_GOSSIP_ITEM(6, "Goblin Female", GOSSIP_SENDER_MAIN, 32);
								player->ADD_GOSSIP_ITEM(6, "Goblin Male", GOSSIP_SENDER_MAIN, 33);
								player->ADD_GOSSIP_ITEM(6, "Blood Elf Female", GOSSIP_SENDER_MAIN, 34);
								player->ADD_GOSSIP_ITEM(6, "Blood Elf Male", GOSSIP_SENDER_MAIN, 35);
								player->ADD_GOSSIP_ITEM(6, "Human Female", GOSSIP_SENDER_MAIN, 36);
								player->ADD_GOSSIP_ITEM(6, "Human Male", GOSSIP_SENDER_MAIN, 37);
								player->ADD_GOSSIP_ITEM(6, "Thrall", GOSSIP_SENDER_MAIN, 38);
								player->ADD_GOSSIP_ITEM(6, "Lady Silvanas", GOSSIP_SENDER_MAIN, 39);
								player->ADD_GOSSIP_ITEM(6, "Caime Bloodhoor", GOSSIP_SENDER_MAIN, 40);
								/*player->ADD_GOSSIP_ITEM(6, "Lorthemar Theron", GOSSIP_SENDER_MAIN, 41);
								player->ADD_GOSSIP_ITEM(6, "King Magni Bronzebeard", GOSSIP_SENDER_MAIN, 42);
								player->ADD_GOSSIP_ITEM(6, "Highlord Bolvar Fordragon", GOSSIP_SENDER_MAIN, 43);
								player->ADD_GOSSIP_ITEM(6, "High Tinker Mekkatorque", GOSSIP_SENDER_MAIN, 44);
								player->ADD_GOSSIP_ITEM(6, "Tyrande Whisperwind", GOSSIP_SENDER_MAIN, 45);
								player->ADD_GOSSIP_ITEM(6, "Dragon", GOSSIP_SENDER_MAIN, 46);
								player->ADD_GOSSIP_ITEM(6, "Vine golem ", GOSSIP_SENDER_MAIN, 47);
								player->ADD_GOSSIP_ITEM(6, "stone guardian  ", GOSSIP_SENDER_MAIN, 48);
								player->ADD_GOSSIP_ITEM(6, "Sea giant  ", GOSSIP_SENDER_MAIN, 49);
								player->ADD_GOSSIP_ITEM(6, "mountain giant  ", GOSSIP_SENDER_MAIN, 50);
								player->ADD_GOSSIP_ITEM(6, "Tree giant, dark green ", GOSSIP_SENDER_MAIN, 51);
								player->ADD_GOSSIP_ITEM(6, "tree giant", GOSSIP_SENDER_MAIN, 52);
								player->ADD_GOSSIP_ITEM(6, "Green stone giant ", GOSSIP_SENDER_MAIN, 53);
								player->ADD_GOSSIP_ITEM(6, "Red infernal ", GOSSIP_SENDER_MAIN, 54);
								player->ADD_GOSSIP_ITEM(6, "green infernal ", GOSSIP_SENDER_MAIN, 55);
								player->ADD_GOSSIP_ITEM(6, "Gronn", GOSSIP_SENDER_MAIN, 56);
								player->ADD_GOSSIP_ITEM(6, "Arcane golem", GOSSIP_SENDER_MAIN, 57);
								player->ADD_GOSSIP_ITEM(6, "purple Harvest golem ", GOSSIP_SENDER_MAIN, 58);
								player->ADD_GOSSIP_ITEM(6, "treeguy  ", GOSSIP_SENDER_MAIN, 59);
								player->ADD_GOSSIP_ITEM(6, "Blue naaru  ", GOSSIP_SENDER_MAIN, 60);*/
                                player->ADD_GOSSIP_ITEM(6, "Eliminar Transformacion", GOSSIP_SENDER_MAIN, 61);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                return true;
        }
       
        bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 action)
        {
 
                switch (action)
        {
            case 1:
                player->CLOSE_GOSSIP_MENU();
                player->SetDisplayId(21105);
                break;
            case 2:
                player->CLOSE_GOSSIP_MENU();
                player->SetDisplayId(21267);
                break;
            case 3:
                player->CLOSE_GOSSIP_MENU();
                player->SetDisplayId(20582);
                break;
            case 4:
                player->CLOSE_GOSSIP_MENU();
                player->SetDisplayId(30414);
                break;
            case 5:
                player->CLOSE_GOSSIP_MENU();
                player->SetDisplayId(26788);
                break;
			case 6:
                player->CLOSE_GOSSIP_MENU();
                player->SetDisplayId(657);
                break;
			case 7:
                player->CLOSE_GOSSIP_MENU();
                player->SetDisplayId(17822);
                break;
			case 8:
                player->CLOSE_GOSSIP_MENU();
                player->SetDisplayId(21137);
                break;
			case 9:
                player->CLOSE_GOSSIP_MENU();
                player->SetDisplayId(24191);
                break;
			case 10:
                player->CLOSE_GOSSIP_MENU();
                player->SetDisplayId(5048);
                break;
			case 11:
                player->CLOSE_GOSSIP_MENU();
                player->SetDisplayId(20030);
                break;
			case 12:
                player->CLOSE_GOSSIP_MENU();
                player->SetDisplayId(15214);
                break;
			case 13:
                player->CLOSE_GOSSIP_MENU();
                player->SetDisplayId(12349);
                break;
			case 14:
                player->CLOSE_GOSSIP_MENU();
                player->SetDisplayId(4162);
                break;
			case 15:
                player->CLOSE_GOSSIP_MENU();
                player->SetDisplayId(414);
                break;
			case 16:
                player->CLOSE_GOSSIP_MENU();
                player->SetDisplayId(16162);
                break;
			case 17:
                player->CLOSE_GOSSIP_MENU();
                player->SetDisplayId(16168);
                break;
			case 18:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(3533);
				break;
			case 19:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(3529);

			case 20:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(4358);
				break;
			case 21:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(11193);
				break;
			case 22:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(20942);
				break;
			case 23:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(17749);
				break;
			case 24:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(5486);
				break;
			case 25:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(3000);
				break; 
			case 26:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(2222);
				break;
			case 27:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(2245);
				break;
			case 28:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(7000);
				break;
			case 29:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(7004);
				break;
			case 30:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(7001);
				break;
			case 31:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(5737);
				break;
			case 32:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(19161);
				break;
			case 33:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(19000);
				break;
			case 34:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(19169);
				break;
			case 35:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(21881);
				break;
			case 36:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(15834);
				break;
			case 37:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(15833);
				break;
			case 38:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(4527);
				break;
			case 39:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(11657);
				break;
			case 40:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(4307);
				break;
			case 41:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(17122);
				break;
			case 42:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(3597);
				break;
			case 43:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(5566);
				break;
			case 44:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(7006);
				break;
			case 45:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(7274);
				break;
			case 46:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(17093);
				break;
			case 47:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(9009);
				break;
			case 48:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(975);
				break;
			case 49:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(6751);
				break;
			case 50:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(1918);
				break;
			case 51:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(20249);
				break;
			case 52:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(20249);
				break;
			case 53:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(20261);
				break;
			case 54:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(20282);
				break;
			case 55:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(20324);
				break;
			case 56:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(20346);
				break;
			case 57:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(19971);
				break;
			case 58:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(514);
				break;
			case 59:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(860);
				break;
			case 60:
				player->CLOSE_GOSSIP_MENU();
				player->SetDisplayId(20306);
				break;
            case 61:
                player->CLOSE_GOSSIP_MENU();
                player->DeMorph();
                break;
                }
                return true;
        }
};
 
void AddSC_Morph2_npc()
{
        new Morph2_npc();
}