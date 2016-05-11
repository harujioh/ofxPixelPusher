#pragma once

#include "DeviceHeader.h"

/**
 * デバイスの抽象クラス
 */
class Device {
   public:
    Device(DeviceHeader header) : header(header) {}
    virtual ~Device(){};

    /**
     * MACアドレスを取得
     */
    string getMacAddress() { return header.macAddress; }

    /**
     * IPアドレスを取得
     */
    string getIpAddress() { return header.ipAddress; }

    /**
     * デバイスの種類を取得
     */
    DeviceType getDeviceType() { return header.deviceType; }

    /**
     * プロトコルバージョンを取得
     */
    int getProtocolVersion() { return header.protocolVersion; }

    /**
     * 製造元IDを取得
     */
    int getVendorId() { return header.vendorId; }

    /**
     * 製品IDを取得
     */
    int getProductId() { return header.productId; }

    /**
     * ハードウェアリビジョンを取得
     */
    int getHardwareRevision() { return header.hardwareRevision; }

    /**
     * ソフトウェアリビジョンを取得
     */
    int getSoftwareRevision() { return header.softwareRevision; }

    /**
     * リンク速度を取得
     */
    long getLinkSpeed() { return header.linkSpeed; }

    /**
     * ヘッダ情報を取得
     */
    DeviceHeader &getHeader() { return header; }

    /**
     * ヘッダ情報を取得
     */
    string getHeaderDescription() { return header.str(); }

   protected:
    /**
     * ヘッダ情報
     */
    DeviceHeader header;
};