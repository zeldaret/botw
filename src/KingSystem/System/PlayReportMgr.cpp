#include "KingSystem/System/PlayReportMgr.h"
#include <nn/account.h>
#include <nn/prepo.h>
#include "KingSystem/System/Account.h"
#include "KingSystem/System/ProductReporter.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(PlayReportMgr)

PlayReportMgr::~PlayReportMgr() {
    if (mReporter)
        delete mReporter;
}

bool PlayReport::setEventId(sead::BufferedSafeString& event_id) {
    if (!mHasNinPrepoReport)
        return false;

    event_id.replaceCharList("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "abcdefghijklmnopqrstuvwxyz");
    return mNinPlayReport->SetEventId(event_id.cstr()).IsSuccess();
}

bool PlayReport::add(const sead::SafeString& key, u32 value) {
    return mHasNinPrepoReport && mNinPlayReport->Add(key.cstr(), s64(value)).IsSuccess();
}

bool PlayReport::add(const sead::SafeString& key, s32 value) {
    return mHasNinPrepoReport && mNinPlayReport->Add(key.cstr(), s64(value)).IsSuccess();
}

bool PlayReport::add(const sead::SafeString& key, f32 value) {
    return mHasNinPrepoReport && mNinPlayReport->Add(key.cstr(), value).IsSuccess();
}

bool PlayReport::add(const sead::SafeString& key, const sead::SafeString& value) {
    return mHasNinPrepoReport && mNinPlayReport->Add(key.cstr(), value.cstr()).IsSuccess();
}

bool PlayReport::save() {
    if (!mHasNinPrepoReport)
        return false;

    nn::account::Uid uid;
    Account::instance()->getUserId(&uid);
    if (uid.IsValid()) {
        static_cast<void>(mNinPlayReport->GetCount());
        return mNinPlayReport->Save(uid).IsSuccess();
    }
    static_cast<void>(ProductReporter::getSomeBool());
    static_cast<void>(mNinPlayReport->GetCount());
    return mNinPlayReport->Save().IsSuccess();
}

void PlayReport::init(s32 num_entries, sead::Heap* heap) {
    if (mHasNinPrepoReport)
        return;

    auto* report = new (heap) nn::prepo::PlayReport;
    const u32 buffer_size = nn::prepo::PlayReport::CalcBufferSize(num_entries);
    mNinPlayReport = report;
    if (buffer_size > 0 && mBuffer.tryAllocBuffer(buffer_size, heap)) {
        mNinPlayReport->SetBuffer(mBuffer.getBufferPtr(), buffer_size);
        mHasNinPrepoReport = true;
    }
}

PlayReport::~PlayReport() {
    if (!mHasNinPrepoReport)
        return;

    if (mNinPlayReport) {
        delete mNinPlayReport;
        mNinPlayReport = nullptr;
    }

    if (mHasNinPrepoReport)
        mBuffer.freeBuffer();

    mHasNinPrepoReport = false;
}

}  // namespace ksys
