#pragma once

#include "test_runner.h"
#include <unordered_set>
#include <algorithm>

inline void TestValidAdvAuction() {
    
    /// Проверям, что из пустого списка баннеров ничего не выбирается
    {
        std::vector<Banner> allBanners = {};

        std::vector<Banner> winningBanners = selectWinningBanners(allBanners, 3, "China");

        ASSERT_EQUAL(winningBanners.size(), 0)
    }

    /// Проверяем условие максимальности суммы выбранных баннеров и соответствие стране
    {
        std::vector<Banner> allBanners = {
            {10, 1, {"USA"}, 1},
            {20, 2, {"Russia"}, 2},
            {30, 3, {"USA"}, 3},
            {40, 4, {"Russia"}, 4},
            {50, 5, {"USA"}, 5},
            {60, 6, {"Russia"}, 6},
            {70, 7, {"USA"}, 7}
        };
        
        std::vector<Banner> expectedResult = {
            {60, 6, {"Russia"}, 6},
            {40, 4, {"Russia"}, 4},
            {20, 2, {"Russia"}, 2}
        };

        std::vector<Banner> winningBanners = selectWinningBanners(allBanners, 3, "Russia");

        ASSERT_EQUAL(winningBanners.size(), expectedResult.size());
        ASSERT_EQUAL(winningBanners, expectedResult);
    }
    
    /// Проверяем ситуацию, если для баннера отсутсвует страна, то он подходит для любой страны
    {
        std::vector<Banner> allBanners = {
            {10, 1, {}, 1},
            {20, 2, {"Russia"}, 2},
            {30, 3, {}, 3}, 
            {40, 4, {"Russia"}, 4},
            {50, 5, {}, 5},
            {60, 6, {"Russia"}, 6},
            {70, 7, {}, 7}
        };

        std::vector<Banner> expectedResult = {
            {70, 7, {}, 7},
            {60, 6, {"Russia"}, 6},
            {50, 5, {}, 5}
        };

        std::vector<Banner> winningBanners = selectWinningBanners(allBanners, 3, "Russia");

        ASSERT_EQUAL(winningBanners.size(), expectedResult.size());
        ASSERT_EQUAL(winningBanners, expectedResult);
    }

    /// Проверяем условие уникальности рекламных кампаний в выбранных баннерах
    {
        std::vector<Banner> allBanners = {
            {100, 10, {"Russia"}, 10},
            {110, 11, {"Russia"}, 11},
            {120, 12, {"Russia"}, 12},
            {130, 13, {"Russia"}, 13},
            {140, 14, {"Russia"}, 14},
            {150, 15, {"Russia"}, 15},
            {150, 15, {"Russia"}, 16},
            {150, 15, {"Russia"}, 17},
            {150, 15, {"Russia"}, 18}
        };

        std::vector<int> expectedPrices = { 150, 140, 130, 120, 110 };

        std::vector<Banner> winningBanners = selectWinningBanners(allBanners, 5, "Russia");
        std::vector<int> winningBannersPrices;

        std::ranges::transform(winningBanners.begin(), winningBanners.end(), std::back_inserter(winningBannersPrices),
            [](const Banner& banner) {return banner.price; });

        ASSERT_EQUAL(winningBanners.size(), expectedPrices.size());
        ASSERT_EQUAL(winningBannersPrices, expectedPrices);
    }

    /// Тест с повторяющимися ценами, проверяем что выбираются баннеры с правильными ценами и уникальными рекламными кампаниями
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
            {100, 20, {}, 4}
        };
        std::vector<int> expectedPrices = { 100,60,60 };

        std::vector<Banner> winningBanners = selectWinningBanners(allBanners, 3, "Russia");
        std::vector<int> winningBannersPrices;
        std::unordered_set<int> winningBannersCampaignId;

        std::ranges::transform(winningBanners.begin(), winningBanners.end(), std::back_inserter(winningBannersPrices),
            [](const Banner& banner) {return banner.price; });
        std::ranges::transform(winningBanners.begin(), winningBanners.end(), std::inserter(winningBannersCampaignId, winningBannersCampaignId.end()),
            [](const Banner& banner) {return banner.campaign_id; });

        ASSERT_EQUAL(winningBanners.size(), 3);
        ASSERT_EQUAL(winningBannersPrices, expectedPrices);
        ASSERT_EQUAL(winningBannersCampaignId.size(), 3);
    }

    /// Тест с повторяющимися ценами, проверяем что выбираются баннеры с правильными ценами и уникальными рекламными кампаниями
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
            {100, 20, {}, 4}
        };
        std::vector<int> expectedPrices = { 100,70,40 };

        std::vector<Banner> winningBanners = selectWinningBanners(allBanners, 3, "USA");
        std::vector<int> winningBannersPrices;
        std::unordered_set<int> winningBannersCampaignId;

        std::ranges::transform(winningBanners.begin(), winningBanners.end(), std::back_inserter(winningBannersPrices),
            [](const Banner& banner) {return banner.price; });
        std::ranges::transform(winningBanners.begin(), winningBanners.end(), std::inserter(winningBannersCampaignId, winningBannersCampaignId.end()),
            [](const Banner& banner) {return banner.campaign_id; });

        ASSERT_EQUAL(winningBanners.size(), 3);
        ASSERT_EQUAL(winningBannersPrices, expectedPrices);
        ASSERT_EQUAL(winningBannersCampaignId.size(), 3);
    }
    
}
