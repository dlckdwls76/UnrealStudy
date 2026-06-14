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

protected:
    virtual void BeginPlay() override;

private:
    // ==============================================================================
    // [6] 충돌 (Collide 관계) 심화: Hit와 Sweep
    // ==============================================================================
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Study|Collision", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UBoxComponent> CollisionBox;

    // 1. Overlap (겹침) - 유령처럼 통과하지만 센서는 작동
    UFUNCTION()
    void OnMyOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    // 2. Hit (블록/부딪힘) - 물리적으로 통과하지 못하고 벽에 부딪혔을 때 발생
    UFUNCTION()
    void OnMyComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    // ==============================================================================
    // [예시 문제 2: SetActorLocation과 Sweep]
    // Q: SetActorLocation(NewLocation, true); 코드에서 두 번째 인자로 true를 넘겨주었습니다.
    //    이 'true(bSweep)' 옵션은 어떤 역할을 하며, false일 때와 비교해서 어떤 차이가 있나요?
    // 
    // A: Sweep(스윕) 옵션을 켠 것입니다. 
    //    - true일 때: 액터가 도착 지점으로 순간이동하는 과정에서, 경로 상에 있는 벽이나 
    //               장애물(Block 콜리전)을 감지하면 그 벽에 막혀서 멈춥니다. (벽뚫기 방지)
    //    - false일 때: 경로에 벽이 있든 없든 무시하고 지정된 위치로 무조건 순간이동합니다. (벽뚫기)
    // ==============================================================================
};
