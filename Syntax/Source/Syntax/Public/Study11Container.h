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
    // Q: TMap<int32, FString> MyMap; 가 선언되어 있습니다. 
    //    MyMap.Find(1); 을 호출하면 어떤 타입의 데이터가 반환(Return)되며, 왜 그런 타입을 반환할까요?
    // 
    // A: 1) 반환 타입: FString* (문자열의 포인터형)
    //    2) 이유: 해당 키(1)가 딕셔너리 내부에 존재하지 않을 경우를 대비하여 
    //            존재하지 않음을 안전하게 표현하기 위해 nullptr를 던져주기 위함입니다.
    // ==============================================================================
};
