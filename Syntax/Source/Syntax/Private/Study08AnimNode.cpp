#include "Study08AnimNode.h"
#include "Animation/AnimMontage.h"

AStudy08AnimNode::AStudy08AnimNode()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AStudy08AnimNode::PlayAttackMontage()
{
    // [8. 애니메이션 노드 (몽타주 재생 실전)]
    // 몽타주는 애니메이션 블루프린트 내부의 'Slot' 노드를 통해 재생됩니다.
    // C++에서 이 함수를 부르면, 상태 머신(걷기/뛰기)이 멈추거나 덮어씌워지면서 공격 애니메이션이 강제 재생됩니다.
    if (AttackAnimMontage)
    {
        PlayAnimMontage(AttackAnimMontage, 1.0f);
    }
}
