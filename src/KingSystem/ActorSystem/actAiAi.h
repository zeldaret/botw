#pragma once

#include <container/seadBuffer.h>
#include "KingSystem/ActorSystem/actAiActionBase.h"

namespace ksys::act::ai {

class Ai : public ActionBase {
    SEAD_RTTI_OVERRIDE(Ai, ActionBase)
public:
    explicit Ai(const InitArg& arg);
    ~Ai() override;

    bool isFlag4Set() const override;
    bool reenter_(ActionBase* other, bool x) override;
    void calc() override;
    void* m22() override;
    void getParams(ParamNameTypePairs* pairs, bool update_use_count) const override;
    s32 getNumChildren() const override { return mChildren.size(); }
    bool initChildren(const AIDefSet& set, sead::Heap* heap) override;
    ActionBase* getCurrentChild() const override;
    ActionType getType() const override { return ActionType::AI; }
    bool reenter(ActionBase* other, const sead::SafeString& context) override;
    void postLeave() override { updateChildIdx(InvalidIdx); }
    ActionBase* getChild(s32 idx) const override { return mChildren[idx]; }
    virtual const char* getPreviousName();

protected:
    virtual void calc_() {}
    virtual void handlePendingChildChange_() { changeChildState(mPendingChildIdx); }
    void updateChildIdx(u16 new_idx);
    void changeChildState(u16 idx, InlineParamPack* params = nullptr);

    static constexpr u16 InvalidIdx = 0xffff;

    // TODO: give better names to these variables
    u16 mChildIdx = InvalidIdx;
    u16 mPrevChildIdx = InvalidIdx;
    u16 mPendingChildIdx = InvalidIdx;
    u16 mNewChildIdx = InvalidIdx;
    sead::Buffer<ActionBase*> mChildren;

private:
    bool initChildren_(s32 num_children, const char** names, sead::Buffer<u16>& indices,
                       sead::Heap* heap);
};
KSYS_CHECK_SIZE_NX150(Ai, 0x38);

}  // namespace ksys::act::ai
