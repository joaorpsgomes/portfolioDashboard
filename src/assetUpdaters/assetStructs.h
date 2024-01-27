#ifndef ASSETSTRUCTS_H
#define ASSETSTRUCTS_H

#include <string>
#include <map>

struct uniqueAssetData {
    double mInvestedValue;
    double mUnits;
    std::string mType;

    uniqueAssetData() = default;

    uniqueAssetData(double investedValue, double units, std::string type)
        : mInvestedValue(investedValue), mUnits(units), mType(type) {}
};

typedef std::map<std::string, uniqueAssetData> uniqueAssetList;

#endif // ASSETSTRUCTS_H
