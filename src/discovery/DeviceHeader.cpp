#include "DeviceHeader.h"

DeviceHeader::DeviceHeader(uint8_t *buf, size_t length) {
    this->buf = new uint8_t[length];
    memcpy(this->buf, buf, length);
    this->length = length;
}

DeviceHeader::DeviceHeader(const DeviceHeader &obj) {
    this->buf = new uint8_t[obj.length];
    memcpy(this->buf, obj.buf, obj.length);
    this->length = obj.length;

    try {
        this->parse();
    } catch (string e) {
        cout << e;
    }
}

DeviceHeader &DeviceHeader::operator=(const DeviceHeader &obj) {
    this->buf = new uint8_t[obj.length];
    memcpy(this->buf, obj.buf, obj.length);
    this->length = obj.length;

    try {
        this->parse();
    } catch (string e) {
        cout << e;
    }

    return (*this);
}

void DeviceHeader::parse() throw(string) {
    if (length < headerLength) {
        throw string("DeviceHeader buffer length needs 24");
    }

    // mac address
    stringstream ss;
    for (int i = 0; i < 6; i++) {
        if (i > 0) {
            ss << ":";
        }
        ss << setw(2) << setfill('0') << uppercase << hex << (int)buf[i];
    }
    macAddress = ss.str();

    // ip address
    ss.str("");
    ss.clear(stringstream::goodbit);
    for (int i = 0; i < 4; i++) {
        if (i > 0) {
            ss << ".";
        }
        ss << dec << (int)buf[6 + i];
    }
    ipAddress = ss.str();

    // device type
    deviceType = getDeviceType(buf[10]);

    // other
    protocolVersion = buf[11];
    vendorId = (buf[13] << 8) | buf[12];
    productId = (buf[15] << 8) | buf[14];
    hardwareRevision = (buf[17] << 8) | buf[16];
    softwareRevision = (buf[19] << 8) | buf[18];
    linkSpeed = (buf[23] << 24) | (buf[22] << 16) | (buf[21] << 8) | buf[20];

    // reminder buffer
    remainder = &buf[headerLength];
    remainderLength = length - headerLength;
}

string DeviceHeader::str() {
    string str = "{";
    str += "\"macAddress\":\"" + macAddress + "\",";
    str += "\"ipAddress\":\"" + ipAddress + "\",";
    str += "\"deviceType\":\"" + getDeviceTypeName(deviceType) + "\",";
    str += "\"protocolVersion\":\"" + to_string((int)protocolVersion) + "\",";
    str += "\"vendorId\":\"" + to_string((int)vendorId) + "\",";
    str += "\"productId\":\"" + to_string((int)productId) + "\",";
    str += "\"hardwareRevision\":\"" + to_string((int)hardwareRevision) + "\",";
    str += "\"softwareRevision\":" + to_string((int)softwareRevision) + ",";
    str += "\"linkSpeed\":" + to_string((int)linkSpeed);
    str += "}";
    return str;
}
