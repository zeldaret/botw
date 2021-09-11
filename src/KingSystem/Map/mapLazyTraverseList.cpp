#include "mapLazyTraverseList.h"

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
        hasEntries = false;
    } else {
        auto* direct_res = sead::DynamicCast<sead::DirectResource>(handle.getResource());
        if (!direct_res) {
            hasEntries = false;
        } else {
            auto* entryIter = new (heap) al::ByamlIter(direct_res->getRawData());
            if (entryIter && entryIter->getSize() >= 1) {
                hasEntries = true;

                entries.allocBufferAssert(entryIter->getSize(), heap);

                int objectCount = 0;
                for (int entryIdx = 0; entryIdx < entryIter->getSize(); ++entryIdx) {
                    const char* key;
                    entryIter->getKeyName(&key, entryIdx);

                    entries[entryIdx].flagName = key;
                    entries[entryIdx].flagValue = 0;

                    al::ByamlIter objectIter;
                    if (entryIter->tryGetIterByIndex(&objectIter, entryIdx)) {
                        objectCount += objectIter.getSize();
                    }
                }

                objects.allocBufferAssert(objectCount, heap);

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

                        kvIter.tryGetUIntByKey(&objects[object].hashId, "HashId");
                        objects[object].entryIdx = entryIdx;
                        ++object;
                    }
                }
            } else {
                hasEntries = false;
            }

            if (entryIter) {
                heap->free(entryIter);
            }
        }
    }

    handle.requestUnload();
}

LazyTraverseList::~LazyTraverseList() {
    entries.freeBuffer();
    objects.freeBuffer();
    hasEntries = false;
}

void LazyTraverseList::updateFlags() {
    for (int i = 0; i < u8(entries.size()); ++i) {
        ksys::gdt::Manager::instance()->getParamBypassPerm().get().getBool(&entries[i].flagValue,
                                                                           entries[i].flagName);
    }
}

}  // namespace ksys::map