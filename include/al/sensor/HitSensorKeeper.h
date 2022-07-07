#pragma once

namespace al {

class HitSensor;
class HitSensorKeeper {
public:
    al::HitSensor* getSensor(int index) const;
    al::HitSensor* getSensor(const char*) const;
};

};