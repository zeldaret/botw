#include "Game/AI/Action/actionForkDisableContactByPreAS.h"

namespace uking::action {

ForkDisableContactByPreAS::ForkDisableContactByPreAS(const InitArg& arg)
    : ForkDisableContact(arg) {}

ForkDisableContactByPreAS::~ForkDisableContactByPreAS() = default;

bool ForkDisableContactByPreAS::init_(sead::Heap* heap) {
    return ForkDisableContact::init_(heap);
}

void ForkDisableContactByPreAS::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkDisableContact::enter_(params);
}

void ForkDisableContactByPreAS::leave_() {
    ForkDisableContact::leave_();
}

void ForkDisableContactByPreAS::loadParams_() {
    ForkDisableContact::loadParams_();
    getStaticParam(&mDisableTime_s, "DisableTime");
    // FIXME: CALL _ZNK4sead22BufferedSafeStringBaseIcE22assureTerminationImpl_Ev @ 0x7100b0ce00
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
}

void ForkDisableContactByPreAS::calc_() {
    ForkDisableContact::calc_();
}

}  // namespace uking::action
