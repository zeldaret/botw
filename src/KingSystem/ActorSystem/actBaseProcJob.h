#pragma once

#include <container/seadSafeArray.h>
#include <container/seadTList.h>
#include <mc/seadJob.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class BaseProc;

enum class Priority {
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

    BaseProc* getProc() const { return mData; }

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

struct BaseProcJobList {
    sead::TListNode<BaseProc*>* front() const;
    sead::TListNode<BaseProc*>* next(BaseProcJobLink* link) const;
    int size() const;

    sead::SafeArray<sead::TList<BaseProc*>, 2> lists;
};

class BaseProcJobLists {
public:
    BaseProcJobLists() = default;
    ~BaseProcJobLists() { ; }

    void pushJob(BaseProcJobLink& link);
    void eraseJob(BaseProcJobLink& link);
    sead::TListNode<BaseProc*>* getJobWithTopPriority() const;
    sead::TListNode<BaseProc*>* getNextJobWithTopPriority(BaseProcJobLink* link) const;
    sead::TListNode<BaseProc*>* getNextJob(BaseProcJobLink* link) const;
    BaseProcJobList& getList(int idx) { return mLists[idx]; }
    const BaseProcJobList& getList(int idx) const { return mLists[idx]; }

private:
    sead::SafeArray<BaseProcJobList, 8> mLists{};
};

class BaseProcJob final : public sead::Job {
public:
    BaseProcJob() = default;
    void invoke() override;

    void set(BaseProcJobLink* link, int rounds) {
        mJobLink = link;
        mRequiredCalcRounds = rounds;
    }

private:
    friend class BaseProcJobQue;

    BaseProcJobLink* mJobLink = nullptr;
    int mRequiredCalcRounds = 0;
};

}  // namespace ksys::act
