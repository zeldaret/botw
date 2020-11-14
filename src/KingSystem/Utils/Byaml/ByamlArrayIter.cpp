#include "KingSystem/Utils/Byaml/ByamlArrayIter.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/Byaml/ByamlData.h"
#include "KingSystem/Utils/Byaml/ByamlLocal.h"

namespace al {
ByamlArrayIter::ByamlArrayIter(const u8* data) {
    mData = data;
}

const u32* ByamlArrayIter::getDataTable() const {
    return reinterpret_cast<const u32*>(&mData[TypeTableOffset + getDataOffset()]);
}

bool ByamlArrayIter::getDataByIndex(ByamlData* data, s32 index) {
    if (index < 0) {
        return false;
    }

    if (index >= ByamlLocalUtil::getContainerSize(mData)) {
        return false;
    }

    data->setType(ByamlType(mData[TypeTableOffset + index]));
    data->setValue(getDataTable()[index]);

    return true;
}
}  // namespace al