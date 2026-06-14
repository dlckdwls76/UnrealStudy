#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Study06Collision.generated.h"

class UBoxComponent;

UCLASS()
class SYNTAX_API AStudy06Collision : public AActor
{
    GENERATED_BODY()
    
public:    
    AStudy06Collision();

private:
    // ==============================================================================
    // [6] 충돌 (Collide 관계)
    // ==============================================================================
    // 특징: 언리얼은 물리 연산을 위해 충돌 컴포넌트(Box, Sphere, Capsule 등)를 사용합니다.
    //      물리적으로 막히는 '블록(Block)'과 통과하되 신호만 주는 '오버랩(Overlap)' 두 가지가 핵심입니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Study|Collision", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UBoxComponent> CollisionBox;

    // 델리게이트 바인딩 대상 함수는 반드시 리플렉션 시스템이 알아야 하므로 UFUNCTION 매크로가 필수입니다.
    UFUNCTION()
    void OnMyOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    // ==============================================================================
    // [예시 문제: 충돌 (Collision)]
    // Q: 캐릭터가 아이템에 닿았을 때 아이템을 튕겨내지 않고 통과하면서 '획득' 처리를 하려고 합니다.
    //    이때 두 물체의 콜리전 반응(Collision Response)은 서로 무엇으로 설정되어야 하며,
    //    C++ 코드에서 콜백 함수를 바인딩할 때 대상 함수 위에 반드시 붙여야 하는 매크로는 무엇일까요?
    // 
    // A: 1) 콜리전 반응: '오버랩(Overlap)'으로 설정되어야 합니다.
    //    2) 필수 매크로: UFUNCTION()
    //    (AddDynamic은 리플렉션 시스템을 이용해 이름을 기반으로 함수를 찾으므로 UFUNCTION이 없으면 바인딩에 실패합니다.)
    // ==============================================================================
};
