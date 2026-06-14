// 헤더 중복 포함 방지
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Study11Container.generated.h"

UCLASS()
class SYNTAX_API AStudy11Container : public AActor
{
    GENERATED_BODY()
    
public:    
    AStudy11Container();

protected:
    virtual void BeginPlay() override;

private:
    // ==============================================================================
    // [11] TArray, TSet, TMap의 주요 멤버 함수 정리
    // ==============================================================================
    void TestContainerFunctions();

    // ==============================================================================
    // [예시 문제: TMap의 Find 반환형]
    // Q: TMap<int32, FString> MyMap; 딕셔너리가 선언되어 있습니다. 
    //    여기서 MyMap.Find(1); 을 호출하면 어떤 타입의 데이터가 반환(Return)되며, 왜 그런 타입을 반환할까요?
    // 
    // A: 1) 반환 타입: FString* (문자열의 포인터형)
    //    2) 해설: 우리가 찾으려는 키(1번 키)가 딕셔너리 내부에 없을 경우, 
    //            에러를 내며 크래시를 내지 않고 "찾지 못했습니다"라는 뜻의 널 포인터(nullptr)를 안전하게 
    //            던져주기 위해 설계된 언리얼의 C++ 방식입니다. 
    //            따라서 항상 if (FString* Val = MyMap.Find(1)) 형태로 널 체크를 동반해야 합니다.
    // ==============================================================================
};
