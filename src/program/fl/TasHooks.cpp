#include "al/util.hpp"
#include "fl/TasHolder.h"
#include "lib.hpp"
#include "patch/code_patcher.hpp"

#define PADTRIGGER(BUTTON, PNAME)                                                           \
    static bool fisPadTrigger##BUTTON(int port)                                             \
    {                                                                                       \
        fl::TasHolder& h = fl::TasHolder::instance();                                       \
        if (h.isRunning) {                                                                  \
            if (h.curFrame == 0)                                                            \
                return h.frames.data[0].PNAME;                                              \
            return !h.frames.data[h.curFrame - 1].PNAME && h.frames.data[h.curFrame].PNAME; \
        } else                                                                              \
            return al::isPadTrigger##BUTTON(port);                                          \
    }

#define PADHOLD(BUTTON, PNAME)                        \
    static bool fisPadHold##BUTTON(int port)          \
    {                                                 \
        fl::TasHolder& h = fl::TasHolder::instance(); \
        if (h.isRunning) {                            \
            if (h.curFrame == 0)                      \
                return h.frames.data[0].PNAME;        \
            return h.frames.data[h.curFrame].PNAME;   \
        } else                                        \
            return al::isPadHold##BUTTON(port);       \
    }

#define PADRELEASE(BUTTON, PNAME)                                                           \
    static bool fisPadRelease##BUTTON(int port)                                             \
    {                                                                                       \
        fl::TasHolder& h = fl::TasHolder::instance();                                       \
        if (h.isRunning) {                                                                  \
            if (h.curFrame == 0)                                                            \
                return false;                                                               \
            return h.frames.data[h.curFrame - 1].PNAME && !h.frames.data[h.curFrame].PNAME; \
        } else                                                                              \
            return al::isPadRelease##BUTTON(port);                                          \
    }

MAKE_HOOK_T(sead::Vector2f*, fgetLeftStick, (int port), {
    fl::TasHolder& h = fl::TasHolder::instance();
    if (h.isRunning)
        return &h.frames.data[h.curFrame].leftStick;
    else
        return impl(port);
});

MAKE_HOOK_T(sead::Vector2f*, fgetRightStick, (int port), {
    fl::TasHolder& h = fl::TasHolder::instance();
    if (h.isRunning)
        return &h.frames.data[h.curFrame].rightStick;
    else
        return impl(port);
});

PADTRIGGER(A, A);
PADTRIGGER(B, B);
PADTRIGGER(X, X);
PADTRIGGER(Y, Y);
PADTRIGGER(L, L);
PADTRIGGER(R, R);
PADTRIGGER(ZL, ZL);
PADTRIGGER(ZR, ZR);
PADTRIGGER(PressLeftStick, pressLeftStick);
PADTRIGGER(PressRightStick, pressRightStick);
PADTRIGGER(Plus, plus);
PADTRIGGER(Minus, minus);
PADTRIGGER(Up, dUp);
PADTRIGGER(Right, dRight);
PADTRIGGER(Down, dDown);
PADTRIGGER(Left, dLeft);
PADTRIGGER(UiCursorUp, dUp);
PADTRIGGER(UiCursorRight, dRight);
PADTRIGGER(UiCursorDown, dDown);
PADTRIGGER(UiCursorLeft, dLeft);

PADHOLD(A, A);
PADHOLD(B, B);
PADHOLD(X, X);
PADHOLD(Y, Y);
PADHOLD(L, L);
PADHOLD(R, R);
PADHOLD(ZL, ZL);
PADHOLD(ZR, ZR);
PADHOLD(PressLeftStick, pressLeftStick);
PADHOLD(PressRightStick, pressRightStick);
PADHOLD(Plus, plus);
PADHOLD(Minus, minus);
PADHOLD(Up, dUp);
PADHOLD(Right, dRight);
PADHOLD(Down, dDown);
PADHOLD(Left, dLeft);
PADHOLD(UiCursorUp, dUp);
PADHOLD(UiCursorRight, dRight);
PADHOLD(UiCursorDown, dDown);
PADHOLD(UiCursorLeft, dLeft);

