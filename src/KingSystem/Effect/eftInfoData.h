#pragma once

#include <heap/seadDisposer.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys::eft {

class InfoData {
    SEAD_SINGLETON_DISPOSER(InfoData)

    InfoData() = default;
    virtual ~InfoData();

public:
    void init(sead::Heap* heap);

    al::ByamlIter getIter(const sead::SafeString& key) const;
    sead::SafeString getEffectSettingUserName(const sead::SafeString& key) const;

private:
    void loadEffectInfo(sead::Heap* heap);

    al::ByamlIter* mRootIter{};
    res::Handle mResHandle{};
};

}  // namespace ksys::eft
