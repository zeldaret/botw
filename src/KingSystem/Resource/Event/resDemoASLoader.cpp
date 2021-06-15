#include "KingSystem/Resource/Event/resDemoASLoader.h"
#include "KingSystem/Resource/Actor/resResourceAS.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys::res {

DemoASLoader::DemoASLoader(const sead::SafeString& event_name, sead::Heap* heap)
    : mHeap(heap), mEventName(event_name) {}

DemoASLoader::~DemoASLoader() {
    mHandles.freeBuffer();
    mNames.freeBuffer();
}

void DemoASLoader::load(const al::ByamlIter& iter, bool synchronous, Handle* pack_handle) {
    al::ByamlIter as_list;
    if (!iter.tryGetIterByKey(&as_list, "as"))
        return;

    const int num_as = as_list.getSize();
    if (num_as <= 0) {
        mNumAS = 0;
    } else {
        mHandles.allocBufferAssert(num_as, mHeap);
        mNames.allocBufferAssert(num_as, mHeap);
        mNumAS = 0;

        for (int i = 0; i < num_as; ++i) {
            al::ByamlIter entry;
            as_list.tryGetIterByIndex(&entry, i);

            const char* file_c;
            entry.tryGetStringByKey(&file_c, "file");
            const sead::SafeString file = file_c;

            sead::FixedSafeString<256> path;
            path.format("Actor/AS/%s/%s.bas", mEventName.cstr(), file.cstr());

            mNames[mNumAS].copy(file);

            LoadRequest request;
            request.mRequester = "DemoASLoader";
            request.mPackHandle = pack_handle;
            request._22 = true;
            Handle::Status status = Handle::Status::Unknown;
            if (synchronous)
                mHandles[mNumAS].load(path, &request, &status);
            else
                mHandles[mNumAS].requestLoad(path, &request, &status);

            ++mNumAS;
        }
    }

    mStatus = synchronous ? Status::Succeeded : Status::Loading;
}

const char* DemoASLoader::getName(int idx) const {
    return mNames[idx].cstr();
}

AS* DemoASLoader::getAS(int idx) const {
    return sead::DynamicCast<AS>(mHandles[idx].getResource());
}

bool DemoASLoader::finishLoad() {
    if (mStatus == Status::Loading) {
        bool ready = true;

        for (int i = 0; i < mNumAS; ++i) {
            auto& handle = mHandles[i];

            if (handle.isReadyOrNeedsParse())
                handle.parseResource(nullptr);

            if (handle.isReady()) {
                if (handle.checkLoadStatus()) {
                    mStatus = Status::Failed;
                    ready = false;
                    break;
                }
            } else {
                ready = false;
            }
        }

        if (ready)
            mStatus = Status::Succeeded;
    }

    return mStatus != Status::Loading;
}

}  // namespace ksys::res
