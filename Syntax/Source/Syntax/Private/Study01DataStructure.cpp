#include "Study01DataStructure.h"

AStudy01DataStructure::AStudy01DataStructure()
{
    PrimaryActorTick.bCanEverTick = false;

    // 생성자에서 배열의 기본값을 셋팅해두면, 에디터에 배치할 때 기본적으로 이 아이템들이 들어있게 됩니다.
    InventoryArray.Add(TEXT("기본 단검"));
}

void AStudy01DataStructure::BeginPlay()
{
    Super::BeginPlay();
    
    // 게임이 시작될 때 테스트 로직 실행
    RunDataStructureTest();
}

void AStudy01DataStructure::RunDataStructureTest()
{
    // ==============================================================================
    // 1. TArray 사용법
    // ==============================================================================
    
    // Add: 맨 뒤에 요소 추가 (데이터 복사 발생)
    InventoryArray.Add(TEXT("빨간 포션"));
    
    // Emplace: 맨 뒤에 요소 추가 (복사 과정 없이 해당 메모리 위치에 직접 생성하므로 성능상 더 효율적임. 언리얼에서 권장)
    InventoryArray.Emplace(TEXT("나무 방패"));

    // Num(): 배열의 총 길이(원소 개수) 반환
    int32 ArraySize = InventoryArray.Num(); 
    UE_LOG(LogTemp, Warning, TEXT("[TArray] 현재 인벤토리의 아이템 개수: %d"), ArraySize);

    // IsValidIndex: 배열의 범위를 벗어난 참조(Crash)를 막기 위해 인덱스가 유효한지 안전 검사
    if (InventoryArray.IsValidIndex(0))
    {
        // RemoveAt: 특정 인덱스의 데이터 삭제. (참고: 삭제 시 뒤에 있던 요소들이 빈 자리를 채우기 위해 앞으로 한 칸씩 당겨짐)
        InventoryArray.RemoveAt(0); 
    }

    // 범위 기반 for문(Range-based for loop)으로 배열 전체 순회
    for (const FString& ItemName : InventoryArray)
    {
        UE_LOG(LogTemp, Log, TEXT("[TArray] 소지품: %s"), *ItemName);
    }

    // ==============================================================================
    // [예시 문제 1: TArray] 
    // Q: 만약 위 코드 실행 후 배열이 ["기본 단검", "빨간 포션", "나무 방패"] 상태일 때,
    //    InventoryArray.RemoveAt(0); 을 실행하면 인덱스 0번의 값은 무엇이 될까요?
    // 
    // A: "빨간 포션"이 됩니다. (출력 결과: "빨간 포션")
    //    이유: 0번 인덱스의 "기본 단검"이 삭제되면, 뒤에 있던 요소들이 메모리 빈 공간을 채우기 위해 
    //         앞으로 한 칸씩 당겨지기(Shift) 때문입니다.
    // ==============================================================================


    // ==============================================================================
    // 2. TSet 사용법
    // ==============================================================================
    
    UniqueItemIDs.Add(101);
    UniqueItemIDs.Add(102);
    UniqueItemIDs.Add(101); // 101은 이미 존재하므로 추가되지 않고 무시됨 (고유성 보장)

    // Contains: 특정 요소가 존재하는지 확인. TArray의 Contains보다 월등히 빠릅니다.
    if (UniqueItemIDs.Contains(102))
    {
        UE_LOG(LogTemp, Warning, TEXT("[TSet] 102번 ID를 가진 아이템을 보유 중입니다."));
    }

    // Remove: 특정 요소 제거
    UniqueItemIDs.Remove(101);

    // ==============================================================================
    // [예시 문제 2: TSet]
    // Q: 빈 TSet에 Add(10), Add(20), Add(10)을 차례대로 수행한 후, UniqueItemIDs.Num() (개수)를 호출하면 
    //    결과값은 얼마가 나올까요?
    // 
    // A: 2가 나옵니다. (출력 결과: 2)
    //    이유: TSet은 '중복을 허용하지 않는' 집합입니다. 처음에 들어간 10은 저장되지만, 
    //         마지막에 들어온 10은 이미 존재하는 값이므로 무시되기 때문입니다.
    // ==============================================================================


    // ==============================================================================
    // 3. TMap 사용법
    // ==============================================================================
    
    // Add / Emplace: 키와 값을 쌍으로 추가
    ItemPrices.Emplace(TEXT("파란 포션"), 200);
    ItemPrices.Emplace(TEXT("철검"), 1500);

    // Find: 키를 던져주면, 해당하는 Value의 "포인터"를 반환합니다.
    // 만약 찾으려는 키가 존재하지 않는다면 nullptr를 반환하므로, 반드시 if문으로 체크해야 안전합니다.
    if (int32* FoundPrice = ItemPrices.Find(TEXT("철검")))
    {
        // 포인터를 역참조(*)하여 실제 값을 가져옴
        UE_LOG(LogTemp, Warning, TEXT("[TMap] 철검의 가격은 %d 골드입니다."), *FoundPrice);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("[TMap] 해당 아이템은 상점에 존재하지 않습니다."));
    }

    // 키를 이용해 특정 데이터(키-값 쌍) 삭제
    ItemPrices.Remove(TEXT("파란 포션"));

    // TMap 순회: TPair라는 구조체(Key, Value 변수를 가짐)를 사용하여 전체를 순회합니다.
    for (const TPair<FString, int32>& Pair : ItemPrices)
    {
        UE_LOG(LogTemp, Log, TEXT("[TMap] 상점 물품: %s / 가격: %d"), *Pair.Key, *Pair.Value);
    }

    // ==============================================================================
    // [예시 문제 3: TMap]
    // Q: ItemPrices 맵에 Add("성검", 5000)을 하고 난 뒤, FString* Val = ItemPrices.Find("마검"); 을 
    //    호출했습니다. 이때 Val에 들어있는 값과, if(Val) 조건문을 통과할 수 있는지 설명하세요.
    // 
    // A: Val에는 nullptr (메모리 주소 0)이 들어갑니다. 따라서 if(Val) 조건문은 거짓(False)이 되어 통과할 수 없습니다.
    //    이유: Find 함수는 해당 키("마검")가 딕셔너리에 없을 경우 안전을 위해 nullptr를 반환하기 때문입니다.
    //         그래서 언리얼 시험이나 실무에서는 항상 if(int32* Val = Map.Find(Key)) 형태로 
    //         널(Null) 체크를 먼저 하는 것이 필수입니다.
    // ==============================================================================
}
