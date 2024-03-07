#pragma once

#include <string>
#include <vector>

struct Banner {
    int price;
    int campaign_id;
    std::vector<std::string> countries;
    int internal_id;
};

auto filterBannersByCountry(const std::vector<Banner>& banners, const std::string& country);

auto groupBannersByPrice(const std::vector<Banner>& banners);

bool isCampaignUnique(int campaignId, const std::vector<Banner>& winningBanners);

std::vector<Banner> getUniqueAmongWinningBanners(const std::vector<Banner>& banners, const std::vector<Banner>& winningBanners);

std::vector<Banner> getUniqueBanners(const std::vector<Banner>& banners, const std::vector<Banner>& winningBanners);

std::vector<Banner> selectWinningBanners(const std::vector<Banner>& banners, int numPlaces, const std::string& country);