PADRELEASE(A, A);
PADRELEASE(B, B);
PADRELEASE(X, X);
PADRELEASE(Y, Y);
PADRELEASE(L, L);
PADRELEASE(R, R);
PADRELEASE(ZL, ZL);
PADRELEASE(ZR, ZR);
PADRELEASE(PressLeftStick, pressLeftStick);
PADRELEASE(PressRightStick, pressRightStick);
PADRELEASE(Plus, plus);
PADRELEASE(Minus, minus);
PADRELEASE(Up, dUp);
PADRELEASE(Right, dRight);
PADRELEASE(Down, dDown);
PADRELEASE(Left, dLeft);
PADRELEASE(UiCursorUp, dUp);
PADRELEASE(UiCursorRight, dRight);
PADRELEASE(UiCursorDown, dDown);
PADRELEASE(UiCursorLeft, dLeft);

namespace fl {

void initTasInputHooks()
{
    exl::patch::CodePatcher(0x0045022c).BranchInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x00450234).BranchInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x0056e260).BranchInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x00575be4).BranchInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x00575bf4).BranchInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x00575c2c).BranchInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x00575c3c).BranchInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x00576ae8).BranchInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x00576af8).BranchInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x00414000).BranchLinkInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x004140f8).BranchLinkInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x004142c4).BranchLinkInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x0044fe94).BranchLinkInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x004fd988).BranchLinkInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x0050bcf0).BranchLinkInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x0050bd8c).BranchLinkInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x0050c218).BranchLinkInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x0050c620).BranchLinkInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x00575bc8).BranchLinkInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x00575c10).BranchLinkInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x00576acc).BranchLinkInst((void*)&fisPadTriggerA);
    exl::patch::CodePatcher(0x00450790).BranchInst((void*)&fisPadHoldA);
    exl::patch::CodePatcher(0x00573594).BranchInst((void*)&fisPadHoldA);
    exl::patch::CodePatcher(0x005765a4).BranchInst((void*)&fisPadHoldA);
    exl::patch::CodePatcher(0x0044fed0).BranchLinkInst((void*)&fisPadHoldA);
    exl::patch::CodePatcher(0x00450448).BranchLinkInst((void*)&fisPadHoldA);
    exl::patch::CodePatcher(0x00576554).BranchLinkInst((void*)&fisPadHoldA);
    exl::patch::CodePatcher(0x0044ff0c).BranchLinkInst((void*)&fisPadReleaseA);
    exl::patch::CodePatcher(0x0044feb8).BranchInst((void*)&fisPadTriggerB);
    exl::patch::CodePatcher(0x0056e23c).BranchInst((void*)&fisPadTriggerB);
    exl::patch::CodePatcher(0x00575cb8).BranchInst((void*)&fisPadTriggerB);
    exl::patch::CodePatcher(0x00450250).BranchLinkInst((void*)&fisPadTriggerB);
    exl::patch::CodePatcher(0x0050bcb8).BranchLinkInst((void*)&fisPadTriggerB);
    exl::patch::CodePatcher(0x00575c68).BranchLinkInst((void*)&fisPadTriggerB);
    exl::patch::CodePatcher(0x0044fef4).BranchInst((void*)&fisPadHoldB);
    exl::patch::CodePatcher(0x00576620).BranchInst((void*)&fisPadHoldB);
    exl::patch::CodePatcher(0x005765d0).BranchLinkInst((void*)&fisPadHoldB);
    exl::patch::CodePatcher(0x0044ff30).BranchInst((void*)&fisPadReleaseB);
    exl::patch::CodePatcher(0x004502b0).BranchInst((void*)&fisPadTriggerX);
    exl::patch::CodePatcher(0x00450594).BranchInst((void*)&fisPadTriggerX);
    exl::patch::CodePatcher(0x0056e1ac).BranchInst((void*)&fisPadTriggerX);
    exl::patch::CodePatcher(0x00576240).BranchInst((void*)&fisPadTriggerX);
    exl::patch::CodePatcher(0x0044ff68).BranchLinkInst((void*)&fisPadTriggerX);
    exl::patch::CodePatcher(0x004fd9b0).BranchLinkInst((void*)&fisPadTriggerX);
    exl::patch::CodePatcher(0x0050bd5c).BranchLinkInst((void*)&fisPadTriggerX);
    exl::patch::CodePatcher(0x0050be1c).BranchLinkInst((void*)&fisPadTriggerX);
    exl::patch::CodePatcher(0x005761f0).BranchLinkInst((void*)&fisPadTriggerX);
    exl::patch::CodePatcher(0x00450740).BranchInst((void*)&fisPadHoldX);
    exl::patch::CodePatcher(0x0056e1f4).BranchInst((void*)&fisPadHoldX);
    exl::patch::CodePatcher(0x00573558).BranchInst((void*)&fisPadHoldX);
    exl::patch::CodePatcher(0x0044ffc4).BranchLinkInst((void*)&fisPadHoldX);
    exl::patch::CodePatcher(0x0045030c).BranchLinkInst((void*)&fisPadHoldX);
    exl::patch::CodePatcher(0x004503a8).BranchLinkInst((void*)&fisPadHoldX);
    exl::patch::CodePatcher(0x00450534).BranchLinkInst((void*)&fisPadHoldX);
    exl::patch::CodePatcher(0x00450890).BranchLinkInst((void*)&fisPadHoldX);
    exl::patch::CodePatcher(0x00576b38).BranchLinkInst((void*)&fisPadHoldX);
    exl::patch::CodePatcher(0x00576ba8).BranchLinkInst((void*)&fisPadHoldX);
    exl::patch::CodePatcher(0x00576c44).BranchLinkInst((void*)&fisPadHoldX);
    exl::patch::CodePatcher(0x00576cbc).BranchLinkInst((void*)&fisPadHoldX);
    exl::patch::CodePatcher(0x00450608).BranchInst((void*)&fisPadReleaseX);
    exl::patch::CodePatcher(0x00450020).BranchLinkInst((void*)&fisPadReleaseX);
    exl::patch::CodePatcher(0x0044ff8c).BranchInst((void*)&fisPadTriggerY);
    exl::patch::CodePatcher(0x0056e1d0).BranchInst((void*)&fisPadTriggerY);
    exl::patch::CodePatcher(0x005762bc).BranchInst((void*)&fisPadTriggerY);
    exl::patch::CodePatcher(0x00576e78).BranchInst((void*)&fisPadTriggerY);
    exl::patch::CodePatcher(0x00577134).BranchInst((void*)&fisPadTriggerY);
    exl::patch::CodePatcher(0x00450264).BranchLinkInst((void*)&fisPadTriggerY);
    exl::patch::CodePatcher(0x004fd9dc).BranchLinkInst((void*)&fisPadTriggerY);
    exl::patch::CodePatcher(0x0050bd28).BranchLinkInst((void*)&fisPadTriggerY);
    exl::patch::CodePatcher(0x0050bdd4).BranchLinkInst((void*)&fisPadTriggerY);
    exl::patch::CodePatcher(0x0057626c).BranchLinkInst((void*)&fisPadTriggerY);
    exl::patch::CodePatcher(0x00576e2c).BranchLinkInst((void*)&fisPadTriggerY);
    exl::patch::CodePatcher(0x00576ebc).BranchLinkInst((void*)&fisPadTriggerY);
    exl::patch::CodePatcher(0x00576ec8).BranchLinkInst((void*)&fisPadTriggerY);
    exl::patch::CodePatcher(0x00576f00).BranchLinkInst((void*)&fisPadTriggerY);
    exl::patch::CodePatcher(0x0044ffe8).BranchInst((void*)&fisPadHoldY);
    exl::patch::CodePatcher(0x0056e218).BranchInst((void*)&fisPadHoldY);
    exl::patch::CodePatcher(0x00576808).BranchInst((void*)&fisPadHoldY);
    exl::patch::CodePatcher(0x0045041c).BranchLinkInst((void*)&fisPadHoldY);
    exl::patch::CodePatcher(0x005767b8).BranchLinkInst((void*)&fisPadHoldY);
    exl::patch::CodePatcher(0x00450044).BranchInst((void*)&fisPadReleaseY);
    exl::patch::CodePatcher(0x005760cc).BranchInst((void*)&fisPadTriggerL);
    exl::patch::CodePatcher(0x004143d8).BranchLinkInst((void*)&fisPadTriggerL);
    exl::patch::CodePatcher(0x0045007c).BranchLinkInst((void*)&fisPadTriggerL);
    exl::patch::CodePatcher(0x00573454).BranchLinkInst((void*)&fisPadTriggerL);
    exl::patch::CodePatcher(0x0057607c).BranchLinkInst((void*)&fisPadTriggerL);
    exl::patch::CodePatcher(0x0084003c).BranchLinkInst((void*)&fisPadTriggerL);
    exl::patch::CodePatcher(0x0056e2b4).BranchInst((void*)&fisPadHoldL);
    exl::patch::CodePatcher(0x00576710).BranchInst((void*)&fisPadHoldL);
    exl::patch::CodePatcher(0x004500f4).BranchLinkInst((void*)&fisPadHoldL);
    exl::patch::CodePatcher(0x004501e4).BranchLinkInst((void*)&fisPadHoldL);
    exl::patch::CodePatcher(0x00450334).BranchLinkInst((void*)&fisPadHoldL);
    exl::patch::CodePatcher(0x004503c0).BranchLinkInst((void*)&fisPadHoldL);
    exl::patch::CodePatcher(0x004508c8).BranchLinkInst((void*)&fisPadHoldL);
    exl::patch::CodePatcher(0x005766c0).BranchLinkInst((void*)&fisPadHoldL);
    exl::patch::CodePatcher(0x0045016c).BranchLinkInst((void*)&fisPadReleaseL);
    exl::patch::CodePatcher(0x00450090).BranchInst((void*)&fisPadTriggerR);
    exl::patch::CodePatcher(0x004505c0).BranchInst((void*)&fisPadTriggerR);
    exl::patch::CodePatcher(0x0045062c).BranchInst((void*)&fisPadTriggerR);
    exl::patch::CodePatcher(0x0056e2d8).BranchInst((void*)&fisPadTriggerR);
    exl::patch::CodePatcher(0x00573478).BranchInst((void*)&fisPadTriggerR);
    exl::patch::CodePatcher(0x00576050).BranchInst((void*)&fisPadTriggerR);
    exl::patch::CodePatcher(0x00840060).BranchInst((void*)&fisPadTriggerR);
    exl::patch::CodePatcher(0x0050bd74).BranchLinkInst((void*)&fisPadTriggerR);
    exl::patch::CodePatcher(0x0050bdbc).BranchLinkInst((void*)&fisPadTriggerR);
    exl::patch::CodePatcher(0x0050be04).BranchLinkInst((void*)&fisPadTriggerR);
    exl::patch::CodePatcher(0x00576000).BranchLinkInst((void*)&fisPadTriggerR);
    exl::patch::CodePatcher(0x00450108).BranchInst((void*)&fisPadHoldR);
    exl::patch::CodePatcher(0x004501f8).BranchInst((void*)&fisPadHoldR);
    exl::patch::CodePatcher(0x004503e4).BranchInst((void*)&fisPadHoldR);
    exl::patch::CodePatcher(0x0057678c).BranchInst((void*)&fisPadHoldR);
    exl::patch::CodePatcher(0x00450340).BranchLinkInst((void*)&fisPadHoldR);
    exl::patch::CodePatcher(0x004508d4).BranchLinkInst((void*)&fisPadHoldR);
    exl::patch::CodePatcher(0x0050bd80).BranchLinkInst((void*)&fisPadHoldR);
    exl::patch::CodePatcher(0x0050bdc8).BranchLinkInst((void*)&fisPadHoldR);
    exl::patch::CodePatcher(0x0050be10).BranchLinkInst((void*)&fisPadHoldR);
    exl::patch::CodePatcher(0x0050c224).BranchLinkInst((void*)&fisPadHoldR);
    exl::patch::CodePatcher(0x0050c644).BranchLinkInst((void*)&fisPadHoldR);
    exl::patch::CodePatcher(0x0057673c).BranchLinkInst((void*)&fisPadHoldR);
    exl::patch::CodePatcher(0x00450180).BranchInst((void*)&fisPadReleaseR);
    exl::patch::CodePatcher(0x0056e57c).BranchInst((void*)&fisPadTriggerZL);
    exl::patch::CodePatcher(0x005761c4).BranchInst((void*)&fisPadTriggerZL);
    exl::patch::CodePatcher(0x0044d89c).BranchLinkInst((void*)&fisPadTriggerZL);
    exl::patch::CodePatcher(0x0044d8ec).BranchLinkInst((void*)&fisPadTriggerZL);
    exl::patch::CodePatcher(0x00450098).BranchLinkInst((void*)&fisPadTriggerZL);
    exl::patch::CodePatcher(0x00576174).BranchLinkInst((void*)&fisPadTriggerZL);
    exl::patch::CodePatcher(0x004507e0).BranchInst((void*)&fisPadHoldZL);
    exl::patch::CodePatcher(0x005735d0).BranchInst((void*)&fisPadHoldZL);
    exl::patch::CodePatcher(0x008400a4).BranchInst((void*)&fisPadHoldZL);
    exl::patch::CodePatcher(0x00450110).BranchLinkInst((void*)&fisPadHoldZL);
    exl::patch::CodePatcher(0x00450200).BranchLinkInst((void*)&fisPadHoldZL);
    exl::patch::CodePatcher(0x004506cc).BranchLinkInst((void*)&fisPadHoldZL);
    exl::patch::CodePatcher(0x005734f8).BranchLinkInst((void*)&fisPadHoldZL);
    exl::patch::CodePatcher(0x00840078).BranchLinkInst((void*)&fisPadHoldZL);
    exl::patch::CodePatcher(0x00450188).BranchLinkInst((void*)&fisPadReleaseZL);
    exl::patch::CodePatcher(0x0044d8c0).BranchInst((void*)&fisPadTriggerZR);
    exl::patch::CodePatcher(0x0044d910).BranchInst((void*)&fisPadTriggerZR);
    exl::patch::CodePatcher(0x004500bc).BranchInst((void*)&fisPadTriggerZR);
    exl::patch::CodePatcher(0x0056e5c4).BranchInst((void*)&fisPadTriggerZR);
    exl::patch::CodePatcher(0x00576148).BranchInst((void*)&fisPadTriggerZR);
    exl::patch::CodePatcher(0x0050bca0).BranchLinkInst((void*)&fisPadTriggerZR);
    exl::patch::CodePatcher(0x0050bcd8).BranchLinkInst((void*)&fisPadTriggerZR);
    exl::patch::CodePatcher(0x0050bd10).BranchLinkInst((void*)&fisPadTriggerZR);
    exl::patch::CodePatcher(0x0050bd44).BranchLinkInst((void*)&fisPadTriggerZR);
    exl::patch::CodePatcher(0x0050be34).BranchLinkInst((void*)&fisPadTriggerZR);
    exl::patch::CodePatcher(0x005760f8).BranchLinkInst((void*)&fisPadTriggerZR);
    exl::patch::CodePatcher(0x00450134).BranchInst((void*)&fisPadHoldZR);
    exl::patch::CodePatcher(0x00450214).BranchInst((void*)&fisPadHoldZR);
    exl::patch::CodePatcher(0x004506f0).BranchInst((void*)&fisPadHoldZR);
    exl::patch::CodePatcher(0x00450830).BranchInst((void*)&fisPadHoldZR);
    exl::patch::CodePatcher(0x0057351c).BranchInst((void*)&fisPadHoldZR);
    exl::patch::CodePatcher(0x0057360c).BranchInst((void*)&fisPadHoldZR);
    exl::patch::CodePatcher(0x0084009c).BranchInst((void*)&fisPadHoldZR);
    exl::patch::CodePatcher(0x008400ac).BranchInst((void*)&fisPadHoldZR);
    exl::patch::CodePatcher(0x0050bc48).BranchLinkInst((void*)&fisPadHoldZR);
    exl::patch::CodePatcher(0x0050bcac).BranchLinkInst((void*)&fisPadHoldZR);
    exl::patch::CodePatcher(0x0050bd1c).BranchLinkInst((void*)&fisPadHoldZR);
    exl::patch::CodePatcher(0x0050bd50).BranchLinkInst((void*)&fisPadHoldZR);
    exl::patch::CodePatcher(0x0050be40).BranchLinkInst((void*)&fisPadHoldZR);
    exl::patch::CodePatcher(0x0050c230).BranchLinkInst((void*)&fisPadHoldZR);
    exl::patch::CodePatcher(0x0050c650).BranchLinkInst((void*)&fisPadHoldZR);
    exl::patch::CodePatcher(0x004501ac).BranchInst((void*)&fisPadReleaseZR);
    exl::patch::CodePatcher(0x0045068c).BranchInst((void*)&fisPadTriggerPressRightStick);
    exl::patch::CodePatcher(0x0056e2fc).BranchInst((void*)&fisPadTriggerPressRightStick);
    exl::patch::CodePatcher(0x005734b4).BranchInst((void*)&fisPadTriggerPressRightStick);
    exl::patch::CodePatcher(0x004d648c).BranchLinkInst((void*)&fisPadTriggerPressRightStick);
    exl::patch::CodePatcher(0x004d7420).BranchLinkInst((void*)&fisPadTriggerPressRightStick);
    exl::patch::CodePatcher(0x00575d14).BranchInst((void*)&fisPadTriggerPlus);
    exl::patch::CodePatcher(0x00575de4).BranchInst((void*)&fisPadTriggerPlus);
    exl::patch::CodePatcher(0x00576678).BranchInst((void*)&fisPadTriggerPlus);
    exl::patch::CodePatcher(0x00576d88).BranchInst((void*)&fisPadTriggerPlus);
    exl::patch::CodePatcher(0x0050be4c).BranchLinkInst((void*)&fisPadTriggerPlus);
    exl::patch::CodePatcher(0x00575db8).BranchLinkInst((void*)&fisPadTriggerPlus);
    exl::patch::CodePatcher(0x0050bc54).BranchLinkInst((void*)&fisPadHoldPlus);
    exl::patch::CodePatcher(0x00575d04).BranchInst((void*)&fisPadTriggerMinus);
    exl::patch::CodePatcher(0x00576694).BranchInst((void*)&fisPadTriggerMinus);
    exl::patch::CodePatcher(0x00576db4).BranchInst((void*)&fisPadTriggerMinus);
    exl::patch::CodePatcher(0x00575d84).BranchLinkInst((void*)&fisPadTriggerMinus);
    exl::patch::CodePatcher(0x00576a94).BranchLinkInst((void*)&fisPadTriggerMinus);
    exl::patch::CodePatcher(0x00576d74).BranchLinkInst((void*)&fisPadTriggerMinus);
    exl::patch::CodePatcher(0x00576d90).BranchLinkInst((void*)&fisPadTriggerMinus);
    exl::patch::CodePatcher(0x00576f2c).BranchLinkInst((void*)&fisPadTriggerMinus);
    exl::patch::CodePatcher(0x0050c360).BranchLinkInst((void*)&fisPadTriggerUp);
    exl::patch::CodePatcher(0x00576a68).BranchLinkInst((void*)&fisPadTriggerUp);
    exl::patch::CodePatcher(0x009a38a8).BranchLinkInst((void*)&fisPadHoldUp);
    exl::patch::CodePatcher(0x009a390c).BranchLinkInst((void*)&fisPadHoldUp);
    exl::patch::CodePatcher(0x00577074).BranchInst((void*)&fisPadTriggerRight);
    exl::patch::CodePatcher(0x00577200).BranchInst((void*)&fisPadTriggerRight);
    exl::patch::CodePatcher(0x0057720c).BranchInst((void*)&fisPadTriggerRight);
    exl::patch::CodePatcher(0x005770d4).BranchInst((void*)&fisPadHoldRight);
    exl::patch::CodePatcher(0x009a38cc).BranchLinkInst((void*)&fisPadHoldRight);
    exl::patch::CodePatcher(0x009a38fc).BranchLinkInst((void*)&fisPadHoldRight);
    exl::patch::CodePatcher(0x00577014).BranchInst((void*)&fisPadTriggerDown);
    exl::patch::CodePatcher(0x0050c4b8).BranchLinkInst((void*)&fisPadTriggerDown);
    exl::patch::CodePatcher(0x009a38b4).BranchLinkInst((void*)&fisPadHoldDown);
    exl::patch::CodePatcher(0x009a3928).BranchLinkInst((void*)&fisPadHoldDown);
    exl::patch::CodePatcher(0x00577234).BranchInst((void*)&fisPadTriggerLeft);
    exl::patch::CodePatcher(0x00577240).BranchInst((void*)&fisPadTriggerLeft);
    exl::patch::CodePatcher(0x009a38c0).BranchLinkInst((void*)&fisPadHoldLeft);
    exl::patch::CodePatcher(0x009a38dc).BranchLinkInst((void*)&fisPadHoldLeft);

    INJECT_HOOK_T(al::getLeftStick, fgetLeftStick);
    INJECT_HOOK_T(al::getRightStick, fgetRightStick);
}

} // namespace fl