#include "Study07CharAsset.h"
#include "GameFramework/CharacterMovementComponent.h"

AStudy07CharAsset::AStudy07CharAsset()
{
    PrimaryActorTick.bCanEverTick = false;

    // ----------------------------------------------------
    // 캐릭터 에셋 제어 예시
    // ----------------------------------------------------
    
    // 1. 메시(Skeletal Mesh) 제어
    // 캡슐 컴포넌트가 루트이므로 메시는 보통 정중앙에 위치합니다. 
    // 발을 캡슐의 바닥으로 내리고 시선을 맞추기 위해 Z축을 -90도, 회전값도 -90도 틀어주는 것이 국룰 세팅입니다.
    if (GetMesh())
    {
        GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
        GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
    }

    // 2. 캐릭터 무브먼트(Movement) 제어
    // 중력, 걷기 속도, 마찰력, 점프력 등을 코드로 설정합니다.
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = 500.0f; // 최대 걷기 속도
        GetCharacterMovement()->JumpZVelocity = 400.0f; // 위쪽(Z)으로 튀어오르는 점프 힘
    }
}

void AStudy07CharAsset::BeginPlay()
{
    Super::BeginPlay();
}
