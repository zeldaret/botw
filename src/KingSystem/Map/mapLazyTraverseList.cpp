#include "KingSystem/Map/mapLazyTraverseList.h"

#include "Game/DLC/aocManager.h"
#include "KingSystem/GameData/gdtManager.h"

namespace ksys::map {

LazyTraverseList::LazyTraverseList(sead::Heap* heap) {
    ksys::res::Handle handle;
    sead::SafeString path = "Map/MainField/LazyTraverseList.mubin";
    ksys::res::LoadRequest request;

    if (uking::aoc::Manager::instance())
        uking::aoc::Manager::instance()->getFileDeviceForMap(&request.mAocFileDevice,
                                                             &request.mPackHandle, path);

    handle.load(path, &request);

    if (handle.checkLoadStatus()) {
        mHasEntries = false;
    } else {
        auto* direct_res = sead::DynamicCast<sead::DirectResource>(handle.getResource());
        if (!direct_res) {
            mHasEntries = false;
        } else {
            auto* entryIter = new (heap) al::ByamlIter(direct_res->getRawData());
            if (entryIter && entryIter->getSize() >= 1) {
                mHasEntries = true;

                mEntries.allocBufferAssert(entryIter->getSize(), heap);

                int objectCount = 0;
                for (int entryIdx = 0; entryIdx < entryIter->getSize(); ++entryIdx) {
                    const char* key;
                    entryIter->getKeyName(&key, entryIdx);

                    mEntries[entryIdx].flag_name = key;
                    mEntries[entryIdx].flag_value = 0;

                    al::ByamlIter objectIter;
                    if (entryIter->tryGetIterByIndex(&objectIter, entryIdx)) {
                        objectCount += objectIter.getSize();
                    }
                }

                mObjects.allocBufferAssert(objectCount, heap);

                for (int object = 0, entryIdx = 0; entryIdx < entryIter->getSize(); ++entryIdx) {
                    al::ByamlIter objectIter;
                    const char* entryName;
                    entryIter->getKeyName(&entryName, entryIdx);  // debug log?

                    if (!entryIter->tryGetIterByIndex(&objectIter, entryIdx))
                        continue;

                    for (int objectIdx = 0; objectIdx < objectIter.getSize(); ++objectIdx) {
                        al::ByamlIter kvIter;
                        if (!objectIter.tryGetIterByIndex(&kvIter, objectIdx))
                            continue;

                        const char* configName;
                        kvIter.tryGetStringByKey(&configName, "UnitConfigName");  // debug log?

                        kvIter.tryGetUIntByKey(&mObjects[object].hash_id, "HashId");
                        mObjects[object].entry_idx = entryIdx;
                        ++object;
                    }
                }
            } else {
                mHasEntries = false;
            }

            if (entryIter) {
                heap->free(entryIter);
            }
        }
    }

    handle.requestUnload();
}

LazyTraverseList::~LazyTraverseList() {
    mEntries.freeBuffer();
    mObjects.freeBuffer();
    mHasEntries = false;
}

void LazyTraverseList::updateFlags() {
    for (int i = 0; i < u8(mEntries.size()); ++i) {
        ksys::gdt::Manager::instance()->getParamBypassPerm().get().getBool(&mEntries[i].flag_value,
                                                                           mEntries[i].flag_name);
    }
}

bool LazyTraverseList::wereFlagsUpdated() {
    auto* mgr = ksys::gdt::Manager::instance();

    bool updated = false;
    for (int i = 0; i < mEntries.size(); ++i) {
        if (mgr->wasFlagNotCopied(mEntries[i].flag_name)) {
            updated = true;
            mEntries[i].flag_value = false;
        } else if (mgr->wasFlagCopied(mEntries[i].flag_name)) {
            updated = true;
            mEntries[i].flag_value = true;
        }
    }

    return updated;
}

}  // namespace ksys::map
