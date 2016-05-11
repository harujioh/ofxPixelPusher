#include "DeviceRegistryEvent.h"

vector<LedStrip *> DeviceRegistryEvent::getStrips() { return deviceRegistry->getStrips(); }

vector<LedStrip *> DeviceRegistryEvent::getStrips(int groupIndex) { return deviceRegistry->getStrips(groupIndex); }