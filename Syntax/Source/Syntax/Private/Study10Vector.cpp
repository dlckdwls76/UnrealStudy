// 본인 헤더 포함
#include "Study10Vector.h"

AStudy10Vector::AStudy10Vector()
{
    // Tick 함수를 끄면 매 프레임 불필요한 연산을 안 하므로 성능이 향상됩니다.
    PrimaryActorTick.bCanEverTick = false;
}

void AStudy10Vector::BeginPlay()
{
    Super::BeginPlay();
    // 시작하자마자 벡터 계산 함수를 실행합니다.
    CalculateVectorMath();
}

void AStudy10Vector::CalculateVectorMath()
{
    // ----------------------------------------------------
    // 벡터 계산 기초
    // ----------------------------------------------------
    
    // GetActorForwardVector() 등은 항상 길이가 1인 '정규화된(Normalized)' 단위 방향 벡터를 반환합니다.
    FVector ForwardVector = GetActorForwardVector(); // 내 액터가 바라보는 앞쪽 (X축)
    FVector RightVector = GetActorRightVector();     // 내 액터의 오른쪽 (Y축)

    // 1. 내적 (Dot Product)
    // 내적은 스칼라(float 실수) 값을 반환합니다. 
    // 완전히 같은 방향이면 1.0, 90도(직교)면 0.0, 정반대 방향이면 -1.0이 나옵니다.
    float DotResult = FVector::DotProduct(ForwardVector, RightVector);
    
    // 2. 외적 (Cross Product)
    // 외적은 스칼라가 아닌 3D 벡터(FVector) 값을 반환합니다. 
    // X축(Forward)과 Y축(Right)을 외적하면, 왼손/오른손 법칙에 의해 위쪽을 향하는 Z축(Up) 방향의 벡터가 튀어나옵니다.
    FVector CrossResult = FVector::CrossProduct(ForwardVector, RightVector);

    // 결과 로그 출력
    UE_LOG(LogTemp, Warning, TEXT("Forward와 Right의 내적: %f (직교하므로 0)"), DotResult);
    UE_LOG(LogTemp, Warning, TEXT("Forward와 Right의 외적: %s (Up 방향 벡터)"), *CrossResult.ToString());
}
