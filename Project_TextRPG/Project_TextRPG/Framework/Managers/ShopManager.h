#pragma once

class ShopManager
{
public:
    static void PrintShopMenu();

private:
    static void PrintShopBuy();
    static void PrintShopSell();

    ShopManager();

    ShopManager(const ShopManager&) = delete;
    ShopManager& operator=(const ShopManager&) = delete;
};