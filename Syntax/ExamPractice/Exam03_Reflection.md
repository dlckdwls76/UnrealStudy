# [3장] 리플렉션 시스템 예상 문제

## 문제 1
다음은 아이템 데이터를 정의하는 C++ 구조체 코드이다. 빈칸 (A)에 들어가야 할 올바른 매크로와, (B)에 들어갈 언리얼 문자열 타입으로 가장 알맞게 짝지어진 것은?

```cpp
// (A) 구조체 리플렉션 매크로
struct FItemData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    // (B) 딕셔너리(TMap)의 Key 값으로 쓰기 위해 속도가 가장 빠르고 해시(Hash) 변환되는 문자열 타입
    [   (B)   ] ItemID; 

    UPROPERTY(EditAnywhere)
    FString ItemDescription;
};
```

1) (A): `UCLASS(BlueprintType)` / (B): `FText`
2) (A): `USTRUCT(BlueprintType)` / (B): `FName`
3) (A): `UENUM(BlueprintType)` / (B): `FString`
4) (A): `USTRUCT(BlueprintType)` / (B): `FText`

---
### 정답 및 해설
**정답: 2번 ((A): USTRUCT, (B): FName)**
**해설:** 구조체를 리플렉션 시스템에 등록하려면 `USTRUCT`를 사용해야 합니다. 또한 내부적으로 문자열을 해시(정수)로 보관하여 비교/검색 속도가 압도적으로 빠른 타입은 `FName`이므로, ID나 식별자(Key) 용도로 가장 적합합니다.
