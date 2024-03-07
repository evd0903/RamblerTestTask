#pragma once

#include "test_runner.h"
#include <unordered_set>

inline void TestValidAdvAuction() {
    {
        std::vector<Banner> allBanners = {
        {10, 1, {"Russia", "USA"}, 1},
        {20, 2, {"Russia"}, 2},
        {30, 3, {"USA"}, 3},
        {40, 4, {}, 4},
        {50, 5, {"Russia"}, 5},
        {60, 6, {"Russia"}, 6},
        {60, 8, {"Russia"}, 10},
        {60, 7, {"Russia"}, 11},
        {70, 7, {"USA"}, 7},
          {100, 20, {}, 4},
        };
        std::vector<int> validPrices = {100,60,60};

        std::vector<Banner> winningBanners = selectWinningBanners(allBanners, 3, "Ruusia");
        std::vector<int> winningBannersPrices;
        std::unordered_set<int> winningBannersCampaignId;

        std::ranges::transform(winningBanners.begin(), winningBanners.end(), winningBannersPrices.begin(),
                            [](const Banner& banner){return banner.price;});
        std::ranges::transform(winningBanners.begin(), winningBanners.end(), std::inserter(winningBannersCampaignId, winningBannersCampaignId.end()),
                            [](const Banner& banner){return banner.campaign_id;});

        ASSERT_EQUAL(winningBanners.size(), 3);
        ASSERT_EQUAL(winningBannersPrices, validPrices);
        ASSERT_EQUAL(winningBannersCampaignId.size(), 3);
    }
}