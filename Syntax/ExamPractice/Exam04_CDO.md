# [4장] CDO (Class Default Object) 심화 예상 문제

## 문제 1. ConstructorHelpers의 규칙
다음 중 `ConstructorHelpers::FObjectFinder`를 사용할 때 발생하는 특징으로 **틀린** 것은?

1) 오직 클래스의 생성자(Constructor) 내부에서만 정상 작동한다.
2) 에셋의 하드 코딩된 파일 경로(예: `"/Game/Mesh/Sword.Sword"`)를 통해 에셋을 로드한다.
3) 이 함수로 불러온 에셋은 해당 클래스의 CDO(Class Default Object)에 저장되어 이후 복사본(인스턴스)들이 재사용한다.
4) 게임 플레이 도중(런타임)에 다른 무기로 바꾸기 위해 무기 이름을 조합하여 이 함수를 다시 부르면 동적으로 무기가 교체된다.

## 문제 2. CDO 원본 조작
코드 상에서 클래스의 CDO(거푸집 원본) 객체를 직접 가져오기 위해 사용하는 함수는 다음 중 무엇인가?

1) `GetClass()->GetDefaultObject()`
2) `GetOwner()->GetDefault()`
3) `this->GetCDO()`
4) `UObject::FindCDO()`

## 문제 3. CDO의 존재 의의
언리얼 엔진이 시작될 때 단 한 번 만들어지는 CDO(Class Default Object)의 주된 목적과 거리가 **먼** 것은?

1) 똑같은 몬스터 1,000마리를 소환할 때, 변수 기본값을 매번 새로 계산하지 않고 CDO의 메모리 블록을 통째로 복사(메모리 카피)하여 소환 속도를 극대화한다.
2) 블루프린트 에디터 창을 열었을 때, 뷰포트에 보여지는 기본 캐릭터의 모습과 컴포넌트 세팅들을 제공하는 기준점이 된다.
3) 게임 플레이 도중 플레이어의 현재 체력(HP)과 획득한 경험치를 실시간으로 저장하고 추적한다.
4) `ConstructorHelpers`를 통해 로드된 무거운 리소스(메시, 머티리얼)의 포인터를 단 하나만 유지하여 메모리를 아낀다.

## 문제 4. FClassFinder 클래스 템플릿 로드 (빈칸 채우기)
액터 생성자에서 에셋(Mesh)이 아닌, 블루프린트 "클래스(BP_Monster)" 자체를 로드하여 변수에 담아두려고 한다. 다음 코드의 빈칸 (A)에 들어갈 올바른 함수는?

```cpp
AMyGameMode::AMyGameMode()
{
    // 클래스(설계도)를 찾기 위한 도우미
    static ConstructorHelpers::[   (A)   ]<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player.BP_Player_C"));
    if (PlayerPawnClassFinder.Succeeded())
    {
        DefaultPawnClass = PlayerPawnClassFinder.Class;
    }
}
```

1) `FObjectFinder`
2) `FClassFinder`
3) `FBlueprintFinder`
4) `FAssetFinder`

## 문제 5. CDO 시점의 크래시 요인 (코드 예측)
다음 코드를 작성하고 컴파일한 후, 언리얼 에디터를 켜거나 해당 액터를 배치하려고 할 때 발생하는 일은?

```cpp
AWeapon::AWeapon()
{
    // 생성자에서 몬스터 스폰 시도
    GetWorld()->SpawnActor<AMonster>(AMonster::StaticClass());
}
```

1) 무기가 생성될 때마다 몬스터가 한 마리씩 안전하게 스폰된다.
2) 생성자(CDO 생성 시점)에는 아직 `GetWorld()`(물리적 레벨 공간)가 완전히 존재하지 않거나 불안정하므로 엔진 크래시가 발생한다.
3) 몬스터가 에디터 공간의 0,0,0 좌표에 영구적으로 배치된다.
4) 컴파일 단계에서 문법 오류로 막힌다.


<br><br><br><br><br><br>
---
# 정답 및 해설

### 문제 1 정답: 4번
**해설:** `ConstructorHelpers`는 엔진 초기화 단계에서 CDO를 굽어낼 때 단 한 번만 실행되는 함수입니다. 런타임에 이 함수를 호출하면 엔진이 즉시 크래시를 내며 뻗어버립니다. 런타임에 동적으로 경로를 바꿔 무기를 로드하려면 `LoadObject<T>`나 `FStreamableManager`를 이용한 비동기 로드를 사용해야 합니다.

### 문제 2 정답: 1번
**해설:** 현재 인스턴스에서 자신의 원본 설계도 템플릿(CDO)을 가져오려면 `GetClass()->GetDefaultObject<T>()`를 사용해야 합니다. 여기서 변수값을 바꾸면 이후 스폰되는 모든 새로운 객체들의 초기값이 바뀌는 엄청난 나비효과를 가져옵니다.

### 문제 3 정답: 3번
**해설:** CDO는 말 그대로 **'기본값(Default)을 가진 불변의 템플릿'**입니다. 한 번 100이라는 체력 기본값이 세팅되면 끝입니다. 게임 도중 플레이어가 몬스터에게 맞아서 체력이 닳는 행위는 런타임에 복사되어 태어난 '인스턴스(Instance)'의 체력 변수가 바뀌는 것이지, 거푸집(CDO) 원본의 체력이 바뀌는 것이 아닙니다.

### 문제 4 정답: 2번 (`FClassFinder`)
**해설:** 눈에 보이는 모델링이나 사운드 같은 "에셋 데이터"를 찾을 때는 `FObjectFinder`를 쓰지만, 블루프린트 "클래스(타입)" 그 자체를 찾아서 `TSubclassOf` 변수에 넣으려고 할 때는 반드시 `FClassFinder`를 사용해야 합니다. 경로 끝에 `_C`가 붙는 것도 특징입니다.

### 문제 5 정답: 2번 (엔진 크래시)
**해설:** 생성자는 엔진이 켜지는 과정이나 에디터에서 에셋을 브라우징할 때 CDO를 만들기 위해 호출됩니다. 이때는 게임을 플레이하는 런타임 공간인 `GetWorld()`가 없거나 완전히 셋팅되지 않은 상태일 확률이 높습니다. 따라서 생성자에서 `GetWorld()`를 호출해 무언가를 소환(`SpawnActor`)하거나 파괴하려고 시도하면 거의 무조건 크래시가 터지며 에디터가 꺼집니다. 소환이나 로직은 `BeginPlay`로 넘겨야 합니다.
