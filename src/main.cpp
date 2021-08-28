#include "types.pb.h"
#include "small-kv/kv.hpp"

using namespace types;

int main()
{
    Hero mage;
    mage.set_name("mage-1");
    mage.set_hp(25);
    mage.set_xp(1024);
    mage.mutable_mage_info()->add_spellbook(Spell::FIREBALL);
    mage.mutable_mage_info()->add_spellbook(Spell::THUNDERBOLT);
    mage.mutable_mage_info()->set_mana(100);
    
    database::kv kv = database::kv();
    int8_t res = kv.set("heroes/mage[1]", mage, true);
    mage.set_hp(11);
    res = kv.set("heroes/mage[1]", mage);
    
    Hero mage_from_database;
    res = kv.get("heroes/mage[1]", mage_from_database);
    
    Hero warrior;
    warrior.set_name("warrior-1");
    warrior.set_hp(50);
    warrior.set_xp(256);
    warrior.mutable_warrior_info()->set_weapon(Weapon::SWORD);
    warrior.mutable_warrior_info()->set_arrows_number(15);
    
    res = kv.set("heroes/warrior[1]", warrior, true);
    
    Hero warrior_from_database;
    res = kv.get("heroes/warrior[1]", warrior_from_database);
    
    return 0;
}
