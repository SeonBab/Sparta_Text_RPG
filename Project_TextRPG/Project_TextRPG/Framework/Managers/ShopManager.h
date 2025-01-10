#pragma once

class ShopManager
{
public:
    static void PrintShopMenu();

private:
    static void PrintShopBuy();
    static void PrintShopSell();

    static void BuyItem(int ItemsIndex);
    static void SellItem();

    ShopManager();

    ShopManager(const ShopManager&) = delete;
    ShopManager& operator=(const ShopManager&) = delete;
};