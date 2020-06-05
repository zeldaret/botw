#pragma once

#include <container/seadTList.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class BaseProc;

enum class Priority : u8 {
    PlayerBefore = 0,
    Player = 2,
    PlayerAfter = 2,
    AllAfter = 3,
};

enum class JobType {
    PreCalc = 0,
    Calc1 = 1,
    Calc2 = 2,
    Calc3 = 3,
    Calc4 = 4,
    AfterMessageDispatch = 5,
    Calc3Alt = 6,
    Invalid = 7,
};

class BaseProcJobLink : public sead::TListNode<BaseProc*> {
public:
    BaseProcJobLink(BaseProc* proc, u8 priority);

    u8 getPriority() const { return mPriority; }
    u8 getPriority2() const { return mPriority2; }

    void setNewPriority(u8 priority) { mNewPriority = priority; }
    void setNewPriority2(u8 priority) { mNewPriority2 = priority; }

    void loadNewPriority() { mPriority = mNewPriority; }
    void loadNewPriority2() { mPriority2 = mNewPriority2; }

    bool hasPriorityChange() const {
        return mPriority != mNewPriority || mPriority2 != mNewPriority2;
    }

private:
    u8 mPriority;
    u8 mNewPriority;
    u8 mPriority2;
    u8 mNewPriority2;
};
KSYS_CHECK_SIZE_NX150(BaseProcJobLink, 0x28);

}  // namespace ksys::act
