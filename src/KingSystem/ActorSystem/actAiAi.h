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
    void calc() override;
    ActionBase* changeChildLater(const sead::SafeString& name) override;
    void getParams(ParamNameTypePairs* pairs, bool update_use_count) const override;
    s32 getNumChildren() const override { return mChildren.size(); }
    bool initChildren(const AIDefSet& set, sead::Heap* heap) override;
    ActionBase* getCurrentChild() const override;
    ActionType getType() const override { return ActionType::AI; }
    bool reenter(ActionBase* other, const sead::SafeString& context) override;
    void postLeave() override { changeChildIdx(InvalidIdx); }
    ActionBase* getChild(s32 idx) const override { return mChildren[idx]; }
    virtual void getNames(sead::BufferedSafeString* out) const;

    bool gatherParamsFromChildren(sead::Heap* heap);

    void changeAS(const char* as_name, bool b, int x, int y);
    // TODO: figure out what this actually does and rename
    bool checkAS(int x, int y);

    /// @returns whether there was a pending child change.
    bool handlePendingChildChange();
    bool hasPendingChildChange() const;
    s32 getChildIdx(const sead::SafeString& name) const;
    void changeChild(u32 idx, InlineParamPack* params = nullptr);
    void changeChild(const char* name, InlineParamPack* params = nullptr);

    bool isCurrentChild(const sead::SafeString& name) const;
    bool isCurrentAction(const sead::SafeString& name);

protected:
    virtual void calc_() {}
    virtual void handlePendingChildChange_() { changeChild(mPendingChildIdx); }
    void changeChildIdx(int new_idx);

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

struct AiFactory {
    using CreateFn = Ai* (*)(const Ai::InitArg& arg, sead::Heap* heap);
    u32 hash;
    CreateFn create_fn;

    template <typename T>
    static Ai* make(const Ai::InitArg& arg, sead::Heap* heap) {
        return new (heap) T(arg);
    }
};

class Ais {
public:
    Ais();
    ~Ais();

    void finalize();

    bool init(Actor* actor, sead::Heap* heap);
    bool updateForPreDelete() const;
    void onPreDelete() const;

    const sead::Buffer<Ai*>& getClasses() const { return mClasses; }

    static AiFactory* getFactory(const sead::SafeString& name);
    static void setFactories(int count, AiFactory* factories);

private:
    static sead::Buffer<AiFactory> sFactories;
    sead::Buffer<Ai*> mClasses;
    // Non-owning buffer.
    sead::Buffer<Ai*> mOnPreDeleteCbs;
    // Non-owning buffer.
    sead::Buffer<Ai*> mUpdateForPreDeleteCbs;
};

}  // namespace ksys::act::ai
