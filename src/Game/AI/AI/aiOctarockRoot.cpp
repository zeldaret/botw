#include "Game/AI/AI/aiOctarockRoot.h"

namespace uking::ai {

OctarockRoot::OctarockRoot(const InitArg& arg) : OctarockRootBase(arg) {}

OctarockRoot::~OctarockRoot() = default;

bool OctarockRoot::init_(sead::Heap* heap) {
    return OctarockRootBase::init_(heap);
}

void OctarockRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    OctarockRootBase::enter_(params);
}

void OctarockRoot::leave_() {
    OctarockRootBase::leave_();
}

void OctarockRoot::loadParams_() {
    OctarockRootBase::loadParams_();
    getStaticParam(&mIsWigBreakable_s, "IsWigBreakable");
    getStaticParam(&mItemName_s, "ItemName");
    getStaticParam(&mConnectRigidBodyName_s, "ConnectRigidBodyName");
    getStaticParam(&mConnectTgtBodyName_s, "ConnectTgtBodyName");
    getStaticParam(&mShootActorName_s, "ShootActorName");
    // FIXME: CALL _ZNK4sead22BufferedSafeStringBaseIcE22assureTerminationImpl_Ev @ 0x7100b0ce00
    // FIXME: CALL _ZN4sead20StringPrintFormatterC2EPNS_22BufferedSafeStringBaseIcEE @ 0x7100b0c320
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL _ZN4sead20StringPrintFormatterC2EPNS_22BufferedSafeStringBaseIcEE @ 0x7100b0c320
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL _ZN4sead20StringPrintFormatterC2EPNS_22BufferedSafeStringBaseIcEE @ 0x7100b0c320
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    getStaticParam(&mExtraShootActorName_s, "ExtraShootActorName");
    getStaticParam(&mExtraShootActorKey_s, "ExtraShootActorKey");
    getMapUnitParam(&mCarryActorName_m, "CarryActorName");
    getAITreeVariable(&mVacuumedExplodingBomb_a, "VacuumedExplodingBomb");
    getAITreeVariable(&mOctarockFormChangeUnit_a, "OctarockFormChangeUnit");
}

}  // namespace uking::ai
