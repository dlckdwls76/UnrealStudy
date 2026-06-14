// 헤더 중복 포함 방지 매크로
#pragma once

// 엔진 필수 코어 기능 포함
#include "CoreMinimal.h"
// UAnimInstance(애니메이션 블루프린트의 C++ 부모 클래스)를 상속받기 위해 포함
#include "Animation/AnimInstance.h"
// 리플렉션 자동 생성 코드 포함 (항상 마지막에 위치해야 함)
#include "Study08AnimNode.generated.h"

// ==============================================================================
// [8] 애니메이션 노드와 시스템 심화 (UAnimInstance)
// ==============================================================================
// 이전에는 캐릭터(ACharacter)에서 테스트했지만, 실제 언리얼 실무에서 애니메이션 로직은 
// 무조건 애니메이션 블루프린트의 부모 클래스인 'UAnimInstance'를 상속받아 C++로 작성합니다.
// 이 클래스에서 캐릭터의 상태를 감시해 변수(Speed 등)로 만들고, 블루프린트 애님그래프(AnimGraph)가 이 변수를 읽어갑니다.

// 리플렉션 시스템 등록
UCLASS()
class SYNTAX_API UStudy08AnimInstance : public UAnimInstance // UAnimInstance를 상속받음
{
    GENERATED_BODY() // 필수 매크로
    
public:
    // 생성자: 클래스가 생성될 때 기본값 초기화
    UStudy08AnimInstance();

    // ----------------------------------------------------
    // 애니메이션 틱(Tick)과 초기화 
    // ----------------------------------------------------
    
    // 애니메이션 블루프린트가 최초로 로드되고 초기화될 때 딱 1번 호출됩니다.
    // (보통 캐릭터 포인터를 Cast해서 미리 저장(캐싱)해두는 최적화 용도로 씁니다)
    virtual void NativeInitializeAnimation() override;

    // 일반 액터의 Tick()처럼 매 프레임마다 호출되는 애니메이션 전용 업데이트 함수입니다.
    // 여기서 속도, 점프 상태 등을 실시간으로 갱신해야 애니메이션이 부드럽게 전환됩니다.
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    // 블루프린트 노드에서 이 함수를 호출할 수 있도록 UFUNCTION 매크로를 달았습니다.
    UFUNCTION(BlueprintCallable, Category = "Study|Animation")
    void PlayAttackMontage();

protected:
    // 블렌드 스페이스(Blend Space) 노드의 X축 좌표(Speed)로 넘겨줄 실수(float) 변수입니다.
    // BlueprintReadOnly로 선언해야 블루프린트 애님그래프에서 이 값을 꺼내어 선을 연결할 수 있습니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Study|Animation")
    float CurrentSpeed;

    // 상태 머신(State Machine)에서 "떨어지는 중인가?" 화살표 조건(Transition Rule)을 만족시킬 부울(bool) 변수입니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Study|Animation")
    bool bIsFalling;

    // 에디터에서 재생할 몽타주 에셋을 할당받을 포인터 변수입니다.
    // 몽타주는 걷기/뛰기 상태를 무시하고 강제로 공격 등의 애니메이션을 덮어씌울 때 사용합니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Study|Animation")
    TObjectPtr<class UAnimMontage> AttackMontage;

    // ==============================================================================
    // [예시 문제: AnimInstance의 데이터 갱신]
    // Q: 매 프레임 캐릭터의 속도(Speed)를 계산해 애니메이션 블루프린트의 변수에 반영하려면, 
    //    UAnimInstance 클래스 내부의 어떤 가상 함수(Virtual Function)를 오버라이드(Override)해야 할까요?
    // 
    // A: NativeUpdateAnimation(float DeltaSeconds)
    //    해설: 일반 액터의 Tick() 함수와 똑같은 역할을 하며, 애니메이션 시스템이 매 프레임 
    //         자동으로 이 함수를 부르기 때문에 여기서 위치나 속도를 계산해야 부드러운 전환이 일어납니다.
    // ==============================================================================
};
