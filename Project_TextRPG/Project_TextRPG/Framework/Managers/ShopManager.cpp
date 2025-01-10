#include "ShopManager.h"

#include <iostream>
#include "Item.h"

void ShopManager::PrintShopMenu()
{
	std::string InputVal;
	bool bIsRunning = true;
	
	while (bIsRunning)
	{
		std::cout << "상점입니다." << std::endl;
		std::cout << "구매: 1 판매: 2 나가기: 0" << std::endl;
		std::cout << "어떤 작업을 하시겠습니까?: ";

		
		std::cin >> InputVal;
		try
		{
			// 숫자로 사용
			int InputNum = std::stoi(InputVal);

			switch (InputNum)
			{
			case 0:
				bIsRunning = false;
				break;
			case 1:
				PrintShopBuy();
				break;
			case 2:
				PrintShopSell();
				break;
			default:
				std::cin.clear(); // 오류 상태 초기화
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 버퍼의 입력 가능한 최대 문자의 수만큼 모든 문자를 무시하고 개행 문자를 만나면 중단
				std::cout << "잘못된 번호입니다. 다시 시도하세요." << std::endl;
				break;
			}
		}
		catch (const std::invalid_argument& e)
		{
			std::cout << "잘못된 입력입니다. 숫자를 입력하세요." << std::endl;
		}
		catch (const std::out_of_range& e)
		{
			std::cout << "입력한 숫자가 너무 큽니다." << std::endl;
		}
	}
}

void ShopManager::PrintShopBuy()
{
	ItemList CurList = ItemList::GetInatance();
	const std::vector<std::shared_ptr<Item>>& Items = CurList.GetItems();
	for (int i = 0; i < Items.size(); ++i)
	{
		// 비어있을경우 넘어감
		if (nullptr == Items[i]) continue;

		std::cout << i + 1 << "번 " << Items[i].get()->GetName() << "의 가격: " << Items[i].get()->GetGoldCost() << std::endl;
	}

	// 입력에 *번이라고 문자를 포함할 경우의 처리를 위해 스트링으로 입력 받음
	std::string InputVal;

	while (true)
	{
		std::cout << "상점을 나가려면 0을 입력하면 됩니다." << std::endl;

		std::cout << "구매하려는 아이템의 번호를 적어주세요: ";

		std::cin >> InputVal;

		try
		{
			// 숫자로 사용
			int InputNum = std::stoi(InputVal);

			// 상점 나가기
			if (0 == InputNum)
			{
				break;
			}
			// 아이템 목록에서 한가지 구매
			else if (InputNum <= Items.size())
			{
				// InputNum을 1 크게 입력 받았으므로 1감소
				BuyItem(InputNum - 1);
			}
			// 잘못된 입력인지 확인
			else
			{
				std::cin.clear(); // 오류 상태 초기화
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "잘못된 아이템 번호입니다. 다시 시도하세요." << std::endl;
			}
		}
		catch (const std::invalid_argument& e)
		{
			std::cout << "잘못된 입력입니다. 숫자를 입력하세요." << std::endl;
		}
		catch (const std::out_of_range& e)
		{
			std::cout << "입력한 숫자가 너무 큽니다." << std::endl;
		}
	}
}

void ShopManager::PrintShopSell()
{
	// 플레이어의 인벤토리에 아이템이 있는지 확인
	// 플레이어의 인벤토리에 아이템이 없다면 없다고 로그 띄운 다음 잠깐 멈추기
	// 플레이어의 인벤토리에 아이템이 있다면 목록 표시
	// 플레이어가 팔려고하는 아이템의 번호 입력 및 개수 입력
	// 입력 확인
	// 팔려하는 아이템의 개수에 문제가 없다면 판매
	SellItem();
	// 팔려하는 아이템의 개수에 문제가 있다면 다시 입력 및 출력
	std::cout << "판매하려는 개수보다 가지고 있는 아이템의 개수가 적습니다." << std::endl;
}

void ShopManager::BuyItem(int ItemsIndex)
{
	ItemList CurList = ItemList::GetInatance();
	const std::vector<std::shared_ptr<Item>>& Items = CurList.GetItems();
	std::shared_ptr<Item> CurItem = Items[ItemsIndex - 1];
	
	if (nullptr == CurItem)
	{
		// 아이템 배열의 값이 비어있는 오류
		// 구매 불가
		return;
	}

	int CurCost = CurItem->GetGoldCost();
	// TODO
	// 플레이어의 골드를 가져와서 돈이 있는지 확인
	// 플레이어의 골드가 있으면 인벤토리에 추가 및 출력
	std::cout << "구매 되었습니다." << std::endl;
	// 플레이어의 골드가 없으면 출력만
	std::cout << "골드가 부족합니다." << std::endl;
}

void ShopManager::SellItem()
{
	// TODO
	// 플레이어의 인벤토리에 아이템 수정

	std::cout << "판매 되었습니다." << std::endl;
}