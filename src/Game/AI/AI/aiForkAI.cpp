#include "Game/AI/AI/aiForkAI.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

ForkAI::ForkAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ForkAI::~ForkAI() = default;

bool ForkAI::init_(sead::Heap* heap) {
    mFlags.set(Flag::_80);
    return true;
}

void ForkAI::enter_(ksys::act::ai::InlineParamPack* params) {
    const int num_children = getNumChildren();
    if (num_children >= 1) {
        for (int i = 0; i < num_children; ++i)
            getChild(i)->enter(params, getName());
        changeChildIdx(num_children - 1);
    } else {
        SEAD_WARN("ForkAI::enter_: no children");
        changeChildIdx(num_children - 1);
    }
    setRootAiFlag(ksys::act::ai::RootAiFlag::_100);
}

bool ForkAI::reenter(ksys::act::ai::ActionBase* other, const sead::SafeString& context) {
    auto* other_ = sead::DynamicCast<ForkAI>(other);
    if (!other_)
        return false;

    const int num_children = getNumChildren();
    if (other_->getNumChildren() != num_children)
        return false;

    changeChildIdx(other_->mPrevChildIdx);
    changeChildIdx(other_->mChildIdx);

    bool ok = true;
    for (int i = 0; i < num_children; ++i) {
        auto* child_other = other_->getChild(i);
        auto* child = getChild(i);
        if (child_other && child)
            ok &= child->takeOver(child_other, getName());
    }
    return ok;
}

void ForkAI::calc() {
    calc_();

    const int num_children = getNumChildren();
    for (int i = 0; i < num_children; ++i)
        getChild(i)->calc();

    handlePendingChildChange();
}

void ForkAI::leave_() {
    const int num_children = getNumChildren();
    for (int i = num_children - 2; i >= 0; --i)
        getChild(i)->leave();
}

bool ForkAI::isFailed() const {
    const int num_children = getNumChildren();
    bool failed = false;
    int i = 0;
    for (; i < num_children; ++i) {
        auto* child = getChild(i);
        failed |= child->isFailed();
        if (!child->isFinished() && !child->isFailed() && !child->isFlag4Set())
            break;
    }
    return i == num_children && failed;
}

bool ForkAI::isFinished() const {
    const int num_children = getNumChildren();
    bool finished = false;
    int i = 0;
    for (; i < num_children; ++i) {
        auto* child = getChild(i);
        if (child->isFailed())
            break;
        if (child->isFinished())
            finished = true;
        else if (!child->isFlag4Set())
            break;
    }
    return i == num_children && finished;
}

bool ForkAI::isFlag4Set() const {
    const int num_children = getNumChildren();
    for (int i = 0; i < num_children; ++i) {
        if (!getChild(i)->isFlag4Set())
            return false;
    }
    return true;
}

bool ForkAI::handleMessage_(ksys::Message* message) {
    const int num_children = getNumChildren();

    bool ok = false;
    for (int i = 0; i < num_children - 1; ++i)
        ok |= getChild(i)->handleMessage(message);

    if (!ok)
        return false;

    getChild(num_children - 1)->handleMessage(message);
    return true;
}

bool ForkAI::handleMessage2_(ksys::Message* message) {
    const int num_children = getNumChildren();

    bool ok = false;
    for (int i = 0; i < num_children - 1; ++i)
        ok |= getChild(i)->handleMessage2(message);

    if (!ok)
        return false;

    getChild(num_children - 1)->handleMessage2(message);
    return true;
}

void ForkAI::getCurrentName(sead::BufferedSafeString* name, ksys::act::ai::ActionBase* last) const {
    name->appendWithFormat("/%s{", getName());
    if (this != last) {
        const int num_children = getNumChildren();
        for (int i = 0; i < num_children; ++i) {
            getChild(i)->getCurrentName(name, last);
            name->appendWithFormat(",");
        }
    }
    name->appendWithFormat("}");
}

void ForkAI::getNames(sead::BufferedSafeString* out) const {
    out->appendWithFormat("{");
    const int num_children = getNumChildren();
    for (int i = 0; i < num_children; ++i) {
        auto* child = getChild(i);
        out->appendWithFormat("/%s", child->getName());
        if (auto* ai = sead::DynamicCast<Ai>(child))
            ai->getNames(out);
        out->appendWithFormat(",");
    }
    out->appendWithFormat("}");
}

}  // namespace uking::ai
