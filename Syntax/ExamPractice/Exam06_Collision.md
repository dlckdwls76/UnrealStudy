# [6장] 충돌(Collision) 시스템 심화 예상 문제

## 문제 1. SetActorLocation과 스윕(Sweep) 기능
다음 코드는 런타임 중에 액터의 위치를 `TargetPos` 좌표로 강제 이동시키는 코드이다. 두 번째 인자인 `true(bSweep)`가 켜져 있을 때 발생하는 물리적 현상으로 가장 정확한 것은?

```cpp
SetActorLocation(TargetPos, true);
```

1) 목적지까지 텔레포트하는 즉시 경로에 있는 모든 Overlap 이벤트를 무시한다.
2) 출발지에서 목적지까지 이동하는 경로를 가상의 빗자루처럼 쓸면서 검사하여, 중간에 Block 설정된 벽돌이 있으면 벽을 뚫지 못하고 그 자리에 멈춘다.
3) 경로에 있는 물체를 뚫고 지나가되, 부딪힌 물체의 내구도를 깎는다(Sweep 대미지).
4) `Hit` 이벤트는 발생시키지만 무조건 목적지인 `TargetPos`까지 도달한다.

## 문제 2. Overlap과 Hit 이벤트의 차이
다음 중 언리얼 엔진의 충돌 판정인 `Overlap`과 `Hit`의 차이점에 대한 설명으로 **틀린** 것은?

1) `Overlap`은 유령이 벽을 통과하듯 물리적으로 물체를 뚫고 지나갈 수 있지만, 코드로 겹쳤다는 사실(센서)은 감지할 수 있다.
2) `Hit`는 단단한 물체끼리 부딪혔을 때 발생하며, 물리적으로 더 이상 뚫고 지나가지 못하게 밀어낸다.
3) `Hit` 이벤트를 C++에서 정상적으로 발생시키려면 해당 컴포넌트의 `Simulation Generates Hit Events` 옵션이 반드시 켜져 있어야 한다.
4) 두 물체가 충돌할 때 한 물체의 콜리전이 `Overlap`이고 다른 물체가 `Block`이면, 두 물체는 서로 물리적으로 막혀버리는 `Hit` 이벤트를 발생시킨다.

## 문제 3. 콜리전 프로필(Collision Profile) 세팅
코드 상에서 박스 컴포넌트(`UBoxComponent`)의 콜리전 프리셋(프로필)을 "모든 다이내믹 객체를 막는 상태"로 변경하려고 한다. 올바른 코드는 무엇인가?

1) `BoxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);`
2) `BoxComp->SetCollisionProfileName(TEXT("BlockAllDynamic"));`
3) `BoxComp->SetGenerateOverlapEvents(true);`
4) `BoxComp->SetCollisionObjectType(ECC_Pawn);`


<br><br><br><br><br><br>
---
# 정답 및 해설

### 문제 1 정답: 2번
**해설:** 언리얼의 `Sweep` 옵션을 켜면 목표 위치로 이동하는 과정에서 충돌체(콜리전)를 빗자루 쓸듯 밀어보며 검사를 수행합니다. 벽 뚫기 버그를 방지하기 위해 사용되며, 중간에 Block 판정의 액터를 만나면 그 자리에 즉시 멈춰 서고 `Hit` 이벤트를 발생시킵니다.

### 문제 2 정답: 4번
**해설:** 언리얼 엔진의 충돌 판정은 '더 약한 판정'을 우선적으로 따라갑니다. 한쪽이 `Block(막힘)`이더라도 다른 한쪽이 `Overlap(겹침)`이면, 이 둘이 만났을 때는 뚫고 지나가는 `Overlap` 판정으로 처리됩니다. `Hit`가 발생하려면 **두 물체 모두 서로를 `Block` 하도록** 설정되어 있어야만 물리적으로 쾅 부딪힙니다.

### 문제 3 정답: 2번
**해설:** 콜리전 설정 창에 있는 프리셋 이름(예: Pawn, BlockAll, OverlapAll 등)을 코드로 한 방에 지정하려면 `SetCollisionProfileName` 함수에 문자열(`FName`)을 넘겨주는 방식이 가장 깔끔하고 실무에서 자주 쓰입니다.
