#include "cryptoUpdater.h"

std::atomic<double> usd2eurRate(0);

cryptoUpdater::cryptoUpdater() { mLogger = std::make_shared<logger>(); }

void cryptoUpdater::updateAssetsMetadata() {
    cryptoUniqueList["bitcoin"] = uniqueAssetData(100.0, 40000.0, "crypto");
    cryptoUniqueList["polkadot"] = uniqueAssetData(100.0, 5.0, "crypto");
    nlohmann::json response;
    fetchEuroValue(response);
    usd2eurRate = 1 / std::stod(response["rateUsd"].get<std::string>());
}

// Input: Name, Value invested, units, type
void cryptoUpdater::updateAssetsValue() {
    updateAssetsMetadata();
    dbWrapper = std::make_unique<databaseWrapper>();
    for (const auto &[cryptoName, cryptoData] : cryptoUniqueList) {
        nlohmann::json response;
        double value;
        std::string name;
        switch (fetchAssetValue(cryptoName, response)) {
        case SUCCESS:
            name = response["id"].get<std::string>().c_str();
            value = std::stod(response["priceUsd"].get<std::string>()) * usd2eurRate;
            mLogger->logInfo("%s values: %.2f", name.c_str(), value);
            {
                std::map<std::string, tableEntries> entry;
                entry.insert(std::pair<std::string, tableEntries>("Name", cryptoName+std::to_string(static_cast<int>(value))));
                entry.insert(std::pair<std::string, tableEntries>("Value", static_cast<int>(value)));
                entry.insert(std::pair<std::string, tableEntries>("Type", "Crypto"));
                dbWrapper->insertInTable("portefolioItemsList", entry);
            }
            break;
        case FAILED_CURL_CONNECTION:
            break;
        case FETCH_ERROR:
            break;
        }
    }
}

cryptoUpdater::Result cryptoUpdater::fetchAssetValue(const std::string &cryptoName, nlohmann::json &response) const {
    CURL *curl;
    CURLcode res;
    std::string curlResponse;
    // Initialize libcurl
    curl = curl_easy_init();

    // Set the URL to the CoinGecko API endpoint for Bitcoin's price
    std::string baseUrl = "https://api.coincap.io/v2/assets/";
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
    curl_easy_setopt(curl, CURLOPT_URL, (baseUrl + cryptoName).c_str());
    // Perform the HTTP GET request
    res = curl_easy_perform(curl);
    // Check for errors
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        return FETCH_ERROR;
    } else {
        // Parse the JSON response to extract the Bitcoin price
        // You would need a JSON parsing library for this part
        // You can use libraries like jsoncpp or nlohmann/json
        try {
            response = nlohmann::json::parse(curlResponse)["data"];
            return SUCCESS;
        } catch (std::exception &e) {
            mLogger->logError("Error getting crypto value: %s", e.what());
            return FETCH_ERROR;
        }
    }
}

cryptoUpdater::Result cryptoUpdater::fetchEuroValue(nlohmann::json &response) const {
    CURL *curl;
    CURLcode res;
    std::string curlResponse;
    // Initialize libcurl
    curl = curl_easy_init();

    // Set the URL to the CoinGecko API endpoint for Bitcoin's price
    std::string baseUrl = "https://api.coincap.io/v2/rates/euro";
    curl = curl_easy_init();
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
    curl_easy_setopt(curl, CURLOPT_URL, baseUrl.c_str());
    // Perform the HTTP GET request
    res = curl_easy_perform(curl);
    // Check for errors
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        return FETCH_ERROR;
    } else {
        // Parse the JSON response to extract the Bitcoin price
        // You would need a JSON parsing library for this part
        // You can use libraries like jsoncpp or nlohmann/json
        try {
            response = nlohmann::json::parse(curlResponse)["data"];
            return SUCCESS;
        } catch (std::exception &e) {
            mLogger->logError("Error getting crypto value: %s", e.what());
            return FETCH_ERROR;
        }
    }
}