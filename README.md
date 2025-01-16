# Sparta_Text_RPG

스파르타 내일부트 캠프의 첫 번째 팀 프로젝트 과제입니다.  
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

7. **몬스터 보스전**
    - **레벨 10 달성** 시, 이제 일반 몬스터는 상대도 안 된다!
    - “보스 몬스터”가 짜잔~ 등장합니다.
    - 체력·공격력은 기존 몬스터의 **1.5배** 범위를 랜덤으로 설정!
    - 보스 클리어하면 “축하합니다! 게임 엔딩을 보셨습니다!”

8. **상점 시스템**
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

### 김승길님 - Monster Class

몬스터를 담당해서 구현하셨습니다.

- struct FMonsterInfo; : 몬스터 정보를 담은 구조체
- static unordered_map<string, int> DeathCountMap; : 몬스터 이름별로 죽은 횟수 저장 맵
- int Difficulty; : 몬스터 난이도 저장 변수
- Monster(string Name, int Hp, int Damage, int Difficulty); : 몬스터 정보 및 난이도에 맞는 몬스터 생성자
- static FMonsterInfo CreateMonsterInfo(int PlayerLevel, int Difficulty); : 플레이어 레벨 및 선택 난이도에 맞는 몬스터의 이름, 체력, 공격력 정보 생성 함수
- void TakeDamage(int Damage); : 입력값만큼 해당 몬스터 HP 차감 함수
- static void PrintAllDeathCounts(); : 모든 몬스터의 죽은 횟수 출력 함수

`Entity` 클래스를 상속받아서 `Entity` 생성자의 `Name`, `HP`, `Damage` 부분을 사용해서 몬스터 생성자 구현

랜덤으로 몬스터 생성 및 몬스터의 공격 및 피격 결과 확인, 보스 몬스터 소환 기능 구현  
이때 몬스터의 스펙이 캐릭터 레벨에 비례해 랜덤하게 생성되도록 구현

`unordered_map` STL을 사용하여 각 몬스터의 죽은 횟수를 저장하고 해당 변수를 사용하여 전투 종료 이후에
각 몬스터의 죽은 횟수를 확인할 수 있도록 구현

### 김영웅님 - LogManager Class

`LogManager`에서 화면을 구성할 때 `Layout`으로 구분해 `LogManager`에서 관리하게 만들었습니다.  
`Layout`을 상속 받아 `DrawLayout`, `PlayerStatLayout`, `LogLayout`를 구현했고 각자 역할에 따라 추가적인 함수를 구현했습니다.

`STL`은 `vector`를 수시로 많이 썼습니다.  
특히 `DrawBPM()` 함수에서 `vector`를 많이 썼습니다.

테스트 제목 : 캐릭터 생성 시, 스탯 동기화 테스트
테스트 절차
1. 캐릭터 생성 때 스탯을 얻어와지는지
Abnormal

테스트 제목 : 스탯 동기화 테스트
테스트 절차
1. 로그 추가
2. 스탯 동기화가 잘 작동하는지 확인
Normal

테스트 제목 : 이미지 로딩
테스트 절차
1. DrawLayout의 ReadBMP로 .bmp 이미지를 로딩
2. DrawLayout에 잘 출력되는지 확인
Normal

테스트 제목 : 이미지 로딩 실패
테스트 절차
1. ReadBMP의 파일 이름을 이상한걸로 넣음
2. 로딩에 실패했다고 로그가 뜸
Abnormal

필수
1. 화면을 분할 해 각자 구역에 출력되게 만들기
완

2. Player의 Status를 실시간 갱신하기
완

3. 상황에 따라 도트 띄어주기
아직 진행

### 엄지훈님 - Player



### 이재명님 - Framwork



### 전재민님 - BattleManager



## 주의사항

현재 주의해야할 사항은 없는걸로 파악됩니다.
