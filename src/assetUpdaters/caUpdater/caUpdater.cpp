#include "caUpdater.h"

caUpdater::caUpdater() { mLogger = std::make_shared<logger>(); }

void caUpdater::updateAssetsMetadata() { caUniqueList["CA"] = uniqueAssetData(1, 1000, "E", "2020-06-12"); }

void caUpdater::updateAssetsValue() {
    updateAssetsMetadata();
    for (const auto &[caName, caData] : caUniqueList) {
        switch (fetchAssetValue(caName, caData.mType, caData.mTimeAquired, caData.mUnits)) {
        case SUCCESS:

            break;

        default:
            break;
        }
    }
}

caUpdater::Result caUpdater::fetchAssetValue(const std::string &caName, const std::string &series,
                                             const std::string &date, const double &units) const {
    CURL *curl;
    CURLcode res;
    std::string curlResponse;
    // Initialize libcurl
    curl = curl_easy_init();

    std::string request = "https://www.igcp.pt/pt/aforro/";
    if (caName == "CA") {
        request += "simulacao.php?serie=" + series + "&data=" + date +
                   "&uni=" + std::to_string(static_cast<int>(units)) + "&a=&m=&d=";
    }
    mLogger->logInfo(request.c_str());
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_USERAGENT,
                     "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) "
                     "Chrome/58.0.3029.110 Safari/537.36");

    // Set the callback function to handle the curlResponse
    curl_easy_setopt(
        curl, CURLOPT_WRITEFUNCTION, +[](void *contents, size_t size, size_t nmemb, std::string *output) -> size_t {
            size_t total_size = size * nmemb;
            output->append(static_cast<char *>(contents), total_size);
            return total_size;
        });
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlResponse);
    if (!curl) {
        mLogger->logError("Unable to initialize curl");
        return FAILED_CURL_CONNECTION;
    }
    curl_easy_setopt(curl, CURLOPT_URL, (request).c_str());
    // Perform the HTTP GET request
    res = curl_easy_perform(curl);
    // Check for errors
    if (res != CURLE_OK) {
        mLogger->logError("curl_easy_perform() failed: %s",curl_easy_strerror(res));
        return FETCH_ERROR;
    } else {
        mLogger->logInfo("Successful response received");
        return SUCCESS;
    }

    return FETCH_ERROR;
}