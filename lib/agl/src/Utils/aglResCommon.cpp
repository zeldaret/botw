#include "agl/Utils/aglResCommon.h"
#include <basis/seadRawPrint.h>
#include <prim/seadEndian.h>

namespace agl {

void ModifyEndianU32(bool big_endian, void* p_data, size_t size) {
    SEAD_ASSERT(p_data != nullptr);
    SEAD_ASSERT(size % 4 == 0);

    u32* data = reinterpret_cast<u32*>(p_data);
    for (s32 i = 0; i < s32(size / 4); ++i) {
        data[i] = sead::Endian::toHostU32(
            big_endian ? sead::Endian::Types::cLittle : sead::Endian::Types::cBig, data[i]);
    }
}

}  // namespace agl
