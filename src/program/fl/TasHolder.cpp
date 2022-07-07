#include "fl/TasHolder.h"

void fl::TasHolder::update()
{
    if (!isRunning) {
        if (startPending) {
            isRunning = true;
            curFrame = 0;
            startPending = false;
        }
        return;
    }
    if (curFrame + 1 >= frames.count)
        stop();
    curFrame++;
}

void fl::TasHolder::start()
{
    isRunning = true;
}

void fl::TasHolder::stop()
{
    curFrame = 0;
    isRunning = false;
}