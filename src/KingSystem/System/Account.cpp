#include "KingSystem/System/Account.h"
#include <nn/account.h>

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(Account)

Account::~Account() {
    if (mFlags.isOn(Flag::HasUserHandle)) {
        if (mUserHandle) {
            delete mUserHandle;
            mUserHandle = nullptr;
        }
        mFlags.reset(Flag::HasUserHandle);
    }
}

void Account::init(sead::Heap* heap) {
    mUserHandle = new (heap) nn::account::UserHandle{};

    nn::account::Initialize();

    if (mFlags.isOff(Flag::HasOpenedUserSuccessfully)) {
        const auto result = nn::account::OpenPreselectedUser(mUserHandle);
        if (result.IsSuccess())
            mFlags.set(Flag::HasOpenedUserSuccessfully);
    }

    mFlags.set(Flag::HasUserHandle);
}

nn::account::UserHandle* Account::getUserHandle() const {
    return mUserHandle;
}

void Account::getUserId(nn::account::Uid* uid) const {
    if (mUserHandle)
        nn::account::GetUserId(uid, *mUserHandle);
    else
        *uid = {};
}

}  // namespace ksys
