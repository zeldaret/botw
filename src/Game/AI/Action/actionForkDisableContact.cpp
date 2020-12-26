#include "Game/AI/Action/actionForkDisableContact.h"

namespace uking::action {

ForkDisableContact::ForkDisableContact(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkDisableContact::~ForkDisableContact() = default;

bool ForkDisableContact::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkDisableContact::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkDisableContact::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkDisableContact::loadParams_() {
    getStaticParam(&mRecoverDelayTimeMin_s, "RecoverDelayTimeMin");
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

void ForkDisableContact::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
