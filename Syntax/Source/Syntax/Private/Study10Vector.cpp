#include "Study10Vector.h"

AStudy10Vector::AStudy10Vector()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AStudy10Vector::BeginPlay()
{
    Super::BeginPlay();
    CalculateVectorMath();
}

void AStudy10Vector::CalculateVectorMath()
{
    // ----------------------------------------------------
    // 벡터 계산 기초
    // ----------------------------------------------------
    
    // GetActorForwardVector() 등은 항상 길이가 1인 '정규화된(Normalized)' 단위 벡터를 반환합니다.
    FVector ForwardVector = GetActorForwardVector();
    FVector RightVector = GetActorRightVector();

    // 1. 내적 (Dot Product)
    // 스칼라(float) 값을 반환합니다. 두 벡터가 정확히 같은 방향이면 1.0, 직교하면 0.0, 정반대면 -1.0입니다.
    float DotResult = FVector::DotProduct(ForwardVector, RightVector);
    
    // 2. 외적 (Cross Product)
    // 벡터(FVector) 값을 반환합니다. X축(Forward)과 Y축(Right)을 외적하면 Z축(Up) 방향의 벡터가 튀어나옵니다.
    FVector CrossResult = FVector::CrossProduct(ForwardVector, RightVector);

    UE_LOG(LogTemp, Warning, TEXT("Forward와 Right의 내적: %f (직교하므로 0)"), DotResult);
    UE_LOG(LogTemp, Warning, TEXT("Forward와 Right의 외적: %s (Up 방향 벡터)"), *CrossResult.ToString());
}
