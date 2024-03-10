#include "AdvAuction.h"

#include <unordered_set>
#include <algorithm>
#include <ranges>
#include <format>
#include <random>
#include <utility>

using namespace std;

auto filterBannersByCountry(const vector<Banner>& banners, const string& country) {
    return ranges::views::filter([&country](const Banner& banner) {
        return find(banner.countries.begin(), banner.countries.end(), country) != banner.countries.end() || banner.countries.empty();
        })(banners);
}

map<int, vector<Banner>> groupBannersByPrice(const vector<Banner>& banners) {
    map<int, vector<Banner>> bannersByPrice;

    for (const auto& banner : banners) {
        bannersByPrice[banner.price].push_back(banner);
    }
    return bannersByPrice;
}

bool isCampaignUnique(int campaignId, const vector<Banner>& winningBanners) {
    return none_of(winningBanners.cbegin(), winningBanners.cend(),
        [campaignId](const Banner& banner) {
            return banner.campaign_id == campaignId;
        });
}

vector<Banner> getUniqueAmongWinningBanners(const vector<Banner>& banners, const vector<Banner>& winningBanners) {
    vector<Banner> uniqueBanners;

    copy_if(banners.cbegin(), banners.cend(), back_inserter(uniqueBanners),
        [&winningBanners](const Banner& banner) {
            return isCampaignUnique(banner.campaign_id, winningBanners);
        });

    return uniqueBanners;
}

vector<Banner> getUniqueBanners(const vector<Banner>& banners, const vector<Banner>& winningBanners) {
    unordered_set<int> usedCampaignId;
    vector<Banner> uniqueAmongWinningBanners = getUniqueAmongWinningBanners(banners, winningBanners);
    vector<Banner> uniqueBanners;

    for (auto it = uniqueAmongWinningBanners.begin(); it != uniqueAmongWinningBanners.end(); ++it) {
        if (usedCampaignId.find(it->campaign_id) == usedCampaignId.end()) {
            usedCampaignId.insert(it->campaign_id);
            uniqueBanners.push_back(std::move(*it));
        }
    }

    return uniqueBanners;
}

vector<Banner> selectWinningBanners(const vector<Banner>& banners, int numPlaces, const string& country) {
    vector<Banner> winningBanners;
    map<int, vector<Banner>> bannersByPrice;

    auto filteredBanners = filterBannersByCountry(banners, country);
    vector<Banner> bannersVec(filteredBanners.begin(), filteredBanners.end());

    bannersByPrice = groupBannersByPrice(bannersVec);

    for (auto it = bannersByPrice.rbegin(); it != bannersByPrice.rend(); ++it) {
        const auto& bannersWithMaxPrice = it->second;

        vector<Banner> uniqueBanners = getUniqueBanners(bannersWithMaxPrice, winningBanners);

        int remainingSlots = numPlaces - winningBanners.size();
        if (remainingSlots < uniqueBanners.size()) {
            random_device rd;
            mt19937 gen{ rd() };

            ranges::shuffle(uniqueBanners.begin(), uniqueBanners.end(), gen);
        }

        for (const auto& banner : uniqueBanners) {
            winningBanners.push_back(banner);

            if (winningBanners.size() == numPlaces) {
                break;
            }
        }

        if (winningBanners.size() == numPlaces) {
            break;
        }
    }

    return winningBanners;
}
