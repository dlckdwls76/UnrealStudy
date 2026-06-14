// 선언부 헤더 포함
#include "Study08AnimNode.h"
// 캐릭터 클래스의 기능(GetVelocity 등)을 사용하기 위해 포함
#include "GameFramework/Character.h"
// 무브먼트 컴포넌트(IsFalling 등)의 물리 상태를 파악하기 위해 포함
#include "GameFramework/CharacterMovementComponent.h"
// 몽타주 객체를 다루기 위해 포함
#include "Animation/AnimMontage.h"

UStudy08AnimInstance::UStudy08AnimInstance()
{
    // 클래스가 메모리에 올라올 때 가장 먼저 실행되어 쓰레기값을 방지합니다.
    CurrentSpeed = 0.0f;
    bIsFalling = false;
}

void UStudy08AnimInstance::NativeInitializeAnimation()
{
    // 부모(UAnimInstance)가 가진 기본 초기화 로직을 보장하기 위해 Super를 부릅니다.
    Super::NativeInitializeAnimation();
}

void UStudy08AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    // ----------------------------------------------------
    // 실무 애니메이션 데이터 추출 로직
    // ----------------------------------------------------
    
    // TryGetPawnOwner()는 현재 이 애니메이션 블루프린트를 입고 있는 '주인님(Pawn 껍데기)'의 포인터를 반환합니다.
    APawn* OwnerPawn = TryGetPawnOwner();
    
    // 주인님이 실제로 존재할 때만(에디터 미리보기 창 등이 아닐 때) 연산을 수행합니다. C++의 기본인 안전한 널(nullptr) 체크입니다.
    if (OwnerPawn)
    {
        // 1. 현재 속도(Speed) 계산: 
        // GetVelocity()로 얻어낸 3D 방향 벡터(방향+힘)의 크기(Size)를 구하면 순수한 스칼라 속력이 됩니다.
        CurrentSpeed = OwnerPawn->GetVelocity().Size();

        // 2. 주인님(APawn)을 더 구체적인 ACharacter 타입으로 형변환(Casting)합니다.
        // 왜냐하면 점프와 관련된 무브먼트 컴포넌트는 APawn이 아니라 ACharacter만 가지고 있기 때문입니다.
        ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerPawn);
        
        // 형변환에 성공했고, 무브먼트 컴포넌트도 정상적으로 존재한다면
        if (OwnerCharacter && OwnerCharacter->GetCharacterMovement())
        {
            // 무브먼트 컴포넌트가 계산해둔 "지금 떨어지고 있는 중인가?" (IsFalling) 정보를 그대로 뺏어와 내 변수에 저장합니다.
            // 이 값 덕분에 캐릭터가 허공에 떴을 때 즉시 '점프/낙하' 애니메이션으로 상태 전이(Transition)가 일어납니다.
            bIsFalling = OwnerCharacter->GetCharacterMovement()->IsFalling();
        }
    }
}

void UStudy08AnimInstance::PlayAttackMontage()
{
    // ----------------------------------------------------
    // 몽타주 재생과 노티파이(Notify)
    // ----------------------------------------------------
    // 에디터에서 AttackMontage 변수에 몽타주 에셋을 슬롯에 잘 넣어뒀다면 if문을 통과합니다.
    if (AttackMontage)
    {
        // Montage_Play는 UAnimInstance에서 제공하는 함수로, 
        // 하체의 걷기/뛰기 상태 머신을 무시하고 특정 Slot(예: DefaultSlot) 노드를 통해 강제로 애니메이션을 덮어씌웁니다.
        // 두 번째 인자(1.0f)는 재생 배속(Speed)입니다.
        Montage_Play(AttackMontage, 1.0f);
    }
}
