#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Study07CharAsset.generated.h"

UCLASS()
class SYNTAX_API AStudy07CharAsset : public ACharacter
{
    GENERATED_BODY()

public:
    AStudy07CharAsset();

protected:
    virtual void BeginPlay() override;

private:
    // ==============================================================================
    // [7] 캐릭터를 구성하는 주요 에셋
    // ==============================================================================
    // 특징: ACharacter 클래스는 폰(APawn)을 상속받은 특수한 클래스로, 인간형 캐릭터를 만들기 위한 
    //      핵심 컴포넌트 3대장을 기본적으로 탑재하고 있습니다.
    // 
    // 1. UCapsuleComponent: 캡슐 모양의 충돌체. 캐릭터의 피격/충돌 판정을 담당 (RootComponent)
    // 2. USkeletalMeshComponent: 뼈대가 있는 외형 모델링 및 애니메이션 (Mesh)
    // 3. UCharacterMovementComponent: 걷기, 점프, 수영, 비행, 낙하 등 완벽한 이동 물리 로직을 제공 (Movement)

    // ==============================================================================
    // [예시 문제: 캐릭터 기본 에셋]
    // Q: 캐릭터가 너무 높이 점프해서, 점프 높이를 절반으로 줄이려고 합니다. 
    //    ACharacter 클래스 내부에서 어떤 컴포넌트를 가져와서 수치를 조정해야 할까요? 
    //    (해당 컴포넌트를 가져오는 함수 이름과 컴포넌트 클래스 명을 적으세요)
    // 
    // A: 1) 함수 이름: GetCharacterMovement()
    //    2) 컴포넌트 클래스 명: UCharacterMovementComponent
    //    (접근하여 JumpZVelocity 변수 값을 수정하면 점프력을 조절할 수 있습니다.)
    // ==============================================================================
};
