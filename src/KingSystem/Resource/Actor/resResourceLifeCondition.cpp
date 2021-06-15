#include "KingSystem/Resource/Actor/resResourceLifeCondition.h"

namespace ksys::res {

// NON_MATCHING: two instructions swapped
bool LifeCondition::parse_(u8* data, size_t, sead::Heap* heap) {
    if (!data)
        return true;

    applyResParameterArchive(agl::utl::ResParameterArchive{data});
    const agl::utl::ResParameterArchive archive{data};
    const auto root = archive.getRootList();

    const auto invalid_weathers_obj = agl::utl::getResParameterObj(root, "InvalidWeathers");
    if (invalid_weathers_obj.ptr())
        LifeCondition::parseArray(&invalid_weathers_obj, &mInvalidWeathersObj,
                                  &mInvalidWeathersBuffer, "InvalidWeathers", "天候", heap);

    const auto invalid_times_obj = agl::utl::getResParameterObj(root, "InvalidTimes");
    if (invalid_times_obj.ptr())
        LifeCondition::parseArray(&invalid_times_obj, &mInvalidTimesObj, &mInvalidTimesBuffer,
                                  "InvalidTimes", "時間", heap);

    const auto display_distance_obj = agl::utl::getResParameterObj(root, "DisplayDistance");
    if (display_distance_obj.ptr()) {
        mDisplayDistance.init(0.0, "Item", "表示距離", &mDisplayDistanceObj);
        addObj(&mDisplayDistanceObj, "DisplayDistance");
        mDisplayDistanceObj.applyResParameterObj(display_distance_obj);
    }

    const auto auto_display_distance_algorithm_obj =
        agl::utl::getResParameterObj(root, "AutoDisplayDistanceAlgorithm");
    if (auto_display_distance_algorithm_obj.ptr()) {
        mBoundingY.init("Bouding.Y", "Item", "自動距離算出アルゴリズム", &mBoundingYObj);
        addObj(&mBoundingYObj, "AutoDisplayDistanceAlgorithm");
        mBoundingYObj.applyResParameterObj(auto_display_distance_algorithm_obj);
    }

    const auto y_limit_algorithm_obj = agl::utl::getResParameterObj(root, "YLimitAlgorithm");
    if (y_limit_algorithm_obj.ptr()) {
        mYLimitAlgorithm.init("NoLimit", "Item", "Y制限アルゴリズム", &mYLimitAlgorithmObj);
        addObj(&mYLimitAlgorithmObj, "YLimitAlgorithm");
        mYLimitAlgorithmObj.applyResParameterObj(y_limit_algorithm_obj);
    }

    const auto delete_weathers_obj = agl::utl::getResParameterObj(root, "DeleteWeathers");
    if (delete_weathers_obj.ptr())
        LifeCondition::parseArray(&delete_weathers_obj, &mDeleteWeathersObj, &mDeleteWeathersBuffer,
                                  "DeleteWeathers", "天候", heap);

    const auto delete_times_obj = agl::utl::getResParameterObj(root, "DeleteTimes");
    if (delete_times_obj.ptr())
        LifeCondition::parseArray(&delete_times_obj, &mDeleteTimesObj, &mDeleteTimesBuffer,
                                  "DeleteTimes", "時間", heap);

    return true;
}

void LifeCondition::parseArray(const agl::utl::ResParameterObj* data, agl::utl::IParameterObj* obj,
                               sead::Buffer<agl::utl::Parameter<sead::SafeString>>* buffer,
                               const sead::SafeString& key, const sead::SafeString& desc,
                               sead::Heap* heap) {
    addObj(obj, key);
    obj->applyResParameterObj(*data);

    auto count = data->mPtr->getNumParameters();
    if (count == 0)
        return;

    buffer->allocBufferAssert(count, heap);

    for (int i = 0; i != count; ++i) {
        sead::FormatFixedSafeString<64> s;
        s.format("Item%03d", (i + 1));

        (*buffer)[i].init("", s, desc, obj);
    }

    obj->applyResParameterObj(*data);
}

}  // namespace ksys::res
