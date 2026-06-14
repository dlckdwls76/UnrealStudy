# [5장] C++ 매크로 시스템 심화 예상 문제

## 문제 1. UFUNCTION 블루프린트 연동
게임 내 '문 열기(OpenDoor)' 기능을 만들었다. C++ 코드에는 단순히 "문이 열렸습니다"라는 로그를 띄우는 기본 로직을 작성해 두었고, 블루프린트에서는 원한다면 이 로직을 지우고 이펙트와 사운드를 재생하는 완전히 새로운 로직으로 **덮어쓰기(Override)** 할 수 있도록 허용하려고 한다.
이러한 구조를 설계하기 위해 C++ 헤더의 UFUNCTION() 매크로 안에 들어가야 할 키워드는 무엇인가?

1) `BlueprintCallable`
2) `BlueprintImplementableEvent`
3) `BlueprintNativeEvent`
4) `BlueprintPure`

## 문제 2. BlueprintPure의 특징
다음 중 `UFUNCTION(BlueprintPure)` 매크로를 선언하여 만든 노드의 특징으로 가장 알맞은 것은?

1) 실행 핀(하얀색 선)이 생겨, 순차적인 흐름 제어가 가능하다.
2) 노드 내에서 액터의 상태나 멤버 변수를 변경(Set)하는 작업에 주로 쓰인다.
3) 실행 핀 없이 데이터(출력 핀)만 반환하며, 단순히 값을 계산하거나 가져올(Get) 때 사용된다.
4) C++ 코드에서 구현할 수 없고 반드시 블루프린트에서만 로직을 짜야 한다.

## 문제 3. UPROPERTY 메타데이터(Meta) 활용
에디터의 디테일 패널에서 기획자가 '무기 공격력' 변수를 입력할 때, 값이 실수로 0 이하로 떨어지는 것을 시스템적으로 막고 한글로 예쁘게 표시하려고 한다. 
다음 빈칸 (A), (B)에 들어갈 올바른 메타 태그는 무엇인가?

```cpp
UPROPERTY(EditAnywhere, meta = ([   (A)   ] = "1", [   (B)   ] = "기본 공격력"))
int32 BaseDamage;
```

1) (A) `ClampMin` / (B) `DisplayName`
2) (A) `LimitMin` / (B) `TitleName`
3) (A) `Min` / (B) `ToolTip`
4) (A) `UIMin` / (B) `ShowName`

## 문제 4. Native 구현 함수명 (빈칸 채우기)
다음은 `BlueprintNativeEvent`로 선언된 함수를 C++ 소스(`.cpp`)에서 실제로 구현하는 코드이다. 올바른 문법을 위해 함수 이름 뒤에 붙여야 하는 (A)는 무엇인가?

```cpp
// 헤더: UFUNCTION(BlueprintNativeEvent) void FireWeapon();

void AWeapon::FireWeapon[    (A)    ]()
{
    UE_LOG(LogTemp, Warning, TEXT("C++ 기본 발사 로직 실행"));
}
```

1) `_Native`
2) `_Base`
3) `_Implementation`
4) `_CppEvent`

## 문제 5. BindWidget 매크로 (코드 예측)
UMG UI 위젯 C++ 클래스에서 아래와 같은 변수를 선언했다. 이 코드가 의도하는 바로 가장 알맞은 것은?

```cpp
UPROPERTY(meta = (BindWidget))
class UProgressBar* HPBar;
```

1) 블루프린트 위젯 창에서 새로운 ProgressBar를 생성하여 C++로 쏴준다.
2) 에디터 블루프린트 위젯 트리에 존재하는 이름이 정확히 "HPBar"인 UI 컴포넌트를 찾아, 이 C++ 포인터 변수와 자동으로 연결(바인딩)시킨다.
3) C++ 클래스의 변수가 바뀔 때마다 위젯 애니메이션이 무조건 재생되도록 묶어둔다.
4) HPBar 포인터를 가비지 컬렉터가 즉각 삭제하도록 명령한다.


<br><br><br><br><br><br>
---
# 정답 및 해설

### 문제 1 정답: 3번 (`BlueprintNativeEvent`)
**해설:** `BlueprintNativeEvent`는 C++에 기본(Native) 동작을 구현(`_Implementation` 함수)해 두고, 블루프린트에서 필요시 덮어쓸 수 있는 유연함을 제공하는 궁극의 매크로입니다. 반면 `BlueprintImplementableEvent`는 C++에 구현부가 아예 없고 100% 블루프린트에서만 로직을 구현해야 합니다.

### 문제 2 정답: 3번
**해설:** `BlueprintPure` 매크로가 붙은 함수는 블루프린트에서 실행 핀(하얀 화살표 선)이 없는 노드로 나타납니다. 즉, 상태를 변화시키지 않고 순수하게 데이터만 읽어오는(Get) 수학 계산이나 변수 반환 전용 노드를 만들 때 사용됩니다.

### 문제 3 정답: 1번 (`ClampMin`, `DisplayName`)
**해설:** `ClampMin`은 에디터 상에서 입력할 수 있는 최솟값을 강제하여 0이나 음수 입력으로 인한 기획 버그를 원천 차단합니다. `DisplayName`은 영어 변수명 대신 디테일 패널에 보여질 예쁜 한글 별명을 지정해 줍니다.

### 문제 4 정답: 3번 (`_Implementation`)
**해설:** `BlueprintNativeEvent` 매크로를 단 함수는 본체 이름을 그대로 C++에서 구현하면 에러가 납니다. 반드시 `함수명_Implementation` 이라는 특수한 이름으로 구현부를 작성해야 언리얼 헤더 툴이 이를 기본 로직으로 인식하고 컴파일을 통과시켜 줍니다.

### 문제 5 정답: 2번
**해설:** UMG C++ 위젯 프로그래밍의 핵심인 `BindWidget` 메타데이터입니다. 블루프린트 위젯(Designer 창)에서 만들어 둔 프로그레스 바의 이름이 C++ 변수명(`HPBar`)과 완전히 똑같다면, 엔진이 게임 시작 시 자동으로 둘을 연결해 주어 코드로 UI를 제어할 수 있게 해줍니다. (이름이 다르면 컴파일 에러를 뿜어냅니다.)
