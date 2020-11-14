#pragma once

#include <basis/seadTypes.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/Byaml/ByamlLocal.h"

namespace al {

class ByamlArrayIter {
public:
    explicit ByamlArrayIter(const u8* data);

    const u32* getDataTable() const;
    bool getDataByIndex(ByamlData* data, s32 index);

private:
    s32 getDataOffset() const {
        const s32 size = ByamlLocalUtil::getContainerSize(mData);
        return sead::Mathu::roundUp(size, 4);
    }

    static constexpr s32 TypeTableOffset = 4;

    const u8* mData;
};

}  // namespace al
