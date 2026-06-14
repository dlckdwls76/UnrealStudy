# [9장] 게임 인스턴스 (Game Instance) 심화 예상 문제

## 문제 1. UGameInstance의 수명(Lifecycle)
플레이어의 총 점수(Score)나 획득한 골드 데이터를 **맵(Level)을 전환한 후에도 파괴되지 않게 유지**하려고 할 때, 이 데이터를 보관하기 가장 적합한 C++ 클래스는 무엇인가?

1) `AGameModeBase`
2) `UGameInstance`
3) `APlayerController`
4) `AActor`

## 문제 2. 형변환과 인스턴스 획득
현재 켜져 있는 게임 인스턴스 객체를 가져와 내가 만든 커스텀 게임 인스턴스(`UMyGameInstance`)로 안전하게 캐스팅(형변환)하는 올바른 문법은 무엇인가?

1) `Cast<AGameMode>(GetGameMode());`
2) `Cast<UMyGameInstance>(GetGameInstance());`
3) `Cast<AActor>(GetOwner());`
4) `Cast<UMyGameInstance>(GetWorldInstance());`

## 문제 3. 초기화 함수 비교
게임 프로세스가 처음 켜질 때 `UGameInstance`가 딱 한 번 호출받아 전역 데이터나 테이블을 로드하기에 가장 좋은 초기화 전용 가상 함수는 무엇인가?

1) `StartPlay()`
2) `OnConstruction()`
3) `Init()`
4) `Awake()`

## 문제 4. 게임 인스턴스 캐스팅 실패 (코드 예측)
프로그래머가 아래 코드를 짰는데, 자꾸 `MyGI`가 널 포인터(`nullptr`)를 반환하여 내부 코드가 실행되지 않는다. 가장 그럴듯한 원인은 무엇인가?

```cpp
UMyGameInstance* MyGI = Cast<UMyGameInstance>(GetGameInstance());
if (MyGI)
{
    UE_LOG(LogTemp, Warning, TEXT("성공적으로 가져옴"));
}
```

1) 게임을 아직 플레이(Play) 버튼을 누르지 않아서 그렇다.
2) `UMyGameInstance` 클래스를 C++로 만들어 두기만 하고, **언리얼 에디터의 프로젝트 세팅(Project Settings) -> 맵 & 모드 -> GameInstance Class 항목**을 이 커스텀 클래스로 바꿔 끼워주지 않아 엔진이 여전히 기본 게임 인스턴스를 생성했기 때문이다.
3) `Cast`가 아니라 `DynamicCast`를 써야 한다.
4) 가비지 컬렉터가 인스턴스를 즉각 수거해 갔기 때문이다.

## 문제 5. Init의 부모 함수 호출 (빈칸 채우기)
게임 인스턴스 초기화 함수인 `Init()`을 오버라이드할 때, C++와 언리얼 규칙에 따라 **가장 첫 줄**에 반드시 넣어야 하는 코드는 무엇인가?

```cpp
void UMyGameInstance::Init()
{
    [       빈 칸       ]
    
    // 나의 초기화 로직...
    TotalScore = 0;
}
```

1) `GetWorld()->Init();`
2) `UGameInstance::BeginPlay();`
3) `Super::Init();`
4) `Init();`


<br><br><br><br><br><br>
---
# 정답 및 해설

### 문제 1 정답: 2번 (`UGameInstance`)
**해설:** 일반 액터나 게임 모드는 맵을 바꾸면 메모리에서 모두 파괴되고 재시작되지만, 게임 프로세스의 최상단 뼈대를 이루는 싱글톤 객체인 `UGameInstance`는 게임을 끄기 전까지 유일하게 데이터가 파괴되지 않고 유지됩니다.

### 문제 2 정답: 2번
**해설:** 전역 헬퍼 함수인 `GetGameInstance()`를 통해 가장 최상위 부모 타입(`UGameInstance*`)의 포인터를 가져온 뒤, `Cast<내클래스명>`을 통해 자식 타입으로 안전하게 다운 캐스팅해야 자식의 고유 변수(총 골드량 등)를 조작할 수 있습니다.

### 문제 3 정답: 3번 (`Init`)
**해설:** `UGameInstance`는 3D 월드 상에 배치되는 `AActor` 계열이 아니므로 레벨 시작을 알리는 `BeginPlay()`가 아예 존재하지 않습니다. 대신 엔진 프로세스가 메모리에 완전히 올라가 게임이 시작될 때 `Init()` 하나만 불리며, 여기서 네트워크나 DB 세팅 등을 초기화합니다.

### 문제 4 정답: 2번 (프로젝트 세팅 미설정)
**해설:** C++에서 아무리 훌륭한 게임 인스턴스를 만들었더라도, 프로젝트 세팅에서 "이제부터 이 인스턴스를 써라"라고 등록해주지 않으면 엔진은 기본 깡통 인스턴스를 생성합니다. 따라서 캐스팅(`Cast`)을 시도하면 타입이 맞지 않아 무조건 `nullptr`을 뱉으며 캐스팅에 실패하게 됩니다. (실무 뉴비들이 가장 많이 하는 실수입니다.)

### 문제 5 정답: 3번 (`Super::Init();`)
**해설:** 언리얼 엔진 프레임워크의 핵심 가상 함수들(`BeginPlay`, `Tick`, `Init` 등)을 오버라이드할 때는, 부모 클래스가 에픽게임즈에서 미리 구워놓은 코어 로직이 날아가는 것을 막기 위해 반드시 `Super::함수명()`을 최우선적으로 호출하는 것이 절대적인 안전 수칙입니다.
