#pragma once

#include <stdint.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "DeviceType.h"

using namespace std;
using namespace DeviceDiscovery;

/**
 * デバイスのヘッダ情報
 */
class DeviceHeader {
   public:
    DeviceHeader() {}
    DeviceHeader(uint8_t *buf, size_t length);

    /**
     * コピーコンストラクタ
     */
    DeviceHeader(const DeviceHeader &obj);

    ~DeviceHeader() { delete[] buf; };

    /**
     * 代入演算
     */
    DeviceHeader &operator=(const DeviceHeader &obj);

    /**
     * パケットを解析する
     */
    void parse() throw(string);

    /**
     * 文字列として取得する
     */
    string str();

    /**
     * MACアドレス
     */
    string macAddress;

    /**
     * IPアドレス
     */
    string ipAddress;

    /**
     * デバイスの種類
     */
    DeviceType deviceType;

    /**
     * プロトコルバージョン
     */
    uint8_t protocolVersion;

    /**
     * 製造元ID
     */
    uint16_t vendorId;

    /**
     * 製品ID
     */
    uint16_t productId;

    /**
     * ハードウェアリビジョン
     */
    uint16_t hardwareRevision;

    /**
     * ソフトウェアリビジョン
     */
    uint16_t softwareRevision;

    /**
     * リンクスピード
     */
    uint32_t linkSpeed;

    /**
     * 残パケット
     */
    uint8_t *remainder;

    /**
     * 残パケット長
     */
    size_t remainderLength = 0;

   private:
    /**
     * ヘッダに使用されるパケット長
     * uint8_t macAddress[6]
     * uint8_t ipAddress[4]
     * uint8_t deviceType
     * uint8_t protocolVersion
     * uint16_t vendorId
     * uint16_t productId
     * uint16_t hwRevision
     * uint16_t swRevision
     * uint32_t linkSpeed
     */
    const int headerLength = 24;

    /**
     * バッファ
     */
    uint8_t *buf = NULL;

    /**
     * バッファ長
     */
    size_t length = 0;
};