#pragma once

#include <basis/seadRawPrint.h>
#include <prim/seadBitUtil.h>

namespace agl {

template <typename ResDataType>
struct ResCommon {
    bool isValid() const { return mPtr != nullptr; }

    ResDataType* ptr() const {
        assertValid();
        return mPtr;
    }

    u8* ptrBytes() const { return reinterpret_cast<u8*>(mPtr); }

    bool isValidMagic() const {
        return sead::BitUtil::bitCastPtr<u32>(ptr(), 0) == ResDataType::getSignature();
    }

    bool isValidVersion() const {
        return sead::BitUtil::bitCastPtr<u32>(ptr(), 4) == ResDataType::getVersion();
    }

    void assertValid() const { SEAD_ASSERT(isValid()); }

    // NON_MATCHING: weird control flow
    void verify() const {
        char* b = reinterpret_cast<char*>(mPtr);
        assertValid();
        SEAD_ASSERT_MSG(isValidMagic(), "Wrong binary. [%c%c%c%c].", b[0], b[1], b[2], b[3]);
        SEAD_ASSERT_MSG(isValidVersion(), "Version error.current:%d binary:%d",
                        ResDataType::getVersion(), sead::BitUtil::bitCastPtr<u32>(ptr(), 4));
    }

    ResDataType* mPtr;
};

void ModifyEndianU32(bool big_endian, void* p_data, size_t size);

}  // namespace agl
