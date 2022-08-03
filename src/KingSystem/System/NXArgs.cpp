#include "KingSystem/System/NXArgs.h"

namespace ksys {

nxargs::SingletonDisposer_::~SingletonDisposer_() { 
    if (this == sStaticDisposer) { 
        sStaticDisposer = nullptr; 
        nxargs::sInstance->~nxargs(); 
        nxargs::sInstance = nullptr; 
    } 
} 
nxargs* nxargs::createInstance(sead::Heap* heap) { 
    if (!sInstance) { 
        auto* buffer = new (heap, alignof(nxargs)) u8[sizeof(nxargs)]; 
        do { 
            if (false) { 
                static_cast<void>(!SingletonDisposer_::sStaticDisposer); 
                sead::system::detail::CheckFormat("Create Singleton Twice (%s).","nxargs"); 
            } 
        } 
        while (0); 
        auto* disposer_buffer = buffer + ((::size_t)&reinterpret_cast<char const volatile&>((((nxargs*)0)->mSingletonDisposerBuf_))); 
        SingletonDisposer_::sStaticDisposer = new (disposer_buffer) SingletonDisposer_(heap); 
        sInstance = new (buffer) nxargs; 
    } 
    else { 
        do { 
            if (false) { 
                static_cast<void>(false); 
                sead::system::detail::CheckFormat("Create Singleton Twice (%s) : addr %p","nxargs", sInstance); 
            } 
        } 
        while (0); 
    } 
    return nxargs::sInstance; 
} 
void nxargs::deleteInstance() { 
    SingletonDisposer_* staticDisposer = SingletonDisposer_::sStaticDisposer; 
    if (SingletonDisposer_::sStaticDisposer != 0) { 
        SingletonDisposer_::sStaticDisposer = 0; 
        staticDisposer->~SingletonDisposer_(); 
        delete sInstance; sInstance = 0; 
    } 
} 
nxargs* nxargs::sInstance = 0; 
nxargs::SingletonDisposer_* nxargs::SingletonDisposer_::sStaticDisposer = 0;

// WIP
void nxargs::init(sead::Heap* heap) {
    sead::SafeString heapname = "nxargsHeap";
    sead::Heap *nxargsheap = nullptr;
    char* string;
    
    nxargsheap = sead::ExpHeap::create(0x13E8, heapname, heap, (u32)8, sead::ExpHeap::HeapDirection::cHeapDirection_Reverse, false);
    nxargs::ResLaunchParamData *reslaunchdata = new (nxargsheap) nxargs::ResLaunchParamData;

    if (nn::oe::TryPopLaunchParameter(reslaunchdata, 0x1000)) {
        int len = 5;
        while (1) {
            sead::BufferedSafeString* inputmagic;
            sead::SafeString expectedmagic = "BotW";
            inputmagic->format("%s", reslaunchdata->header.magic);
            bool isMagicMatch = (inputmagic->cstr() == expectedmagic.cstr());
            if (isMagicMatch)
                break;


        }
    }


}

}