# [12장] TSubclassOf 와 TObjectPtr 심화 예상 문제

## 문제 1. TSubclassOf의 사용 목적
무기 스폰 시스템을 개발 중이다. 블루프린트 디자이너가 에디터 디테일 패널에서 소환할 무기 종류(검, 창, 활)를 고르게 하려고 한다. 
이때 기획자가 실수로 무기가 아닌 '포션'이나 '캐릭터' 클래스를 넣는 휴먼 에러를 시스템적으로 원천 차단해 주는 가장 안전한 변수 선언은 무엇인가?

1) `UPROPERTY(EditAnywhere) AWeapon* WeaponToSpawn;`
2) `UPROPERTY(EditAnywhere) TArray<AWeapon> WeaponToSpawn;`
3) `UPROPERTY(EditAnywhere) TSubclassOf<AWeapon> WeaponToSpawn;`
4) `UPROPERTY(EditAnywhere) TObjectPtr<AWeapon> WeaponToSpawn;`

## 문제 2. TObjectPtr의 특징 (언리얼 5)
언리얼 엔진 5부터 기존의 C++ 로우 포인터(예: `AActor*`) 대신 도입된 `TObjectPtr<AActor>`가 가지는 장점이나 특징으로 **틀린** 것은?

1) 에디터 빌드에서 변수에 접근할 때 메모리가 유효한지 널 체크를 더 깐깐하게 해준다.
2) 에디터에서 아직 사용되지 않은 무거운 에셋의 지연 로딩(Lazy Loading)을 도와주어 에디터가 켜지는 속도를 빠르게 만든다.
3) 패키징된 배포용(Shipping) 게임 빌드에서는 오버헤드를 줄이기 위해 내부적으로 로우 포인터(`*`)와 똑같이 100% 동일하게 동작하도록 컴파일된다.
4) 가비지 컬렉터(GC) 기능을 완전히 대체하여 `UPROPERTY()` 매크로를 붙이지 않아도 자동으로 메모리를 수거해 준다.

## 문제 3. 동적 스폰 (SpawnActor)
월드상에 존재하지 않는 새로운 액터를 런타임에 소환하려고 한다. 다음 빈칸 (A), (B)에 들어갈 올바른 함수와 파라미터 타입은?

```cpp
// (A)는 월드 객체를 가져오는 함수
// (B)는 에디터에서 할당받은 설계도(클래스) 타입의 변수
if(MonsterClass) {
    AActor* NewMonster = [   (A)   ]()->SpawnActor<AActor>([   (B)   ], Location, Rotation);
}
```

1) (A) `GetEngine` / (B) `UClass*`
2) (A) `GetWorld` / (B) `TSubclassOf<AMonster>`
3) (A) `GetGameInstance` / (B) `TObjectPtr<AMonster>`
4) (A) `GetWorld` / (B) `FString`


<br><br><br><br><br><br>
---
# 정답 및 해설

### 문제 1 정답: 3번 (`TSubclassOf`)
**해설:** `TSubclassOf<AWeapon>`은 "실제로 소환된 무기 객체"를 가리키는 것이 아니라, 붕어빵 틀인 **"무기 설계도(클래스) 자체"**를 담는 타입입니다. 에디터 디테일 패널에서 이 변수를 클릭하면, 오직 `AWeapon`을 상속받은 자식 블루프린트들만 목록에 필터링되어 나오기 때문에 기획자의 실수를 완벽히 방지합니다.

### 문제 2 정답: 4번
**해설:** `TObjectPtr`는 메모리 지연 로딩과 에디터 타입 안정성을 위한 언리얼 5 전용 스마트 포인터일 뿐, **가비지 컬렉션(GC)의 보호를 받으려면 무조건 `UPROPERTY()` 매크로를 위에 달아주어야 합니다.** `UPROPERTY`가 없으면 `TObjectPtr`든 로우 포인터든 가차 없이 메모리가 삭제되어 크래시가 납니다. (1,2,3번은 모두 맞는 말입니다.)

### 문제 3 정답: 2번 ((A) `GetWorld` / (B) `TSubclassOf`)
**해설:** 액터를 소환하려면 반드시 레벨 공간이 필요하므로 `GetWorld()` 함수를 호출하여 월드 객체를 얻어와야 합니다. 그리고 `SpawnActor` 함수의 첫 번째 인자로는 어떤 설계도로 액터를 찍어낼지 묻기 때문에, 클래스 타입 변수인 `TSubclassOf`가 전달되어야 합니다.
