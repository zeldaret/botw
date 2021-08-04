#include "KingSystem/ActorSystem/actLinkTag.h"

namespace ksys::act {

LinkTag* LinkTag::construct(const BaseProc::CreateArg& arg, sead::Heap* heap){
    return new (heap, std::nothrow) LinkTag(arg);
}

LinkTag::LinkTag(const BaseProc::CreateArg& arg) : BaseProc(arg), mJob(this,&LinkTag::calc) {
    mJobHandlers[3] = &mJob;
}

}  // namespace ksys::act
