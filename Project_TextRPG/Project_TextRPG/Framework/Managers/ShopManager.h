#pragma once

class ShopManager
{
public:
    void PrintShopMenu();
    void PrintShopBuy();
    void PrintShopSell();

private:
    void BuyItem(int ItemsIndex);
    void SellItem();

    friend class MainGame;

    ShopManager() = default;
};