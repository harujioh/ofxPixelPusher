#pragma once

#include <string>

namespace DeviceDiscovery {

/**
 * デバイスの種類
 */
enum DeviceType {
    ETHERDREAM = 0,

    LUMIABRIDGE = 1,

    PIXELPUSHER = 2,

    OTHER
};

/**
 * デバイスの種類を取得
 */
inline DeviceType getDeviceType(int num) {
    switch (num) {
        case 0:
            return ETHERDREAM;
        case 1:
            return LUMIABRIDGE;
        case 2:
            return PIXELPUSHER;
        default:
            return OTHER;
    }
}

/**
 * デバイスの種類名を取得
 */
inline std::string getDeviceTypeName(DeviceType type) {
    switch (type) {
        case ETHERDREAM:
            return std::string("ETHERDREAM");
        case LUMIABRIDGE:
            return std::string("LUMIABRIDGE");
        case PIXELPUSHER:
            return std::string("PIXELPUSHER");
        case OTHER:
        default:
            return "OTHER";
    }
}
}