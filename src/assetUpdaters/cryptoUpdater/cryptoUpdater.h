#ifndef CRYPTOUPDATER_H
#define CRYPTOUPDATER_H

#include "assetStructs.h"
#include "logger.h"
#include <curl/curl.h>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <atomic>

extern std::atomic<double> usd2eurRate;

class cryptoUpdater {
public:
    enum Result { SUCCESS = 0, FAILED_CURL_CONNECTION = 1, FETCH_ERROR = 2 };

public:
    cryptoUpdater();

    void updateAssetsMetadata();

    void updateAssetsValue();

    Result fetchAssetValue(const std::string &cryptoName, nlohmann::json &response) const;

    cryptoUpdater::Result fetchEuroValue(nlohmann::json &response) const;

private:
    uniqueAssetList cryptoUniqueList;
    std::shared_ptr<logger> mLogger;
};

#endif // CRYPTOUPDATER_H
