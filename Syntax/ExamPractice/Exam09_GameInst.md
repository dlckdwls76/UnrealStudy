# [9장] 게임 인스턴스 (Game Instance) 심화 예상 문제

## 문제 1. UGameInstance의 수명(Lifecycle)
플레이어의 레벨 데이터나 총 점수(Score)를 저장하려고 한다. 만약 이 데이터를 `AGameModeBase`나 `APlayerController`에 저장했을 때 발생하는 치명적인 문제점은 무엇인가?

1) 다른 액터에서 절대 접근할 수 없는 private 메모리로 잠긴다.
2) 레벨(맵)이 전환되거나 게임을 재시작하면 해당 객체들이 파괴(Destroy)되어 데이터가 전부 초기화된다.
3) 가비지 컬렉션(GC)에 의해 1분마다 강제로 지워진다.
4) 멀티플레이에서 다른 유저의 화면에 강제로 공유되어 버린다.

## 문제 2. 형변환과 인스턴스 획득
플레이어 액터의 `BeginPlay()` 내부에서, 개발자가 만든 `UMyGameInstance` 클래스의 변수에 접근하려고 한다. 
다음 빈칸 (A), (B)에 들어갈 올바른 C++ 코드는 무엇인가?

```cpp
// 시스템에 등록된 게임 인스턴스를 가져와서 내 커스텀 클래스로 형변환
[   (A)   ]* MyGI = Cast<[   (A)   ]>([   (B)   ]());
if (MyGI)
{
    MyGI->TotalScore += 10;
}
```

1) (A) `AGameMode` / (B) `GetGameMode`
2) (A) `UMyGameInstance` / (B) `GetGameInstance`
3) (A) `AActor` / (B) `GetOwner`
4) (A) `UMyGameInstance` / (B) `GetWorldInstance`

## 문제 3. 초기화 함수 비교
일반 액터(AActor)는 생성자 실행 후 게임에 배치될 때 `BeginPlay()`가 호출된다. 그렇다면 게임 인스턴스(`UGameInstance`)가 맨 처음 생성될 때, 초기화 코드를 넣기 위해 오버라이드해야 하는 가상 함수는 무엇인가?

1) `StartPlay()`
2) `OnConstruction()`
3) `Init()`
4) `Awake()`


<br><br><br><br><br><br>
---
# 정답 및 해설

### 문제 1 정답: 2번
**해설:** 게임 모드나 플레이어 컨트롤러를 포함한 월드 안의 모든 `AActor` 파생 클래스들은 맵(Level)이 바뀌면 모두 메모리에서 파괴(Destroy)되고 새 맵에서 다시 태어납니다. 따라서 맵 전환에도 보존되어야 하는 전역 데이터는 게임 프로세스 전체를 관장하는 싱글톤 객체인 `UGameInstance`에 넣어야만 안전합니다.

### 문제 2 정답: 2번 ((A) `UMyGameInstance` / (B) `GetGameInstance`)
**해설:** 언리얼 엔진에서 현재 켜져 있는 게임 인스턴 객체를 가져오는 전역 함수는 `GetGameInstance()` (또는 `GetWorld()->GetGameInstance()`) 입니다. 이 함수는 부모 타입인 `UGameInstance*`를 반환하므로, 우리가 만든 자식 클래스의 변수에 접근하려면 반드시 `Cast<UMyGameInstance>`로 다운 캐스팅(형변환)을 해 주어야 합니다.

### 문제 3 정답: 3번 (`Init`)
**해설:** `UGameInstance`는 액터가 아니라 `UObject`의 자식이므로 `BeginPlay()`라는 개념이 없습니다. 대신 엔진 프로세스가 켜지며 인스턴스가 할당될 때 딱 한 번 호출되는 전용 초기화 함수인 `Init()`을 가집니다.
