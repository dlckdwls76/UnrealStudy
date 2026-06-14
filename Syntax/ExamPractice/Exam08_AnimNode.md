# [8장] 애니메이션 인스턴스 (UAnimInstance) 심화 예상 문제

## 문제 1. 데이터 업데이트 시점
`UAnimInstance`에서 캐릭터의 이동 속도(Speed)나 공중에 떠 있는지 여부(IsFalling)를 계산하여 애니메이션 변수를 갱신하려고 한다. 일반 액터의 `Tick()` 함수처럼 매 프레임 애니메이션 엔진에 의해 자동으로 호출되는 가상 함수(Virtual Function)는 무엇인가?

1) `NativeInitializeAnimation()`
2) `NativeUpdateAnimation(float DeltaSeconds)`
3) `TryGetPawnOwner()`
4) `Montage_Play()`

## 문제 2. 무브먼트 상태 캐스팅과 판단
다음 코드는 애님 인스턴스에서 캐릭터가 허공에 떠 있는지 검사하는 코드이다. 빈칸 (A), (B)에 들어갈 올바른 함수와 타입은?

```cpp
APawn* OwnerPawn = TryGetPawnOwner();
if (OwnerPawn)
{
    // 점프/낙하 상태는 APawn에는 없고 ACharacter만 가진 물리 컴포넌트에 있으므로 캐스팅이 필요합니다.
    [   (A)   ]* OwnerCharacter = Cast<[   (A)   ]>(OwnerPawn);
    
    if (OwnerCharacter && OwnerCharacter->GetCharacterMovement())
    {
        // 무브먼트 컴포넌트에서 체공 상태를 알아내는 함수
        bIsFalling = OwnerCharacter->GetCharacterMovement()->[   (B)   ]();
    }
}
```

1) (A) `AActor` / (B) `IsJumping`
2) (A) `ACharacter` / (B) `IsFalling`
3) (A) `APlayerController` / (B) `IsFlying`
4) (A) `UAnimInstance` / (B) `IsInAir`

## 문제 3. 애니메이션 몽타주(Montage)의 기능
애니메이션 몽타주(`UAnimMontage`) 시스템이 제공하는 고유의 강력한 기능이 **아닌** 것은?

1) 캐릭터의 걷기/뛰기 같은 블렌드 스페이스 상태 머신 로직을 무시하고, 특정 슬롯(Slot)을 통해 강제로 공격이나 피격 모션을 덮어씌울 수 있다.
2) 타임라인 특정 프레임(시간대)에 '애님 노티파이(Anim Notify)'를 심어 소리를 재생하거나 파티클을 터뜨리고 콤보 공격을 제어하는 등 정밀한 타이밍 제어가 가능하다.
3) 무기를 휘두를 때 상체는 공격 애니메이션을 틀면서 하체는 계속 뛰어다닐 수 있게 뼈대 레이어를 분리할 수 있다.
4) 언리얼 엔진의 C++ 가비지 컬렉션을 무시하고 컴포넌트 메모리를 영구적으로 보호하는 역할을 한다.

## 문제 4. 포인터 널 체크 누락 (코드 예측)
`NativeUpdateAnimation` 함수 내부에 다음과 같이 코드를 작성했다. 발생할 수 있는 가장 치명적인 문제는 무엇인가?

```cpp
void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    // 널 체크(if문) 없이 즉시 캐스팅 후 역참조
    ACharacter* MyChar = Cast<ACharacter>(TryGetPawnOwner());
    CurrentSpeed = MyChar->GetVelocity().Size();
}
```

1) 블루프린트에서 변수값을 덮어써서 속도가 무조건 0이 된다.
2) 맵 로딩 화면이나 캐릭터가 아직 완전히 월드에 스폰되지 않은 찰나의 순간에 `TryGetPawnOwner()`가 nullptr을 반환하며, 널 포인터를 역참조하여 무조건 **엔진 크래시**가 터진다.
3) 애니메이션이 2배속으로 빠르게 재생된다.
4) 컴파일 에러가 발생하여 빌드가 막힌다.

## 문제 5. 몽타주 재생 함수 (빈칸 채우기)
C++ 캐릭터 코드에서 몬스터가 공격할 때 내가 만든 공격 몽타주(`AttackMontage`)를 강제 재생시키려고 한다. 빈칸에 들어갈 알맞은 구조는?

```cpp
void AMonster::PlayAttackAnim()
{
    UAnimInstance* AnimInst = Mesh->GetAnimInstance();
    if (AnimInst && AttackMontage)
    {
        AnimInst->[    (A)    ](AttackMontage, 1.0f); // 1.0f는 재생 속도
    }
}
```

1) `PlayAnimation`
2) `Montage_Play`
3) `Anim_Start`
4) `ForcePlay`


<br><br><br><br><br><br>
---
# 정답 및 해설

### 문제 1 정답: 2번 (`NativeUpdateAnimation`)
**해설:** `NativeUpdateAnimation`은 애니메이션 시스템의 핵심 심장부로, 매 틱(프레임)마다 불리며 이 안에서 캐릭터의 속도나 점프 상태를 감시해 갱신해야, 블루프린트의 애님그래프(AnimGraph)가 이 변수를 실시간으로 읽어가서 부드러운 애니메이션 전환을 수행할 수 있습니다.

### 문제 2 정답: 2번 ((A) `ACharacter` / (B) `IsFalling`)
**해설:** 걷기, 수영, 점프 등 복잡한 물리 계산은 단순한 `APawn` 껍데기가 아니라 그 자식인 `ACharacter`의 전유물인 `UCharacterMovementComponent`가 담당합니다. 따라서 반드시 `ACharacter`로 캐스팅(형변환)해야 이동 컴포넌트에 접근할 수 있으며, 이 컴포넌트가 제공하는 `IsFalling()` 함수가 공중에 떴는지 여부를 정확히 `true/false`로 알려줍니다.

### 문제 3 정답: 4번
**해설:** 몽타주는 애니메이션의 강제 재생, 슬롯 오버라이딩, 노티파이를 통한 타이밍 로직 처리, 상하체 분리 블렌딩 등을 위한 애니메이션 시퀀스 도구이지, 물리적 메모리 관리나 가비지 컬렉션(GC)을 제어하는 기능과는 전혀 무관합니다.

### 문제 4 정답: 2번 (엔진 크래시)
**해설:** 언리얼 엔진에서 포인터 널 체크(`if(MyChar)`)를 하지 않고 `->` 로 변수나 함수에 접근하면 가장 무서운 'Null Pointer 역참조(Access Violation)' 크래시가 100% 터집니다. 특히 애니메이션 시스템은 폰이 완전히 스폰되기 전 찰나의 순간(초기화 로딩 타이밍)에도 틱이 돌 수 있어 각별히 주의해야 합니다.

### 문제 5 정답: 2번 (`Montage_Play`)
**해설:** 몽타주 에셋은 스켈레탈 메시의 `UAnimInstance` 객체에서 제공하는 내장 함수인 `Montage_Play`를 통해 호출해야 블렌드 스페이스를 뚫고 강제로 덮어씌워지며 재생됩니다.
