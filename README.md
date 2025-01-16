# Sparta_Text_RPG

스파르타 내일배움캠프의 첫 번째 팀 프로젝트 과제입니다.  
6명이서 한 조가 되어 협업해서 만들었습니다.

C++을 사용해 만든 텍스트 기반 RPG게임입니다.  
주요 콘텐츠는 출력되는 이미지와 자동 배틀, 상점이 있습니다.  
해당 프로젝트로 개인의 실력을 향상시키거나 개념을 복습하는 등

## 개발 환경

+ IDE: Visual Studio 2022 / IntelliJ
+ Compiler : MSVC 19.38.38143 / C++ 17 이상
+ Architecture : x86 (32-bit)

## 빌드/실행 방법

`Project_TextRPG.sln`를 실행시켜 사용하고 있는 IDE에서 빌드 > 솔루션 빌드를 합니다.

## 의존 라이브러리/패키지

사용하고 있는 라이브러리 등 추가로 사용한 것은 없습니다.

## 프로젝트 개요

### 개발 기간

2025.01.10 ~ 2025.01.16

### 게임 설명

캐릭터를 생성해 몬스터와 전투를 하며 경험치와 골드를 얻어 캐릭터를 강하게 만듭니다.  
강해지다가 캐릭터의 렙이 10이 될 경우 보스 몬스터와 전투를 하고 이기면 엔딩입니다.

## 기본 요구사항

1. **캐릭터 생성 및 관리**
    - 원하는 이름으로 캐릭터를 하나 뿅! 만들 수 있어야 합니다.
    - **레벨 1**, **초기 체력 200**, **공격력 30**, **경험치 0**으로 시작하고, 레벨업에 필요한 경험치는 **100** 고정!
    - 언제든지 캐릭터 상태 확인 가능!

2. **레벨업 효과**
    - 레벨이 오를 때마다 체력과 공격력이 폭발적으로(?) 상승합니다.
    - **체력**: `(현재 체력 + (레벨 × 20))`, **공격력**: `(현재 공격력 + (레벨 × 5))`
    - 레벨업 시 체력은 최대치까지 완전히 회복!
    - 최대 레벨은 **10으로 제한.**

3. **전투 시스템**
    - 랜덤으로 출몰하는 몬스터와 턴제로 싸웁니다.
    - 전투 시작 조건:
        - 캐릭터 생성 직후
        - 전투 승리 후 상점 방문을 스킵하거나, 상점 이용 후
    - 전투 승리: 경험치 50 획득 & 10~20 골드 랜덤 획득
    - 경험치 누적 100 이상 → 자동 레벨업

4. **몬스터 설명**
    - 몬스터도 이름, 체력, 공격력을 가집니다.
    - 몬스터 스펙은 캐릭터 레벨에 비례해서 랜덤하게 생성:
        - 체력: (레벨 × 20) ~ (레벨 × 30)
        - 공격력: (레벨 × 5) ~ (레벨 × 10)

5. **아이템 및 골드 관리**
    - 전투에서 이기면 골드를 얻고, 가끔(30% 확률) 아이템이 떨어집니다.
    - 아이템은 **체력 +50** 또는 **공격력 +10**을 해주는 멋진 효과!
    - 전투 중에는 "이럴 때 아이템!" 하고 랜덤하게 사용됩니다. (디테일은 자유롭게!)
    - 아이템은 사용 순간 사라지고, 효과는 바로 캐릭터에게 반영됩니다.
    
6. **게임 로그 확인**
    - “전투? 아이템 사용? 골드 획득?” 중요한 이벤트는 콘솔에 쭉 기록됩니다.
    - 로그를 통해 오늘 어떤 몬스터를 몇 마리 눕혔는지~ 한 눈에 확인 가능!

