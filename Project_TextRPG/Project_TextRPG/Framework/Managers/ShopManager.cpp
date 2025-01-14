#include "ShopManager.h"

#include <iostream>
#include "Framework/Managers/LogManager.h"
#include "Item.h"
#include "Player/Player.h"

void ShopManager::PrintShopMenu()
{
	std::string InputVal;
	bool bIsRunning = true;
	
	while (bIsRunning)
	{
		// 로그 초기화
		LogManager::Get().Clear();

		std::cout << "상점입니다." << std::endl;
		std::cout << "구매: 1 판매: 2 나가기: 0" << std::endl;
		std::cout << "어떤 작업을 하시겠습니까?: ";

		std::cin >> InputVal;

		// 버퍼의 입력 가능한 최대 문자의 수만큼 모든 문자를 무시하고 개행 문자를 만나면 중단
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
				std::cout << "잘못된 번호입니다. ";

				LogManager::Get().Pause();
				break;
			}
		}
		catch (const std::invalid_argument&)
		{
			std::cout << "숫자를 입력해야합니다. ";

			LogManager::Get().Pause();
		}
		catch (const std::out_of_range&)
		{
			std::cout << "입력한 숫자가 너무 큽니다. ";

			LogManager::Get().Pause();
		}
	}
}

void ShopManager::PrintShopBuy()
{
	ItemList CurList = ItemList::GetInstance();
	const std::vector<std::shared_ptr<Item>>& Items = CurList.GetItems();

	// 로그 초기화
	LogManager::Get().Clear();

	for (int i = 0; i < Items.size(); ++i)
	{
		// 비어있을경우 넘어감
		if (nullptr == Items[i]) continue;

		std::cout << i + 1 << "번 " << Items[i].get()->GetName() << "의 가격: " << Items[i].get()->GetGoldCost() << std::endl;
	}

	std::cout << "구매를 취소하려면 0을 입력해주세요." << std::endl;

	// 입력에 *번이라고 문자를 포함할 경우의 처리를 위해 스트링으로 입력 받음
	std::string InputVal;

	while (true)
	{
		std::cout << "구매하려는 아이템의 번호를 적어주세요: ";

		std::cin >> InputVal;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		try
		{
			// 숫자로 사용
			int ItemsIndex = std::stoi(InputVal);

			// 구매 나가기
			if (0 == ItemsIndex)
			{
				break;
			}
			// 아이템 목록에서 한가지 구매
			else if (ItemsIndex <= Items.size())
			{
				std::cout << Items[ItemsIndex - 1]->GetName() << "의 구매를 취소하려면 0을 입력해주세요." << std::endl;
				std::cout << "구매하려는 아이템의 개수를 적어주세요: ";

				std::cin >> InputVal;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				// 숫자로 사용
				int ItemCount = std::stoi(InputVal);

				// 0을 입력 받으므로 취소처리
				if (0 == ItemCount)
				{
					std::cout << "구매가 취소 됐습니다." << std::endl;

					LogManager::Get().Pause();
					continue;
				}

				Player* CurPlayer = Player::GetInstance();
				if (nullptr == CurPlayer)
				{
					return;
				}

				// ItemsIndex를 1크게 입력 받으므로 1감소해서 접근
				CurPlayer->BuyItem(Items[ItemsIndex - 1]->GetName(), Items[ItemsIndex - 1]->GetGoldCost(), ItemCount);

				LogManager::Get().Pause();

				break;
			}
			// 잘못된 입력인지 확인
			else
			{
				std::cin.clear(); // 오류 상태 초기화
				std::cout << "잘못된 아이템 번호입니다. ";

				LogManager::Get().Pause();
			}
		}
		catch (const std::invalid_argument&)
		{
			std::cout << "숫자를 입력해야합니다. ";

			LogManager::Get().Pause();
		}
		catch (const std::out_of_range&)
		{
			std::cout << "입력한 숫자가 너무 큽니다. ";

			LogManager::Get().Pause();
		}
	}
}

void ShopManager::PrintShopSell()
{
	// 로그 초기화
	LogManager::Get().Clear();

	ItemList CurList = ItemList::GetInstance();
	const std::vector<std::shared_ptr<Item>>& Items = CurList.GetItems();

	Player* CurPlayer = Player::GetInstance();
	if (nullptr == CurPlayer)
	{
		return;
	}

	// 플레이어의 인벤토리에 있는 아이템 출력
	unordered_map<string, int> CurInv = CurPlayer->GetInventory();

	// 인벤토리에 있는 아이템들의 이름 임시 저장
	std::vector<std::string> InvItems;
	for (pair<string, int> e : CurInv)
	{
		std::cout << InvItems.size() + 1 << "번 " << e.first << " 현재 " << e.second << "개 있습니다. " << "1개당 가격: " << CurList.GetItem(e.first)->GetGoldCost() << std::endl;
		InvItems.push_back(e.first);
	}

	std::cout << "판매를 취소하려면 0을 입력해주세요." << std::endl;

	// 플레이어가 팔려고하는 아이템의 번호 입력 및 개수 입력
	// 입력에 *번이라고 문자를 포함할 경우의 처리를 위해 스트링으로 입력 받음
	std::string InputVal;

	while (true)
	{
		std::cout << "판매하려는 아이템의 번호를 적어주세요: ";

		std::cin >> InputVal;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		try
		{
			// 숫자로 사용
			int ItemsIndex = std::stoi(InputVal);

			// 상점 나가기
			if (0 == ItemsIndex)
			{
				break;
			}
			// 아이템 목록에서 한가지 구매
			else if (ItemsIndex <= InvItems.size())
			{
				std::cout << InvItems[ItemsIndex - 1] << "의 판매를 취소하려면 0을 입력해주세요." << std::endl;
				std::cout << "판매하려는 아이템의 개수를 적어주세요: ";

				std::cin >> InputVal;

				// 숫자로 사용
				int ItemCount = std::stoi(InputVal);

				// 0을 입력 받으므로 취소처리
				if (0 == ItemCount)
				{
					std::cout << "판매가 취소 됐습니다." << std::endl;

					LogManager::Get().Pause();
					continue;
				}

				Player* CurPlayer = Player::GetInstance();
				if (nullptr == CurPlayer)
				{
					return;
				}

				// 판매 가격을 구매 가격의 60%로
				int SellPrice = CurList.GetItem(InvItems[ItemsIndex - 1])->GetGoldCost();
				SellPrice *= 0.6;

				// ItemsIndex를 1크게 입력 받으므로 1감소해서 접근
				CurPlayer->SellItem(InvItems[ItemsIndex - 1], SellPrice, ItemCount);

				LogManager::Get().Pause();

				break;
			}
			// 잘못된 입력인지 확인
			else
			{
				std::cin.clear(); // 오류 상태 초기화
				std::cout << "잘못된 아이템 번호입니다. ";

				LogManager::Get().Pause();
			}
		}
		catch (const std::invalid_argument&)
		{
			std::cout << "숫자를 입력해야합니다. ";

			LogManager::Get().Pause();
		}
		catch (const std::out_of_range&)
		{
			std::cout << "입력한 숫자가 너무 큽니다. ";

			LogManager::Get().Pause();
		}
	}
}

void ShopManager::BuyItem(int ItemsIndex)
{
}

void ShopManager::SellItem()
{
}