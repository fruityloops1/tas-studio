#pragma once

#include "al/audio/AudioKeeper.h"
namespace al {

bool isPlayingBgm(const al::IUseAudioKeeper*, const char*);
void pauseBgm(const al::IUseAudioKeeper*, const char*, int);
void resumeBgm(const al::IUseAudioKeeper*, const char*, int);
void startBgm(const al::IUseAudioKeeper*, const char*, int, int);
void stopBgm(const al::IUseAudioKeeper*, const char*, int);

} // namespace al