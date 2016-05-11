#include "PixelPusher.h"

PixelPusher::PixelPusher(DeviceHeader header) throw(string) : Device(header) {
    if (header.remainderLength < bodyLength) {
        throw string("PixelPusher buffer length needs 24");
    }

    uint8_t *buf = header.remainder;
    stripsAttached = buf[0];
    maxStripsPerPacket = buf[1];
    pixelsPerStrip = (buf[3] << 8) | buf[2];
    updatePeriod = (buf[7] << 24) | (buf[6] << 16) | (buf[5] << 8) | buf[4];
    powerTotal = (buf[11] << 24) | (buf[10] << 16) | (buf[9] << 8) | buf[8];
    deltaSequence = (buf[15] << 24) | (buf[14] << 16) | (buf[13] << 8) | buf[12];
    controllerOrdinal = (buf[19] << 24) | (buf[18] << 16) | (buf[17] << 8) | buf[16];
    groupOrdinal = (buf[23] << 24) | (buf[22] << 16) | (buf[21] << 8) | buf[20];

    for (int i = 0; i < stripsAttached; i++) {
        strips.push_back(new LedStrip(i, pixelsPerStrip));
    }
    packet.reserve(4 + (1 + pixelsPerStrip * 3) * stripsAttached);
}

PixelPusher::~PixelPusher() {
    for (LedStrip *strip : strips) {
        delete strip;
    }
}

bool PixelPusher::operator<(const PixelPusher &obj) const {
    if (groupOrdinal != obj.groupOrdinal) {
        return groupOrdinal < obj.groupOrdinal;
    }
    if (controllerOrdinal != obj.controllerOrdinal) {
        return controllerOrdinal < obj.controllerOrdinal;
    }
    return strcmp(header.macAddress.c_str(), obj.header.macAddress.c_str()) > 0;
}

bool PixelPusher::operator>(const PixelPusher &obj) const { return !(*this < obj); }

bool PixelPusher::operator==(const PixelPusher &obj) const {
    if (this == &obj) {
        return true;
    }
    if (pixelsPerStrip != obj.pixelsPerStrip) {
        return false;
    }
    if (strips.size() != obj.strips.size()) {
        return false;
    }
    return true;
}

bool PixelPusher::operator!=(const PixelPusher &obj) const { return !(*this == obj); }

void PixelPusher::updateProperty(PixelPusher *pusher) {
    this->maxStripsPerPacket = pusher->maxStripsPerPacket;
    this->updatePeriod = pusher->updatePeriod;
    this->powerTotal = pusher->powerTotal;
    this->deltaSequence = pusher->deltaSequence;
    this->groupOrdinal = pusher->groupOrdinal;
    this->controllerOrdinal = pusher->controllerOrdinal;
}

int PixelPusher::getStripLength() { return strips.size(); }

vector<LedStrip *> PixelPusher::getStrips() { return strips; }

vector<uint8_t> *PixelPusher::serialize() {
    packet.clear();
    packet.push_back((packetNumber >> 0) & 0xff);
    packet.push_back((packetNumber >> 8) & 0xff);
    packet.push_back((packetNumber >> 16) & 0xff);
    packet.push_back((packetNumber >> 24) & 0xff);
    for (int i = 0; i < strips.size(); i++) {
        strips[i]->serialize(packet);
    }

    if (packet.size() > 4) {
        packetNumber++;
    } else {
        packet.clear();
    }
    return &packet;
}

string PixelPusher::str() {
    string str = "{";
    str += "\"stripsAttached\":\"" + to_string((int)stripsAttached) + "\",";
    str += "\"maxStripsPerPacket\":\"" + to_string((int)maxStripsPerPacket) + "\",";
    str += "\"pixelsPerStrip\":\"" + to_string((int)pixelsPerStrip) + "\",";
    str += "\"updatePeriod\":\"" + to_string((int)updatePeriod) + "\",";
    str += "\"powerTotal\":\"" + to_string((int)powerTotal) + "\",";
    str += "\"deltaSequence\":\"" + to_string((int)deltaSequence) + "\",";
    str += "\"controllerOrdinal\":\"" + to_string((int)controllerOrdinal) + "\",";
    str += "\"groupOrdinal\":" + to_string((int)groupOrdinal);
    str += "}";
    return str;
}
