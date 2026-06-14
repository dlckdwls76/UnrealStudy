# [3장] 리플렉션 시스템 심화 예상 문제

## 문제 1. 언리얼 문자열 타입 선택
게임 내 방대한 양의 '아이템 데이터 테이블(CSV/JSON)'을 로드하여 딕셔너리(`TMap`)에 저장하려고 한다. 
아이템의 고유 식별 코드(예: "SWORD_001", "POTION_002")를 Key 값으로 사용하여 매 프레임 빠르게 검색해야 할 때, 문자열 비교 연산이 가장 빠른 타입은 무엇인가?

1) `FString`
2) `FName`
3) `FText`
4) `std::string`

## 문제 2. UPROPERTY 매크로
디자이너가 언리얼 에디터의 **디테일 패널에서는 값을 마음대로 수정**할 수 있게 하고 싶지만, **블루프린트 노드(이벤트 그래프)에서는 이 변수를 절대 꺼내 쓰거나 변경하지 못하게** 막고 싶다. 
다음 중 가장 알맞은 UPROPERTY 매크로 구성은?

1) `UPROPERTY(EditAnywhere, BlueprintReadWrite)`
2) `UPROPERTY(VisibleAnywhere, BlueprintReadOnly)`
3) `UPROPERTY(EditAnywhere)`
4) `UPROPERTY(BlueprintCallable)`

## 문제 3. 가비지 컬렉션(GC) 추적
언리얼 엔진의 가비지 컬렉터(GC)에 의해 자동으로 메모리 해제 관리를 **받지 않는** 타입은 다음 중 무엇인가?

1) `UCLASS()` 매크로가 붙고 `UObject`를 상속받은 객체
2) `USTRUCT(BlueprintType)` 매크로가 붙은 구조체
3) `UPROPERTY()` 매크로가 붙은 `AActor*` 포인터
4) `NewObject`로 생성된 컴포넌트

## 문제 4. 리플렉션 오류 (코드 예측)
다음 코드를 컴파일했을 때 발생하는 현상과 원인으로 올바른 것은?

```cpp
UCLASS()
class AMyHero : public ACharacter
{
    // [!] GENERATED_BODY() 누락

public:
    UPROPERTY(EditAnywhere)
    int32 HeroLevel;
};
```

1) 경고(Warning)만 뜨고 정상적으로 컴파일되며 게임 실행에 문제가 없다.
2) `GENERATED_BODY()` 매크로가 빠졌기 때문에 언리얼 헤더 툴(UHT)이 리플렉션 코드를 삽입하지 못해 컴파일 에러(C++ 오류)가 발생한다.
3) 언리얼 엔진이 자동으로 `GENERATED_BODY()`를 추론해서 채워 넣고 컴파일한다.
4) 컴파일은 되지만 게임 시작 시 크래시가 발생한다.

## 문제 5. 열거형(Enum) 리플렉션 매크로 (빈칸 채우기)
C++에서 만든 열거형(Enum)을 블루프린트에서 변수 타입으로 사용하거나 스위치(Switch) 노드로 꺼내 쓰기 위해 다음 코드를 작성했다. 빈칸 (A)에 들어갈 매크로 코드는 무엇인가?

```cpp
[     (A)     ]
enum class EWeaponType : uint8
{
    Sword,
    Bow,
    Staff
};
```

1) `UCLASS()`
2) `USTRUCT(BlueprintType)`
3) `UENUM(BlueprintType)`
4) `UPROPERTY(BlueprintReadWrite)`


<br><br><br><br><br><br>
---
# 정답 및 해설

### 문제 1 정답: 2번 (`FName`)
**해설:** `FName`은 내부에 문자열 자체를 들고 있지 않고 문자열을 해시(정수 숫자) 테이블에 등록한 뒤 숫자끼리만 비교합니다. 따라서 검색 속도가 비교를 불허할 정도로 가장 빠릅니다. 반면 화면에 다국어로 띄워야 할 글자는 `FText`, 동적으로 글자를 자르고 붙여야 할 때는 `FString`을 씁니다.

### 문제 2 정답: 3번 (`UPROPERTY(EditAnywhere)`)
**해설:** `EditAnywhere`는 에디터 디테일 패널에서 숫자를 수정할 수 있게 해줍니다. 하지만 `BlueprintReadWrite`나 `BlueprintReadOnly` 같은 블루프린트 노드 권한을 적어주지 않으면, 블루프린트 그래프 창에서는 해당 변수의 겟/셋 노드를 검색조차 할 수 없게 완벽히 차단됩니다. 

### 문제 3 정답: 2번 (`USTRUCT`)
**해설:** 언리얼의 가비지 컬렉터는 오직 `UObject`를 상속받은 '클래스(UCLASS) 인스턴스'만을 감시하고 관리합니다. 구조체(`USTRUCT`)는 매크로가 붙어있어도 여전히 값(Value) 타입이므로 일반 C++의 스택/힙 규칙을 따르며 블록을 벗어나면 즉시 파기됩니다. GC의 감시망에서 자유롭기 때문에 매우 가볍습니다.

### 문제 4 정답: 2번
**해설:** `UCLASS()`, `USTRUCT()` 등을 선언한 중괄호 내부 최상단에는 반드시 `GENERATED_BODY()`가 들어가야 합니다. 이 매크로가 있어야 언리얼 빌드 시스템(UHT)이 리플렉션 메타데이터를 해당 클래스에 주입할 수 있습니다. 누락되면 즉시 빌드 실패(컴파일 에러)를 뿜어냅니다.

### 문제 5 정답: 3번 (`UENUM(BlueprintType)`)
**해설:** 열거형(enum)을 엔진과 블루프린트 리플렉션 시스템에 등록하려면 `UENUM` 매크로를 사용해야 합니다. 괄호 안에 `BlueprintType` 지정자를 넣어주어야 블루프린트 변수창에서 이 열거형을 타입으로 골라 쓸 수 있습니다.
