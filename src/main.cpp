#include "AdvAuction.h"

#include <iostream>

using namespace std;

int main() {
    vector<Banner> allBanners = {
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

    int numPlaces = 3;
    string country = "Russia";

    vector<Banner> winningBanners = selectWinningBanners(allBanners, numPlaces, country);

    for (const auto& banner : winningBanners) {
        cout << "Price: " << banner.price << ", Campaign ID: " << banner.campaign_id << ", Countries: ";
        for (const auto& c : banner.countries) {
            cout << c << " ";
        }
        cout << ", Internal ID: " << banner.internal_id << endl;
    }

    return 0;
}
