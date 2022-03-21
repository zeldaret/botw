/**
 * @file SoundDataManager.h
 * @brief Sound data management implementation.
 */

#pragma once

#include <nn/types.h>

namespace nn {
namespace atk {
class SoundDataManager {
public:
    SoundDataManager();
    virtual ~SoundDataManager();

    virtual void InvalidateData(void const*, void const*);
    virtual void SetFileAddressToTable(u32, void const*);
    virtual u64 GetFileAddressFromTable(u32) const;
    virtual u32 GetFileAddressImpl(u32) const;

    u8 _0[0x240];
};
};  // namespace atk
};  // namespace nn