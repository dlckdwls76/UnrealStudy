# [7장] 캐릭터 회전 제어와 입력 심화 예상 문제

## 문제 1. BindAxis와 BindAction의 차이
다음 중 플레이어의 입력을 바인딩하는 `SetupPlayerInputComponent` 함수 내에서 `BindAxis`와 `BindAction`의 역할에 대한 설명으로 올바른 것은?

1) `BindAxis`는 스페이스바처럼 딱 한 번 눌렸을 때 발동하는 점프 같은 행동에 사용된다.
2) `BindAction`은 W,A,S,D처럼 계속 꾹 누르고 있을 때마다 매 프레임 -1.0 ~ 1.0 사이의 수치(Value)를 전달받는 이동에 사용된다.
3) `BindAxis`는 조이스틱 아날로그 스틱이나 방향키처럼 누르고 있는 동안 매 프레임 연속적인 수치값을 전달받아 이동 함수를 호출할 때 사용된다.
4) 두 함수는 완전히 동일한 기능을 하며 이름만 다를 뿐이다.

## 문제 2. 3D 공간에서의 앞(Forward) 계산 로직
다음은 플레이어가 W키를 눌렀을 때 실행되는 전진(MoveForward) 함수의 일부이다. 코드를 읽고 (A)의 목적을 가장 잘 설명한 것을 고르시오.

```cpp
const FRotator Rotation = Controller->GetControlRotation(); 
const FRotator YawRotation(0, Rotation.Yaw, 0); // (A)
const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
AddMovementInput(Direction, Value);
```

1) (A)는 카메라가 바닥을 향해 숙이거나 하늘을 쳐다보는 각도(Pitch)까지 포함하여, 플레이어가 하늘을 향해 날아갈 수 있도록 해준다.
2) (A)는 카메라가 위/아래로 기울어진 각도(Pitch)와 옆으로 기울어진 각도(Roll)를 0으로 무시하고, 지면과 평행한 좌/우(Yaw) 회전 방향만 추출하여 캐릭터가 땅을 뚫거나 하늘로 날아가지 않고 수평으로만 걷게 만든다.
3) (A)는 캐릭터의 현재 이동 속도를 0으로 초기화하는 수학 연산이다.
4) (A)는 캐릭터가 무조건 절대 좌표계의 북쪽(X축 방향)으로만 이동하게 강제로 고정한다.

## 문제 3. 3인칭 RPG 회전 국룰 세팅 (오리엔트 로테이션)
카메라 시점은 마우스를 따라 자유롭게 회전하지만, 캐릭터의 몸통은 마우스를 쳐다보지 않고 "자신이 이동 키를 눌러 걸어가고 있는 방향"을 향해 부드럽게 몸을 돌리게(원신, 젤다 방식) 만들려고 한다. 
다음 중 `ACharacter` 생성자에서 설정해야 할 필수 조합으로 가장 올바른 것은?

1) `bUseControllerRotationYaw = true;` / `GetCharacterMovement()->bOrientRotationToMovement = false;`
2) `bUseControllerRotationYaw = false;` / `GetCharacterMovement()->bOrientRotationToMovement = true;`
3) `bUseControllerRotationPitch = true;` / `GetCharacterMovement()->bOrientRotationToMovement = true;`
4) `bUseControllerRotationRoll = false;` / `GetCharacterMovement()->bOrientRotationToMovement = false;`


<br><br><br><br><br><br>
---
# 정답 및 해설

### 문제 1 정답: 3번
**해설:** `BindAxis`는 입력 장치(조이스틱, 키보드 WASD)의 상태를 매 틱(프레임)마다 실수(float) 값으로 읽어오는 '연속적인' 입력 처리입니다. 반면 `BindAction`은 공격, 점프, 상호작용처럼 눌렀을 때(Pressed) 또는 뗐을 때(Released) 딱 1번만 발생하는 '단발성' 이벤트 트리거에 사용됩니다.

### 문제 2 정답: 2번
**해설:** 카메라가 바닥이나 하늘을 쳐다볼 때 그 회전값 그대로 앞(Forward) 방향 벡터를 구하면, `AddMovementInput`이 캐릭터를 하늘로 비스듬히 밀어 올리거나 땅 밑으로 파고들게 만드는 힘을 가합니다. 이를 막기 위해 위아래(Pitch)와 기울기(Roll)를 버리고, 오직 좌우 회전(Yaw) 각도만을 이용해 지면과 평행한 전진 방향(X축 벡터)을 뽑아내는 실무 필수 수학 공식입니다.

### 문제 3 정답: 2번
**해설:** 마우스를 돌린다고 해서 캐릭터의 몸체가 카메라를 따라 휙휙 즉시 돌아가는(FPS/TPS 타겟팅 방식) 것을 막으려면 액터 최상단 옵션인 `bUseControllerRotationYaw`를 꺼야(`false`) 합니다. 그리고 캐릭터 무브먼트 컴포넌트의 `bOrientRotationToMovement`를 켜야(`true`) 현재 가속받고 있는 방향 쪽으로 모델링 뼈대가 부드럽게 돌아갑니다.
