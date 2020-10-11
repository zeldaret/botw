#include "KingSystem/Resource/resInfoContainer.h"
#include <codec/seadHashCRC32.h>
#include <prim/seadBitUtil.h>
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys::res {

ResourceInfoContainer::ResourceInfoContainer() = default;

ResourceInfoContainer::~ResourceInfoContainer() = default;

// NON_MATCHING: LoadRequest field write order
bool ResourceInfoContainer::loadResourceSizeTable() {
    const auto load_res = [&] {
        LoadRequest req;
        req._68 = nullptr;
        req.mArena = nullptr;
        req.mPackHandle = nullptr;
        req._22 = false;
        req._20 = false;
        req._21 = false;
        req._26 = false;
        req.mFileDevice = nullptr;
        req.mLoadCompressed = true;
        req._24 = false;
        req._8 = true;
        req.mLoadDataAlignment = 8;
        req.mBufferSize = 0;
        req.mEntryFactory = nullptr;
        req.mAocFileDevice = nullptr;
        req._34 = 0;
        req.mRequester = "ResourceInfoContainer";
        req.mPath = "System/Resource/ResourceSizeTable.product.rsizetable";
        req._c = 1;
        return sead::DynamicCast<Resource>(mRstbHandle.load(req.mPath, req));
    };

    const Resource* resource = load_res();
    if (!resource)
        return false;

    const u8* data = resource->getRawData();

    if (data[0] == 'R' && data[1] == 'S' && data[2] == 'T' && data[3] == 'B') {
        stubbedLogFunction();
        const auto num_entries = sead::BitUtil::bitCastPtr<s32>(data, 0x4);
        const auto num_string_entries = sead::BitUtil::bitCastPtr<s32>(data, 0x8);

        auto* entries_data =
            reinterpret_cast<const ResEntry*>(reinterpret_cast<const u8*>(data) + 0xc);

        if (num_entries >= 1) {
            mEntries = {num_entries, entries_data};
            entries_data += num_entries;
        }

        if (num_string_entries >= 1) {
            mStringEntries = {num_string_entries,
                              reinterpret_cast<const ResStringEntry*>(entries_data)};
            // Log each conflict.
            for (s32 i = 0; i < num_string_entries; ++i)
                stubbedLogFunction();
        }
    } else {
        // Assume that there is no string table.
        stubbedLogFunction();
        if (resource->getRawSize() != 0) {
            const u32 num_entries = resource->getRawSize() / sizeof(ResEntry);
            mEntries.setBuffer(num_entries,
                               reinterpret_cast<const ResEntry*>(resource->getRawData()));
        }
    }

    stubbedLogFunction();
    stubbedLogFunction();
    stubbedLogFunction();
    return true;
}

// NON_MATCHING: missing mStringEntries(string_entry_idx).res_size > 0 check
u32 ResourceInfoContainer::getResourceSize(const sead::SafeString& name) const {
    const u32 name_hash = sead::HashCRC32::calcStringHash(name.cstr());

    const s32 entry_idx = mEntries.binarySearch({name_hash, 0}, ResEntry::compareT);
    if (entry_idx >= 1 && mEntries(entry_idx).res_size > 0)
        return mEntries(entry_idx).res_size;

    const s32 string_entry_idx = mStringEntries.binarySearchC(
        [&](const ResStringEntry& entry) { return entry.compare(name); });
    if (string_entry_idx >= 1 && mStringEntries(string_entry_idx).res_size > 0)
        return mStringEntries(string_entry_idx).res_size;

    return 0;
}

namespace {
[[gnu::noinline]] bool stringLessThan(const sead::SafeString& a, const sead::SafeString& b) {
    return a < b;
}
}  // namespace

[[gnu::noinline]] s32
ResourceInfoContainer::ResStringEntry::compare(const sead::SafeString& name) const {
    if (res_name > name)
        return 1;
    if (stringLessThan(res_name, name))
        return -1;
    return 0;
}

}  // namespace ksys::res
