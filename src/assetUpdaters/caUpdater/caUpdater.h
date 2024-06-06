#ifndef CAUPDATER_H
#define CAUPDATER_H

#include "assetStructs.h"
#include "logger.h"
#include <curl/curl.h>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <atomic>

extern std::atomic<double> usd2eurRate;

class caUpdater {
public:
    enum Result { SUCCESS = 0, FAILED_CURL_CONNECTION = 1, FETCH_ERROR = 2 };

public:
    caUpdater();

    void updateAssetsMetadata();

    void updateAssetsValue();

    caUpdater::Result fetchEuroValue(nlohmann::json &response) const;

private:
    Result fetchAssetValue(const std::string &caName, const std::string &series, const std::string &date,
                                  const double &units) const;

    bool parseCaValue(const std::string& response);      
private:
    uniqueAssetList caUniqueList;
    std::shared_ptr<logger> mLogger;
};

#endif // CAUPDATER_H
