#include "KingSystem/Sound/sndInfoData.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys::snd {

SEAD_SINGLETON_DISPOSER_IMPL(InfoData)

InfoData::~InfoData() {
    if (mRootIter)
        delete mRootIter;
}

void InfoData::loadSoundInfo(sead::Heap* heap) {
    res::LoadRequest req;
    req.mRequester = "snd::InfoData";
    req._22 = true;
    mResHandle.load("Actor/Sound/SoundInfo.byml", &req);

    auto* resource = sead::DynamicCast<sead::DirectResource>(mResHandle.getResource());

    if (mRootIter)
        delete mRootIter;
    mRootIter = new (heap) al::ByamlIter(resource->getRawData());
}

void InfoData::init(sead::Heap* heap) {
    loadSoundInfo(heap);
}

al::ByamlIter InfoData::getInfo(const sead::SafeString& key) const {
    const auto iter = mRootIter->getIterByKey(key.cstr());
    return al::ByamlIter(iter);
}

sead::SafeString InfoData::getSoundSettingUserName(const sead::SafeString& key) const {
    const auto iter = getInfo(key);
    const char* name = "Dummy";
    iter.tryGetStringByKey(&name, "SoundSettingUserName");
    return name;
}

sead::SafeString InfoData::getReactionSettingLandType(const al::ByamlIter& iter,
                                                      const sead::SafeString& key) const {
    const char* value = "Auto";
    iter.tryGetStringByKey(&value, "ReactionSettingLandType");
    return value;
}

float InfoData::getReactionSettingLandPitch(const al::ByamlIter& iter) const {
    float value = 1.0;
    iter.tryGetFloatByKey(&value, "ReactionSettingLandPitch");
    return value;
}

float InfoData::getReactionSettingLandVolume(const al::ByamlIter& iter) const {
    float value = 1.0;
    iter.tryGetFloatByKey(&value, "ReactionSettingLandVolume");
    return value;
}

float InfoData::getReactionSettingLandVelocityRatio(const al::ByamlIter& iter) const {
    float value = 1.0;
    iter.tryGetFloatByKey(&value, "ReactionSettingLandVelocityRadio");
    return value;
}

sead::SafeString InfoData::getReactionSettingSlideType(const al::ByamlIter& iter) const {
    const char* value = "Auto";
    iter.tryGetStringByKey(&value, "ReactionSettingSlideType");
    return value;
}

sead::SafeString InfoData::getReactionSettingSlideSlideType(const al::ByamlIter& iter) const {
    const char* value = "Drag";
    iter.tryGetStringByKey(&value, "ReactionSettingSlideSlideType");
    return value;
}

float InfoData::getReactionSettingSlidePitch(const al::ByamlIter& iter) const {
    float value = 1.0;
    iter.tryGetFloatByKey(&value, "ReactionSettingSlidePitch");
    return value;
}

float InfoData::getReactionSettingSlideVolume(const al::ByamlIter& iter) const {
    float value = 1.0;
    iter.tryGetFloatByKey(&value, "ReactionSettingSlideVolume");
    return value;
}

float InfoData::getReactionSettingSlideVelocityRatio(const al::ByamlIter& iter) const {
    float value = 1.0;
    iter.tryGetFloatByKey(&value, "ReactionSettingSlideVelocityRatio");
    return value;
}

sead::SafeString InfoData::getWeaponOwnerSettingOwnerType(const al::ByamlIter& iter) const {
    const char* value = "None";
    iter.tryGetStringByKey(&value, "WeaponOwnerSettingOwnerType");
    return value;
}

sead::SafeString InfoData::getEquipSoundSettingEquipMaterial(const al::ByamlIter& iter) const {
    const char* value = "Dummy";
    iter.tryGetStringByKey(&value, "EquipSoundSettingEquipMaterial");
    return value;
}

bool InfoData::getMiscInDoorOcclusion(const al::ByamlIter& iter) const {
    bool value = true;
    iter.tryGetBoolByKey(&value, "MiscInDoorOcclusion");
    return value;
}

sead::SafeString InfoData::getMiscPlantShakeType(const al::ByamlIter& iter) const {
    const char* value = "None";
    iter.tryGetStringByKey(&value, "MiscPlantShakeType");
    return value;
}

}  // namespace ksys::snd
