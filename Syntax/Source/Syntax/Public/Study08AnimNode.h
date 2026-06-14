#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Study08AnimNode.generated.h"

class UAnimMontage;

UCLASS()
class SYNTAX_API AStudy08AnimNode : public ACharacter
{
    GENERATED_BODY()

public:
    AStudy08AnimNode();

public:
    UFUNCTION(BlueprintCallable, Category = "Study|Animation")
    void PlayAttackMontage();

private:
    // ==============================================================================
    // [8] 애니메이션 노드 4대장 요약
    // ==============================================================================
    // 1. 블렌드 스페이스 (Blend Space): 캐릭터의 현재 '속도(Speed)'나 '방향(Direction)' 같은 실수 값에 따라 걷기, 뛰기 애니메이션을 부드럽게 섞어(보간) 줍니다.
    // 2. 몽타주 (Montage): 기본 걷기 상태를 무시하고 덮어씌워 강제로 재생하는 애니메이션(예: 공격, 피격). C++에서 가장 많이 호출합니다.
    // 3. 레이어드 블렌드 퍼 본 (Layered Blend Per Bone): 척추뼈(Spine) 같은 특정 뼈대를 기점으로, 하체는 계속 '뛰기' 애니메이션을 하면서 상체만 '총 장전' 애니메이션을 합성할 때 씁니다.
    // 4. 에임 오프셋 (Aim Offset): 마우스 방향(Pitch, Yaw)에 따라 상체 뼈대만 위/아래/좌/우를 조준하도록 여러 포즈를 합성하는 기능입니다.
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Study|Animation", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAnimMontage> AttackAnimMontage;

    // ==============================================================================
    // [예시 문제: 애니메이션 노드]
    // Q: 캐릭터가 달리면서(하체 이동) 동시에 총을 쏘거나 재장전(상체 행동)하려고 합니다. 
    //    애니메이션 블루프린트의 AnimGraph에서 이 두 가지 애니메이션을 하나의 포즈로 합치기 
    //    위해 사용하는 합성 노드의 정확한 이름은 무엇인가요?
    // 
    // A: Layered Blend Per Bone (본 별 레이어 블렌드) 입니다.
    // ==============================================================================
};
