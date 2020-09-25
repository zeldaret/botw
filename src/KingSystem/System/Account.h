#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/Utils/Types.h"

namespace nn::account {
class Uid;
class UserHandle;
}  // namespace nn::account

namespace ksys {

class Account {
    SEAD_SINGLETON_DISPOSER(Account)
    Account() = default;
    virtual ~Account();

public:
    void init(sead::Heap* heap);

    nn::account::UserHandle* getUserHandle() const;
    void getUserId(nn::account::Uid* uid) const;

private:
    enum class Flag : u8 {
        HasUserHandle = 0x1,
        HasOpenedUserSuccessfully = 0x2,
    };

    [[maybe_unused]] void* _28 = nullptr;
    sead::TypedBitFlag<Flag> mFlags;
    nn::account::UserHandle* mUserHandle = nullptr;
};
KSYS_CHECK_SIZE_NX150(Account, 0x40);

}  // namespace ksys
