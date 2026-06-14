#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Study12ObjectPtr.generated.h"

UCLASS()
class SYNTAX_API AStudy12ObjectPtr : public AActor
{
    GENERATED_BODY()
    
public:    
    AStudy12ObjectPtr();

protected:
    virtual void BeginPlay() override;

private:
    // ==============================================================================
    // [12] TObjectPtr, TSubclassOf
    // ==============================================================================
    
    // TObjectPtr: 언리얼 5부터 기존 로우 포인터(AActor*)를 대체하는 최신 포인터 타입입니다.
    // 에디터에서 객체 참조를 지연 로딩하거나 디버깅/추적할 때 압도적으로 안전하고 빠릅니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Study|Pointers", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<AActor> TargetActor;

    // TSubclassOf: 실체(인스턴스)가 아닌 "클래스(타입) 정보"만 보관하는 변수입니다.
    // AActor를 상속받은 무수히 많은 블루프린트 중에서만 고를 수 있게 디테일 패널을 필터링해주는 마법을 부립니다.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Study|Pointers", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AActor> ActorClassToSpawn;

    void TestSpawning();

    // ==============================================================================
    // [예시 문제: TSubclassOf]
    // Q: "AMonster" 라는 C++ 클래스를 상속받아 여러 종류의 블루프린트 몬스터(BP_Orc, BP_Troll 등)를 만들었습니다.
    //    개발자가 에디터 창에서 이 수많은 몬스터 템플릿 중 하나를 '선택'할 수 있는 변수를 만들려고 합니다.
    //    타입란(빈칸)에 들어가야 할 올바른 템플릿 코드는 무엇일까요?
    //    UPROPERTY(EditAnywhere)
    //    [        빈 칸        ] MonsterClassToSpawn;
    // 
    // A: TSubclassOf<AMonster>
    // ==============================================================================
};
