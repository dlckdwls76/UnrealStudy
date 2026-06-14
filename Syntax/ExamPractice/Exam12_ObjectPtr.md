# [12장] TSubclassOf 와 TObjectPtr 심화 예상 문제

## 문제 1. TSubclassOf의 사용 목적
기획자가 에디터의 디테일 패널에서 "무기(Weapon)" 클래스들만 선택할 수 있게 하고, 몬스터나 힐링 포션 같은 엉뚱한 클래스는 아예 넣지 못하게 원천 차단하려고 한다. 
이를 위해 C++에 선언해야 할 가장 좋은 변수 타입은 무엇인가?

1) `AWeapon*`
2) `TArray<AWeapon>`
3) `TSubclassOf<AWeapon>`
4) `TObjectPtr<AWeapon>`

## 문제 2. TObjectPtr의 특징
언리얼 엔진 5에서 기존의 로우 포인터(`AActor*`) 대신 도입된 **`TObjectPtr<AActor>`**에 대한 설명으로 **틀린** 것은?

1) 에디터 환경에서 널 포인터 역참조나 초기화되지 않은 메모리를 보호하는 안정성이 높아진다.
2) 아직 쓰지 않은 거대한 에셋 데이터의 지연 로딩(Lazy Loading)을 도와 메모리를 최적화한다.
3) 실제 유저가 플레이하는 배포용(Shipping) 빌드에선 포인터 오버헤드를 막기 위해 기존의 로우 포인터(`*`)와 100% 동일하게 동작하도록 컴파일된다.
4) 스마트 포인터와 동일하게 가비지 컬렉터 기능을 완전히 내장하고 있어서, 이 변수 위에는 `UPROPERTY()` 매크로를 달아주지 않아도 언리얼이 자동으로 메모리를 수거한다.

## 문제 3. 동적 스폰 (SpawnActor)
게임 도중 C++ 코드로 월드 상의 특정 좌표(`Location`)에 몬스터 클래스 원본(TSubclassOf 변수)을 기반으로 새로운 액터를 하나 소환하려고 한다.
올바른 코드를 완성하기 위한 (A)와 (B)의 조합은?

```cpp
AActor* NewMonster = [   (A)   ]()->SpawnActor<AActor>([   (B)   ], Location, Rotation);
```

1) (A) `GetEngine` / (B) `UClass*`
2) (A) `GetWorld` / (B) `MonsterClass(TSubclassOf 변수)`
3) (A) `GetGameInstance` / (B) `TObjectPtr<AMonster>`
4) (A) `GetWorld` / (B) `TEXT("Monster")`

## 문제 4. 스마트 포인터 매크로 필수성 (코드 예측)
스마트 포인터를 선언했으나 이 코드에는 시한폭탄 버그가 있다. 그 이유는?

```cpp
public:
    // UPROPERTY 매크로를 빼먹음
    TObjectPtr<AWeapon> MyEquippedWeapon;
```

1) 컴파일 불가.
2) `UPROPERTY` 매크로가 없기 때문에 가비지 컬렉터(GC)가 이 변수를 "버려진 메모리"로 오해하고 게임 도중 지워버려, 찌르기 공격 시 Null 크래시가 난다.
3) 블루프린트에서만 안 보일 뿐 작동은 정상이다.
4) 무기 공격력이 강제 0이 된다.

## 문제 5. 런타임 클래스 동적 지정 (빈칸 채우기)
블루프린트 변수 없이 C++ 코드상에서 특정 클래스를 하드코딩해 소환하고 싶다. 빈칸 (A)에 들어갈 함수는?

```cpp
// 몬스터 C++ 원본 클래스 그대로 스폰
GetWorld()->SpawnActor<AMonster>([    (A)    ], Location, Rotation);
```

1) `AMonster::StaticClass()`
2) `AMonster::GetClass()`
3) `AMonster::DefaultObject()`
4) `AMonster::ClassPtr()`


<br><br><br><br><br><br>
---
# 정답 및 해설

### 문제 1 정답: 3번 (`TSubclassOf`)
**해설:** `TSubclassOf<AWeapon>`은 실체화된 인스턴스가 아니라 붕어빵을 찍어낼 **"AWeapon의 자식 설계도(클래스)"**만 쏙 담아주는 강력한 에디터 타입 필터링 도구입니다.

### 문제 2 정답: 4번
**해설:** `TObjectPtr`는 로딩과 안정성 강화를 위한 포인터 래퍼(Wrapper)일 뿐, **언리얼 GC의 보호를 받으려면 무조건 머리 위에 `UPROPERTY()` 매크로를 달아주어야 합니다.**

### 문제 3 정답: 2번 ((A) `GetWorld` / (B) `MonsterClass`)
**해설:** 동적 스폰은 반드시 현재 물리 레벨 덩어리인 `GetWorld()`에 부탁해야 하며, 어떤 설계도로 만들지 매개변수로 클래스 원본(TSubclassOf 변수)을 넘겨줘야 엔진이 찍어낼 수 있습니다.

### 문제 4 정답: 2번 (크래시 유발)
**해설:** 언리얼의 메모리 관리자(GC)는 머리 위에 `UPROPERTY()`가 없는 포인터는 수색망에서 아예 배제하며, 포인터 안에 무기가 들어있든 말든 냅다 메모리를 파괴해 버려 끔찍한 크래시를 유발합니다. `TObjectPtr`도 예외가 아닙니다.

### 문제 5 정답: 1번 (`StaticClass()`)
**해설:** 특정 C++ 객체의 '클래스(UClass*) 타입 원본 메타데이터' 자체를 즉석에서 가져올 때는 `클래스명::StaticClass()` 전역 함수를 사용하는 것이 리플렉션의 최고 기본기입니다. (생성된 놈한테 물어보는 건 `GetClass()`)