7. **게임 화면**
    - 캐릭터 생성 및 상태 확인
      
    > 캐릭터 이름을 입력하세요: Hero  
    > 캐릭터 Hero 생성 완료! 레벨: 1, 체력: 100, 공격력: 10

    - 일반 몬스터와의 전투
      
        > 몬스터 Goblin 등장! 체력: 40, 공격력: 8  
        > Hero가 Goblin을 공격합니다! Goblin 체력: 30  
        > Goblin이 Hero를 공격합니다! Hero 체력: 92  
        > Hero가 Goblin을 공격합니다! Goblin 처치!  
        > Hero가 50 EXP와 12 골드를 획득했습니다. 현재 EXP: 50/100, 골드: 12

    - 주인공 사망으로 게임 종료
      
        > 몬스터 Dragon 등장! 체력: 450, 공격력: 50  
        > Dragon이 Hero를 공격합니다! Hero 체력: 50 → 0  
        > Hero가 사망했습니다. 게임 오버!

8. **몬스터 보스전**
    - **레벨 10 달성** 시, 이제 일반 몬스터는 상대도 안 된다!
    - “보스 몬스터”가 짜잔~ 등장합니다.
    - 체력·공격력은 기존 몬스터의 **1.5배** 범위를 랜덤으로 설정!
    - 보스 클리어하면 “축하합니다! 게임 엔딩을 보셨습니다!”

9. **상점 시스템**
    - 전투가 끝나면 “상점을 방문하시겠습니까? (Y/N)” 물어보기
    - 상점에서는 골드로 아이템을 구매/판매 가능(아이템 목록은 자유롭게!)
        - 아이템 구매
            - 플레이어는 골드를 사용해서 아이템을 구매
            - 구매 아이템은 인벤토리에 즉시 추가
        - 아이템 판매
            - 플레이어는 보유한 아이템을 골드로 판매 **(판매 가격은 구입 원가의 60%!)**
            - 판매된 아이템은 인벤토리에서 즉시 제거
    - “체력 물약 10 Gold”, “공격력 강화 15 Gold”처럼 가격을 정해놓기!
    - 구매 즉시 인벤토리에 들어오며, 판매 시 아이템이 소멸되고 골드 획득!
    - 즉, 상점 시스템을 추가한다는 것은 곧 인벤토리도 있어야한다.

## 과제 이외의 추가 구현 사항

과제 이외의 추가로 구현하는 사항을 구현하면서 6번 게임 로그 확인과 몬스터와 플레이어 스텟 등 구체적인 값을 살짝 변경했습니다.  
현재 요구사항과 프로젝트의 차이점은 튜터 선생님들의 확인을 받아 이정도는 문제 없다는 것을 확인했습니다.

### 유저의 선택지 추가

유저가 몬스터의 난이도를 선택해서 전투를 할 수 있도록 선택지를 추가했습니다.

