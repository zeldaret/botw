/**
 * @file vi.h
 * @brief Visual interface implementation.
 */

#pragma once

#include <nn/types.h>

namespace nn {

namespace os {
struct SystemEventType;
}

namespace vi {
class Display;
class Layer;
class NativWindow;
struct DisplayInfo {
    static const int maxNameLen = 64;
    char name[maxNameLen];
    bool hasLayerLimit;
    int64_t maxLayers;
    int64_t maxWidth;
    int64_t maxHeight;
};

enum ScalingMode { None, Exact, FitLayer, ScaleAndCrop, PreserveAspectRatio };

void Initialize();
Result OpenDefaultDisplay(nn::vi::Display** outDisp);
Result CreateLayer(nn::vi::Layer** outLayer, nn::vi::Display* disp);
Result SetLayerScalingMode(nn::vi::Layer* layer, nn::vi::ScalingMode scalingMode);
Result GetDisplayVsyncEvent(nn::os::SystemEventType*, nn::vi::Display*);
Result GetNativeWindow(void** window, nn::vi::Layer*);
Result GetLatestFrameNumber(u64* pOutFrameNumber, const Layer* pLayer);
int ListDisplays(DisplayInfo* outDisplays, int count);
};  // namespace vi
};  // namespace nn