#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"

namespace ksys::act {

bool getSystemIsGetItemSelf(InfoData* data, const char* actor) {
    return data->getBool(actor, "systemIsGetItemSelf");
}

bool getSystemIsGetItemSelf(const al::ByamlIter& iter) {
    return InfoData::getBoolByKey(iter, "systemIsGetItemSelf");
}

int getGeneralLife(InfoData* data, const char* actor) {
    return data->getInt(actor, "generalLife", 100);
}

int getGeneralLife(const al::ByamlIter& iter) {
    return InfoData::getIntByKey(iter, "generalLife", 100);
}

int getEnemyRank(InfoData* data, const char* actor) {
    return data->getInt(actor, "enemyRank");
}

int getAttackPower(InfoData* data, const char* actor) {
    return data->getInt(actor, "attackPower");
}

int getWeaponCommonGuardPower(InfoData* data, const char* actor) {
    return data->getInt(actor, "weaponCommonGuardPower");
}

float getWeaponCommonSharpWeaponPer(InfoData* data, const char* actor) {
    return data->getFloat(actor, "weaponCommonSharpWeaponPer", 10.0);
}

int getWeaponCommonSharpWeaponAddAtkMin(const al::ByamlIter& iter) {
    return InfoData::getIntByKey(iter, "weaponCommonSharpWeaponAddAtkMin");
}

int getWeaponCommonSharpWeaponAddAtkMax(const al::ByamlIter& iter) {
    return InfoData::getIntByKey(iter, "weaponCommonSharpWeaponAddAtkMax");
}

int getWeaponCommonSharpWeaponAddLifeMin(const al::ByamlIter& iter) {
    return InfoData::getIntByKey(iter, "weaponCommonSharpWeaponAddLifeMin");
}

int getWeaponCommonSharpWeaponAddLifeMax(const al::ByamlIter& iter) {
    return InfoData::getIntByKey(iter, "weaponCommonSharpWeaponAddLifeMax");
}

bool getWeaponCommonSharpWeaponAddCrit(const al::ByamlIter& iter) {
    return InfoData::getBoolByKey(iter, "weaponCommonSharpWeaponAddCrit");
}

int getWeaponCommonSharpWeaponAddGuardMin(const al::ByamlIter& iter) {
    return InfoData::getIntByKey(iter, "weaponCommonSharpWeaponAddGuardMin");
}

int getWeaponCommonSharpWeaponAddGuardMax(const al::ByamlIter& iter) {
    return InfoData::getIntByKey(iter, "weaponCommonSharpWeaponAddGuardMax");
}

int getWeaponCommonPoweredSharpAddAtkMin(const al::ByamlIter& iter) {
    return InfoData::getIntByKey(iter, "weaponCommonPoweredSharpAddAtkMin");
}

int getWeaponCommonPoweredSharpAddAtkMax(const al::ByamlIter& iter) {
    return InfoData::getIntByKey(iter, "weaponCommonPoweredSharpAddAtkMax");
}

int getWeaponCommonPoweredSharpAddLifeMin(const al::ByamlIter& iter) {
    return InfoData::getIntByKey(iter, "weaponCommonPoweredSharpAddLifeMin");
}

int getWeaponCommonPoweredSharpAddLifeMax(const al::ByamlIter& iter) {
    return InfoData::getIntByKey(iter, "weaponCommonPoweredSharpAddLifeMax");
}

int getWeaponCommonPoweredSharpAddGuardMin(const al::ByamlIter& iter) {
    return InfoData::getIntByKey(iter, "weaponCommonPoweredSharpAddGuardMin");
}

int getWeaponCommonPoweredSharpAddGuardMax(const al::ByamlIter& iter) {
    return InfoData::getIntByKey(iter, "weaponCommonPoweredSharpAddGuardMax");
}

float getWeaponCommonPoweredSharpAddThrowMin(const al::ByamlIter& iter) {
    return InfoData::getFloatByKey(iter, "weaponCommonPoweredSharpAddThrowMin", 1.0);
}

float getWeaponCommonPoweredSharpAddThrowMax(const al::ByamlIter& iter) {
    return InfoData::getFloatByKey(iter, "weaponCommonPoweredSharpAddThrowMax", 1.0);
}

bool getWeaponCommonPoweredSharpAddSpreadFire(const al::ByamlIter& iter) {
    return InfoData::getBoolByKey(iter, "weaponCommonPoweredSharpAddSpreadFire");
}

bool getWeaponCommonPoweredSharpAddZoomRapid(const al::ByamlIter& iter) {
    return InfoData::getBoolByKey(iter, "weaponCommonPoweredSharpAddZoomRapid");
}

float getWeaponCommonPoweredSharpAddRapidFireMin(const al::ByamlIter& iter) {
    return InfoData::getFloatByKey(iter, "weaponCommonPoweredSharpAddRapidFireMin", 1.0);
}

float getWeaponCommonPoweredSharpAddRapidFireMax(const al::ByamlIter& iter) {
    return InfoData::getFloatByKey(iter, "weaponCommonPoweredSharpAddRapidFireMax", 1.0);
}

bool getWeaponCommonPoweredSharpAddSurfMaster(const al::ByamlIter& iter) {
    return InfoData::getBoolByKey(iter, "weaponCommonPoweredSharpAddSurfMaster");
}

const char* getArmorNextRankName(InfoData* data, const char* actor) {
    return data->getString(actor, "armorNextRankName", sead::SafeString::cEmptyString);
}

int getItemStainColor(InfoData* data, const char* actor) {
    return data->getInt(actor, "itemStainColor", -1);
}

int getMonsterShopSellMamo(const al::ByamlIter& iter) {
    return InfoData::getIntByKey(iter, "monsterShopSellMamo");
}

}  // namespace ksys::act
