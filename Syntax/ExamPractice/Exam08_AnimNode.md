# [8장] 애니메이션 인스턴스 (UAnimInstance) 예상 문제

## 문제 1
다음은 C++ 기반의 `UAnimInstance`에서 캐릭터의 현재 속력(Speed)을 계산하여 애니메이션 상태를 업데이트하는 코드이다. 빈칸 (A), (B)에 들어갈 코드로 알맞은 것은?

```cpp
void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    // 이 애니메이션을 재생 중인 실제 캐릭터 껍데기(Pawn)의 주소를 가져온다.
    APawn* OwnerPawn = [   (A)   ]();

    if (OwnerPawn)
    {
        // 3D 벡터인 Velocity를 스칼라(실수) 형태의 속력(Speed)으로 변환한다.
        CurrentSpeed = OwnerPawn->GetVelocity().[   (B)   ]();
    }
}
```

1) (A): `GetOwnerActor` / (B): `Length`
2) (A): `TryGetPawnOwner` / (B): `Size`
3) (A): `GetPlayerCharacter` / (B): `Normalize`
4) (A): `TryGetPawnOwner` / (B): `DotProduct`

---
### 정답 및 해설
**정답: 2번 ((A): TryGetPawnOwner / (B): Size)**
**해설:** `UAnimInstance`에서 자신을 입고 있는 폰을 안전하게 가져오는 함수는 `TryGetPawnOwner()`입니다. 그리고 3D 방향 벡터(`FVector`)의 길이(스칼라 크기)를 반환하여 순수한 속력(Speed)을 도출하는 함수는 `Size()` (또는 `Length()`)입니다.
