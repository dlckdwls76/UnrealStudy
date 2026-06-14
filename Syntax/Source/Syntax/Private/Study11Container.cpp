#include "Study11Container.h"

AStudy11Container::AStudy11Container()
{
    // 불필요한 Tick 연산 제거
    PrimaryActorTick.bCanEverTick = false;
}

void AStudy11Container::BeginPlay()
{
    Super::BeginPlay();
    // 게임 시작 시 컨테이너(자료구조) 테스트 돌입
    TestContainerFunctions();
}

void AStudy11Container::TestContainerFunctions()
{
    // [11. 자료구조 핵심 멤버 함수 완벽 해설]

    // 1. TArray (순서가 있는 동적 배열)
    TArray<int32> MyArray;
    // Add: 데이터를 뒤에 밀어 넣습니다. (객체의 경우 메모리 복사가 일어나 성능이 약간 저하됨)
    MyArray.Add(10);        
    // Emplace: 데이터를 뒤에 밀어 넣되, 복사하지 않고 해당 메모리 번지에서 직접 생성(Construct)하여 성능이 훨씬 좋습니다. (언리얼 실무 권장)
    MyArray.Emplace(20);    
    // Remove: 배열을 전부 뒤져서 '10'이라는 값을 가진 모든 칸을 지워버립니다.
    MyArray.Remove(10);     
    // RemoveAt: 값과 상관없이 무조건 '0번째' 칸을 날려버립니다. (뒤에 있던 요소들이 앞으로 당겨집니다)
    MyArray.RemoveAt(0);    

    // 2. TSet (순서가 없고 중복을 불허하는 집합)
    TSet<FString> MySet;
    // Add: 내부적으로 해시(Hash)를 계산하여 들어갑니다. 같은 값을 넣으면 무시됩니다.
    MySet.Add(TEXT("Item"));
    // Contains: 이 집합 안에 "Item"이 있는지 검색합니다. 해시 덕분에 TArray의 검색 속도와는 비교도 안 되게 빠릅니다. (O(1))
    bool bContains = MySet.Contains(TEXT("Item")); 
    // Remove: 특정 값을 지웁니다.
    MySet.Remove(TEXT("Item")); 

    // 3. TMap (Key-Value 딕셔너리)
    TMap<int32, FString> MyMap;
    // Add: 1번이라는 열쇠(Key)에 "Value"라는 내용물(Value)을 매핑합니다.
    MyMap.Add(1, TEXT("Value"));
    
    // Find: 키를 던지면 포인터를 반환합니다. 반드시 if문 안에 변수 선언을 함께 하여 nullptr 체크를 하는 것이 전공자의 정석입니다.
    if (FString* FoundVal = MyMap.Find(1)) 
    {
        // FoundVal은 포인터형이므로 내용물을 꺼내려면 역참조(*)를 해야 합니다.
        // 그리고 로그(UE_LOG)에 문자열을 넣을 때는 언리얼 FString을 C언어 스타일 문자열로 바꾸는 또 다른 역참조(*)가 필요하므로 **FoundVal이 됩니다.
        UE_LOG(LogTemp, Warning, TEXT("Find Value: %s"), **FoundVal); 
    }
}
