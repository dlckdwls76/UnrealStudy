#include "Study07CharAsset.h"
#include "GameFramework/CharacterMovementComponent.h"

AStudy07CharAsset::AStudy07CharAsset()
{
    PrimaryActorTick.bCanEverTick = false;

    if (GetMesh())
    {
        GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
        GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
    }

    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = 500.0f; 
        GetCharacterMovement()->JumpZVelocity = 400.0f; 
        
        // ----------------------------------------------------
        // 심화: 캐릭터의 몸체 회전 제어 (3인칭 RPG 국룰 세팅)
        // ----------------------------------------------------
        
        // 1. 마우스를 돌린다고 해서 캐릭터 몸체가 바로 휙휙 돌아가지 않게 막음
        bUseControllerRotationPitch = false;
        bUseControllerRotationYaw = false;
        bUseControllerRotationRoll = false;

        // 2. 대신, 캐릭터가 걷고 있는 "이동하는 방향"을 쳐다보며 몸을 부드럽게 돌리도록 설정함
        GetCharacterMovement()->bOrientRotationToMovement = true;
        
        // 3. 캐릭터가 돌아가는 속도 (Z축 회전(Yaw) 초당 540도 속도)
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
    }
}

void AStudy07CharAsset::BeginPlay()
{
    Super::BeginPlay();
}
