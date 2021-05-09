#pragma once

#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

class Revision final : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(Revision)
    Revision() = default;

public:
    void init(sead::Heap* heap);
    void loadInfo();

    void* get28() const { return _28; }
    int getResourceVer() const { return mResourceVer; }
    int getProgramVer() const { return mProgramVer; }
    const sead::SafeString* getBuilderName() const { return mBuilderName; }
    const sead::SafeString* getStageSelectName() const { return mStageSelectName; }
    int get48() const { return _48; }
    int get4C() const { return _4c; }

private:
    void* _28{};
    int mResourceVer = -1;
    int mProgramVer = -1;
    const sead::SafeString* mBuilderName{};
    const sead::SafeString* mStageSelectName{};
    int _48 = -1;
    int _4c = 0;
};
KSYS_CHECK_SIZE_NX150(Revision, 0x50);

}  // namespace ksys
