# [2장] 액터와 컴포넌트 심화 예상 문제

## 문제 1. 컴포넌트 생성 시점
게임이 시작되고(`BeginPlay` 호출 이후), 플레이어가 특정 버튼을 눌렀을 때 런타임 중에 동적으로 파티클 이펙트 컴포넌트를 생성하여 캐릭터에 부착하려고 한다.
이때 사용해야 하는 올바른 언리얼 C++ 함수는 무엇인가?

1) `CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));`
2) `NewObject<UParticleSystemComponent>(this);` 호출 후 `RegisterComponent();`
3) `SpawnActor<UParticleSystemComponent>();`
4) `ConstructObject<UParticleSystemComponent>();`

## 문제 2. 컴포넌트 클래스 설계
MMORPG에서 플레이어의 '버프 지속 시간'과 '상태 이상(독, 기절)' 데이터만을 실시간으로 계산하는 `UStatusComponent`를 C++로 만들려고 한다. 
이 컴포넌트는 화면에 보이지 않고 좌표도 필요 없다. 성능을 최대한 깎아먹지 않기 위해 상속받아야 할 가장 적합한 부모 클래스는?

1) `USceneComponent`
2) `UStaticMeshComponent`
3) `UActorComponent`
4) `UPrimitiveComponent`

## 문제 3. 계층 구조(Hierarchy) 조립
액터의 생성자(`AWeapon::AWeapon()`)에서 루트 컴포넌트로 사용할 `BoxComponent`를 만들고, 그 자식으로 `StaticMeshComponent`를 부착하려고 한다. 빈칸 (A)와 (B)에 들어갈 올바른 함수는?

```cpp
BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
[   (A)   ] = BoxComp;

MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
MeshComp->[   (B)   ](BoxComp);
```

1) (A) `SetRootComponent` / (B) `AttachTo`
2) (A) `RootComponent` / (B) `SetupAttachment`
3) (A) `GetRootComponent` / (B) `AttachToComponent`
4) (A) `RootComponent` / (B) `BindTo`


<br><br><br><br><br><br>
---
# 정답 및 해설

### 문제 1 정답: 2번
**해설:** `CreateDefaultSubobject`는 오직 액터의 **생성자(Constructor)** 내부에서만 사용할 수 있는 엔진 초기화 전용 함수입니다. 런타임(게임 도중)에 컴포넌트를 동적으로 생성하려면 **`NewObject<T>`**를 사용해 메모리를 할당한 뒤, 엔진 시스템에 적용되도록 반드시 **`RegisterComponent()`**를 호출해 주어야 합니다. (`SpawnActor`는 컴포넌트가 아니라 액터를 소환할 때 씁니다.)

### 문제 2 정답: 3번 (`UActorComponent`)
**해설:** 위치, 회전, 크기(Transform)를 나타내는 행렬 연산이 단 하나도 필요 없는 순수 로직/데이터 처리용 컴포넌트는 `UActorComponent`를 상속받는 것이 국룰입니다. Transform 데이터가 덕지덕지 붙어 있는 `USceneComponent`를 상속받으면 메모리와 연산에 큰 손해를 봅니다.

### 문제 3 정답: 2번
**해설:** 액터의 최상단 뿌리(Root)를 지정할 때는 액터가 이미 갖고 있는 `RootComponent` 포인터 변수에 직접 대입(`RootComponent = BoxComp;`)합니다. 그리고 생성자 안에서 특정 씬 컴포넌트를 다른 씬 컴포넌트의 자식으로 부착할 때는 **`SetupAttachment`** 함수를 사용해야 트랜스폼 계층 구조가 안전하게 묶입니다. (`AttachToComponent`는 생성자가 아닌 런타임(BeginPlay 이후)에 동적 부착할 때 씁니다.)
