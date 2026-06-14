#include "Study11Container.h"

AStudy11Container::AStudy11Container()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AStudy11Container::BeginPlay()
{
    Super::BeginPlay();
    TestContainerFunctions();
}

void AStudy11Container::TestContainerFunctions()
{
    // [11. 자료구조 핵심 멤버 함수]

    // 1. TArray (동적 배열)
    TArray<int32> MyArray;
    MyArray.Add(10);        // 단순 추가 (데이터 복사 O)
    MyArray.Emplace(20);    // 메모리 내 직접 생성 (데이터 복사 X - 권장)
    MyArray.Remove(10);     // "값"을 찾아 모두 지움
    MyArray.RemoveAt(0);    // "인덱스(순번)"를 찾아 지움

    // 2. TSet (집합)
    TSet<FString> MySet;
    MySet.Add(TEXT("Item"));
    bool bContains = MySet.Contains(TEXT("Item")); // Contains 함수가 TArray보다 월등히 빠름
    MySet.Remove(TEXT("Item")); 

    // 3. TMap (딕셔너리)
    TMap<int32, FString> MyMap;
    MyMap.Add(1, TEXT("Value"));
    if (FString* FoundVal = MyMap.Find(1)) // 반환형은 무조건 포인터(*)
    {
        UE_LOG(LogTemp, Warning, TEXT("Find Value: %s"), **FoundVal); // 이중 별(**)은 언리얼 FString을 C스타일 문자열로 변환하는 연산자입니다.
    }
}
