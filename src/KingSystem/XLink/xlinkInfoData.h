#pragma once

#include <heap/seadDisposer.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys::xlink {

class InfoData {
    SEAD_SINGLETON_DISPOSER(InfoData)

    InfoData() = default;
    virtual ~InfoData();

public:
    void init(sead::Heap* heap);

    al::ByamlIter getIter(const sead::SafeString& key) const;

    sead::SafeString getXLinkSettingPropertyTableName(const al::ByamlIter& iter) const;
    sead::SafeString getXLinkSettingFootStepProcTypeName(const al::ByamlIter& iter) const;
    float getXLinkSettingVeloClampThreshold(const al::ByamlIter& iter) const;
    float getXLinkSettingVeloRollClampThreshold(const al::ByamlIter& iter) const;
    bool getXLinkSettingIsReactionTargetEnemy(const al::ByamlIter& iter) const;
    bool getXLinkSettingIsReactionTargetTinyEnemy(const al::ByamlIter& iter) const;
    bool getXLinkSettingIsReactionTargetObject(const al::ByamlIter& iter) const;
    bool getXLinkSettingIsIgnoreDamageToObject(const sead::SafeString& key) const;

private:
    void loadInfo(sead::Heap* heap);

    al::ByamlIter* mRootIter{};
    res::Handle mResHandle{};
};

}  // namespace ksys::xlink