![Player_Choose](https://github.com/user-attachments/assets/a61643ba-77db-4c29-9db2-0e493239a35e)

### 특정 아이템 획득시 즉시 사용

상점 혹은 몬스터의 드랍을 통해 특정 아이템을 획득 할 시 그 즉시 아이템이 사용되도록 했습니다.

![Immediately_Item_1](https://github.com/user-attachments/assets/60c8a328-8874-4f66-b2b7-ff31d3aade87)

![Immediately_Item_2](https://github.com/user-attachments/assets/8b308220-233f-438d-ac95-859d067cb2d6)

### 콘솔창에 이미지 띄우기 및 유저 인터페이스

유저인터페이스와 이미지를 띄우는 기능을 추가했습니다.

![Player_Choose_Menu](https://github.com/user-attachments/assets/0316ceb2-4ee3-4d9e-aa96-3fd691e19986)

![Shop_Menu](https://github.com/user-attachments/assets/5d254ee8-61f2-48c4-b132-803b346b7c65)

## 프로젝트 구조

```
Project_TextRPG
┣ Project_TextRPG.cpp // 메인 함수 진입점
┃
┣ Item.h        // 아이템 헤더
┣ Item.cpp      // 아이템 구현
┃
┣ Framwork      // 디렉토리
┃ ┣ Framwork.h      // 프레임워크 헤더
┃ ┣ Framwork.cpp    // 프레임워크 구현
┃ ┃
┃ ┣ Manager     // 디렉토리
┃ ┃ ┣ BattleManager.h   // 배틀 매니저 헤더
┃ ┃ ┣ BattleManager.cpp // 배틀 매니저 구현
┃ ┃ ┃
┃ ┃ ┣ LogManager.h      // 로그 매니저 헤더
┃ ┃ ┣ LogManager.cpp    // 로그 매니저 구현
┃ ┃ ┃
┃ ┃ ┣ ShopManager.h     // 상점 매니저 헤더
┃ ┃ ┣ ShopManager.cpp   // 상점 매니저 구현
┃
┣ Monster       // 디렉토리
┃ ┣ Monster.h       // 몬스터 헤더
┃ ┣ Monster.cpp     // 몬스터 구현
┃
┣ Player        // 디렉토리
┃ ┣ Player.h        // 플레이어 캐릭터 헤더
┃ ┣ Player.cpp      // 플레이어 캐릭터 구현
```

## 클래스 다이어그램

![Class_Diagram](https://github.com/user-attachments/assets/13424e12-d15a-4240-bce2-4f428a7d8971)

## 클래스 설명 및 핵심 로직

### 김선국님 - Item Class, ShopManager

아이템과 상점을 담당해서 구현했습니다.

`Item`클래스의 특징은 다음과 같습니다.

+ 기본 생성자가 없으며 매개변수를 가지는 오버로딩된 생성자를 가집니다.
+ 자식 클래스에서 부모 클래스의 생성자를 위임해 부모 클래스의 생성자가 호출되도록 했습니다.
+ 상속받을 클래스에서 사용할 매개변수를 가지고 있습니다.
+ `Use`함수라는 순수 가상함수를 상속받아 아이템의 사용을 구현합니다.
+ 획득 즉시 사용되는 아이템과 전투 중 사용되는 아이템으로 구분됩니다.

부모 클래스인 아이템 클래스입니다.

![Item_Class](https://github.com/user-attachments/assets/268e43e7-0bfe-4024-b4c2-2f48028e6633)

대표적인 예시로 자식 클래스인 체력 포션 클래스입니다.

![Item_HealthPotion](https://github.com/user-attachments/assets/e5457a5f-02fc-4a57-a9a9-2c1ded6fb4f7)

아이템은 다음과 같은 `enum class`를 사용해 획득 즉시 사용되는 아이템과 전투 중 사용되는 아이템으로 구분됩니다.

![Item_ EItemUsageTypePNG](https://github.com/user-attachments/assets/d1e20ff1-5cee-4ca3-a3cd-a76e4265aafa)

이 `enum`을 멤버 변수로 가지고 플레이어의 인벤토리에 추가되기 전 플레이어 캐릭터가 아이템을 확인하고 즉시 사용하거나 인벤토리에 추가하게 됩니다.

아이템을 상속한 클래스들의 구조는 다음과 같습니다.

![Untitled diagram-2025-01-16-061828](https://github.com/user-attachments/assets/0a5b1314-f51e-4d13-9d31-806515ccd674)

이렇게 아이템의 객체가 정의된 뒤 `ItemList`클래스에서 각 아이템들의 인스턴스를 저장합니다.

`ItemList`는 싱글톤 패턴을 가집니다.  
`ItemList`는 생성자에서 각 객체의 인스턴스를 저장합니다.  
`Get`함수를 만들고, 반환하는 값에 `const`를 사용해 가리키는 주소를 수정하지 못하도록 했습니다.

`ShopManager`클래스의 특징은 다음과 같습니다.

+ 멤버변수를 가지지 않습니다.
+ 모든 멤버 함수를 `static`으로 가집니다.
+ 싱글톤 디자인패턴을 활용한 정적 클래스를 구현했습니다.

![Shop_Class](https://github.com/user-attachments/assets/d82a5ada-3e5f-4c01-9d33-8dbbe78b68f3)

`ShopManager`에서 각 함수는 유저에게 관련된 정보를 출력하고, 입력을 받아 구매, 판매를 선택합니다.  
구매 시 관련된 내용을 출력하고, 구매할 아이템을 입력받고 개수를 입력받아 구매에 필요한 처리를 합니다.  
판매 시 관련된 내용을 출력하고, 판매할 아이템을 입력받고 개수를 입력받아 구매에 필요한 처리를 합니다.

### 김승길님 - Monster Class

몬스터를 담당해서 구현하였습니다. 쉬움, 보통, 어려움에 해당하는 난이도의 몬스터를 생성할 수 있고 각 몬스터의 죽은 횟수도 확인할 수 있습니다.

### FMonsterInfo CreateMonsterInfo 함수

플레이어 레벨 및 선택 난이도에 맞는 몬스터의 이름, 체력, 공격력 정보를 생성할 수 있는 함수입니다.  
Monster 생성자에 이름, 체력, 공격력을 넘겨주기 위해서 FMonsterInfo 라는 구조체 값을 리턴하도록 구현하였습니다.

![image](https://github.com/user-attachments/assets/bfd568ec-63ca-4135-b252-de5cfaadbfc3)

### Monster 생성자

상속받은 Entity 클래스에 있는 이름, 체력, 공격력 변수에 그대로 값을 넣기위하여 해당 값을 받는 형태로 구현하였습니다.  
Difficulty와 Draw는 각각 해당 몬스터의 난이도 및 그림을 위한 데이터입니다.

![image](https://github.com/user-attachments/assets/2cbee39b-ff1b-4dca-9783-f41535237e51)

### void TakeDamage 함수

몬스터가 피해를 입을때마다 해당 값을 계산하고 몬스터가 죽으면 해당 몬스터의 죽은 횟수를 저장하기 위하여  
unordered_map<string, int> DeathCountMap 변수를 사용하여 저장합니다.

![image](https://github.com/user-attachments/assets/2ab8335b-51aa-42b9-b507-3c19690ab66b)

- struct FMonsterInfo; : 몬스터 정보를 담아서 생성자로 넘겨주기 위한 구조체
- static unordered_map<string, int> DeathCountMap; : 몬스터 이름별로 죽은 횟수를 저장 후 이를 출력하기 위한 맵 변수
- int Difficulty; : 몬스터 난이도 저장 변수
- Monster(string Name, int Hp, int Damage, int Difficulty, EDraw Draw); : 몬스터 정보 및 난이도에 맞는 몬스터를 생성하기 위한 생성자
- static FMonsterInfo CreateMonsterInfo(int PlayerLevel, int Difficulty); : 플레이어 레벨 및 선택 난이도에 맞는 몬스터의 이름, 체력, 공격력 정보 생성 함수
- void TakeDamage(int Damage); : 입력값만큼 해당 몬스터 HP 차감을 위한 함수
- static void PrintAllDeathCounts(); : 모든 몬스터의 죽은 횟수를 출력하는 함수

### 김영웅님 - LogManager Class

`LogManager`에서 화면을 구성할 때 `Layout`으로 구분해 `LogManager`에서 관리하게 만들었습니다.  
`Layout`을 상속 받아 `DrawLayout`, `PlayerStatLayout`, `LogLayout`를 구현했고 각자 역할에 따라 추가적인 함수를 구현했습니다.

![Layout 구분](https://github.com/user-attachments/assets/4b7ae973-f9d6-4269-a0eb-c7a7d41e5df1)

Append(string, float)로 LogLayout에 로그를 추가할 수 있습니다만, cout처럼 사용하기 편하게 하기 위해 operator<<를 추가해 LogManager::Get() << "텍스트"; 형식으로 간단하게 사용할 수 있게 만들었습니다.
Clear()로 모든 Layout의 출력을 없앨 수 있습니다.

### DrawLayout

왼쪽에 있는 그림을 출력해 주는 구역입니다.
Draw(EDraw, int, int)로 출력할 수 있으며, 기본적으로는 LogManager에서 같은 이름의 Draw(EDraw, int, int)로 연결되어 호출됩니다.

내부적으로 ReadBMP(string) 함수를 호출해 경로에 있는 .bmp 파일을 가져와 출력해 줍니다.
다른 Layout은 보통 Layout에 있는 Output() 함수로 출력을 하지만 DrawLayout은 자체 적으로 출력합니다.

Layout의 Clear(bool) 함수를 상속받아 다른 Layout은 비워주는 것과 다르게 DrawLayout은 화면을 하얀색으로 초기화해준다.

### PlayerStatLayout

오른쪽 위에 있는 플레이어의 정보를 출력해 주는 구역입니다.
LogManager에서 Append(string, float)를 호출할 시 Update() 함수가 실행되어 플레이어의 정보가 갱신되게 됩니다.

### Log Layout

오른쪽 아래에 있는 다른 모든 Log들을 출력해 주는 구역입니다.
Append(string, float)로 Log를 추가할 수 있으며, LogManager의 같은 이름의 함수로 연결되어 있습니다.

만약 로그가 지정된 범위를 넘어갈 정도로 길거나 줄바꿈이 되어있지 않아 범위를 넘어가게 된다면 자동으로 줄바꿈 및 잘라서 출력해 줍니다.


### 테스트 케이스
|테스트 제목|테스트 절차|케이스 분류|
|---|---|---|
|캐릭터 생성 시, 스탯 동기화 테스트|캐릭터 생성 때 스탯을 얻어와지는지|Abnormal|
|스탯 동기화 테스트|로그 추가, 스탯 동기화가 잘 작동하는지 확인|Normal|
|이미지 로딩|DrawLayout의 ReadBMP로 .bmp 이미지를 로딩, DrawLayout에 잘 출력되는지 확인|Normal|
|이미지 로딩 실패|ReadBMP의 파일 이름을 이상한걸로 넣음. 로딩에 실패했다고 로그가 뜸|Abnormal|

### 도트

기존에 가지고 있던 에셋 및 직접 찍어서 상황에 맞는 도트를 제작했습니다.
DrawLayout의 크기가 50x39가 최대라서 그 안에 맞추는 게 힘들었습니다.

![Stage](https://github.com/user-attachments/assets/26156f47-06c7-45cb-b421-9f69bf615969)
![Slime](https://github.com/user-attachments/assets/ad4b70e2-c021-4509-b82c-2c557a17b813)
![Oak](https://github.com/user-attachments/assets/6306f7dd-c9cb-4990-814d-8d5684062362)
![Boss](https://github.com/user-attachments/assets/667b2114-e9dc-4a26-8a69-d99408925128)

### 엄지훈님 - Player
`Player` 클래스의 독립 변수 및 함수를 전반적으로 담당하였습니다.   
[Player.h](https://github.com/SeonBab/Sparta_Text_RPG/blob/main/Project_TextRPG/Project_TextRPG/Player/Player.h)   
[Player.cpp](https://github.com/SeonBab/Sparta_Text_RPG/blob/main/Project_TextRPG/Project_TextRPG/Player/Player.cpp)   
`Player`는 `Monster`와 같은 부모로 `Entity` 클래스를 두고 있어 이름(`Name`), 최대 체력(`MaxHP`), 현재 쳬력(`HP`), 데미지(`Damage`), 총 4가지의 독립 변수를 공통으로 가지고 있고 추상 함수 `TakeDamage(int Damage)`를 사용합니다.   
`Player`는 추가로 현재 레벨(`Level`), 현재 경험치(`Exp`), 현재 골드(`Gold`), 인벤토리(`Inventory`)를 독립변수로 가집니다. `Inventory`는 unordered_map<string, int> 타입이며 아이템의 이름을 key, 개수를 value로 가집니다.
#### Player 객체 생성(***필수 기능 1***)
해당 게임은 싱글 플레이로 진행되기 때문에 `Player`의 인스턴스를 하나만 생성하기 위해 **싱글톤 패턴**으로 구현하였습니다.   
`Player`는 게임 시작 전에 아래와 같이 초기화 됩니다.   
- `Name`: ""
- `MaxHP`: 200
- `HP`: 200
- `Damage`: 30
- `Level`: 1
- `Exp`: 0
- `Gold`: 0   

게임이 시작되고 플레이어 이름을 설정하기 위해 `SetPlayerName(string Name)` 함수를 통해 `cin`으로 입력 받게 하였습니다.   
#### 경험치 및 레벨 처리(***필수 기능 2***)
`Player`는 몬스터를 잡게되면 경험치를 일정량 받게됩니다. `Player`의 `UpdateExp(int ExpAmount)` 함수에서 전투에서 `Player`가 획득한 경험치만큼 `Exp`를 증가시키고 만약 `Exp`가 100이상이 된다면 `LevelUP()`함수를 호출합니다. 만약 플레이어가 이미 10레벨인 경우 더 이상 경험치를 받지 않도록 하였습니다.  
`LevelUp()`함수는 `Player`의 `Level`을 1 상승시키고 `Exp`를 100 감소시킵니다. 레벨이 오르는 경우 `Level`x20만큼 `MaxHP`가 오르고 `Level`x5만큼 `Damage`가 오르게 됩니다. 만약 `Player`의 `Level`이 10이 되면 `Exp`를 0으로 초기화합니다.   

#### 아이템 구매/판매(상점)(***도전 기능 2***)
`Player`가 상점에서 아이템을 구매하는 `BuyItem(string ItemName, int ItemPrice, int Count)`, 아이템을 판매하는 `SellItem(string ItemName, int ItemPrice, int Count)` 함수를 구현하였습니다.   
`BuyItem(string ItemName, int ItemPrice, int Count)` 함수는 `ItemName` 이름을 가지는 아이템을 `Item` 클래스의 함수를 통해 조회한 뒤 `ItemPrice`x`Count` 보다 `Player`의 `Gold`가 많을 경우 `ItemPrice`x`Count`만큼 골드를 차감하여 구매에 성공하고 `AddItem(String ItemName, int Count)` 함수를 호출합니다.   
`SellItem(string ItemName, int ItemPrice, int Count)` 함수는 `Inventory`에서 `ItemName`의 개수를 조사한 뒤 `Count`보다 많다면 `Inventory`에서 해당 `Count`만큼 `ItemName`의 개수를 줄이고고 `ItemPrice`x`Count` 만큼 
#### 아이템 추가
아이템을 구매하거나(`Player::BuyItem`) 전투 후 획득했을 때(`BattleManager`의 로직) `AddItem(string ItemName, int Count)` 함수를 통해 아이템을 처리합니다.   
`Item`은 2가지 사용 타입(`EItemUsageType`)을 가집니다.   
`EItemUsageType`이 `Battle`인 경우 `Count`만큼 인벤토리에 아이템을 추가합니다.
`EItemUsageType`이 `Immediately`인 경우 해당 아이템은 즉시 `Count`만큼 반복하여 사용됩니다.
#### 랜덤 아이템 사용(***필수 기능 5***)
아이템 사용을 랜덤화하여 게임 플레이에 재미를 더해보았습니다.   
아이템은 전투 중에 매 턴이 끝날때 마다 30퍼센트의 확률로 `UseRandomItem()`을 호출합니다(`BattleManger`에 로직으로 구현).   
`UseRandomItem()`은 `Inventory`에 개수가 0보다 많은 아이템에 대해 `Vector`를 만들고 해당 아이템 중 랜덤하게 하나를 사용하도록 구현하였습니다.


### 이재명님 - Framwork
게임이 실행될 프레임워크 구현을 담당했습니다.



### 전재민님 - BattleManager

`Player`와 사용자가 선택한 길의 `Monster` 클래스를 받아와 전투를 진행

10레벨 달성시 보스 몬스터와 전투를 진행

`Monster`의 강함 정도에 따른 골드와 경험치 차등 보상 지급

랜덤으로 `Item` 사용 및 `Item` 드랍

## 주의사항

현재 주의해야할 사항은 없는걸로 파악됩니다.
