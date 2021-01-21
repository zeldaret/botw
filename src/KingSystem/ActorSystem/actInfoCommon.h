#pragma once

namespace al {
class ByamlIter;
}

namespace ksys::act {

class InfoData;

bool getSystemIsGetItemSelf(InfoData* data, const char* actor);
bool getSystemIsGetItemSelf(const al::ByamlIter& iter);

int getGeneralLife(InfoData* data, const char* actor);
int getGeneralLife(const al::ByamlIter& iter);

int getEnemyRank(InfoData* data, const char* actor);
int getAttackPower(InfoData* data, const char* actor);

int getWeaponCommonGuardPower(InfoData* data, const char* actor);
float getWeaponCommonSharpWeaponPer(InfoData* data, const char* actor);

int getWeaponCommonSharpWeaponAddAtkMin(const al::ByamlIter& iter);
int getWeaponCommonSharpWeaponAddAtkMax(const al::ByamlIter& iter);
int getWeaponCommonSharpWeaponAddLifeMin(const al::ByamlIter& iter);
int getWeaponCommonSharpWeaponAddLifeMax(const al::ByamlIter& iter);
bool getWeaponCommonSharpWeaponAddCrit(const al::ByamlIter& iter);
int getWeaponCommonSharpWeaponAddGuardMin(const al::ByamlIter& iter);
int getWeaponCommonSharpWeaponAddGuardMax(const al::ByamlIter& iter);

int getWeaponCommonPoweredSharpAddAtkMin(const al::ByamlIter& iter);
int getWeaponCommonPoweredSharpAddAtkMax(const al::ByamlIter& iter);
int getWeaponCommonPoweredSharpAddLifeMin(const al::ByamlIter& iter);
int getWeaponCommonPoweredSharpAddLifeMax(const al::ByamlIter& iter);
int getWeaponCommonPoweredSharpAddGuardMin(const al::ByamlIter& iter);
int getWeaponCommonPoweredSharpAddGuardMax(const al::ByamlIter& iter);
float getWeaponCommonPoweredSharpAddThrowMin(const al::ByamlIter& iter);
float getWeaponCommonPoweredSharpAddThrowMax(const al::ByamlIter& iter);
bool getWeaponCommonPoweredSharpAddSpreadFire(const al::ByamlIter& iter);
bool getWeaponCommonPoweredSharpAddZoomRapid(const al::ByamlIter& iter);
float getWeaponCommonPoweredSharpAddRapidFireMin(const al::ByamlIter& iter);
float getWeaponCommonPoweredSharpAddRapidFireMax(const al::ByamlIter& iter);
bool getWeaponCommonPoweredSharpAddSurfMaster(const al::ByamlIter& iter);

const char* getArmorNextRankName(InfoData* data, const char* actor);

int getItemStainColor(InfoData* data, const char* actor);

int getMonsterShopSellMamo(const al::ByamlIter& iter);

}  // namespace ksys::act
