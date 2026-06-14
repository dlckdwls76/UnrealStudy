# [1장] 자료구조 (TArray, TSet, TMap) 심화 예상 문제

## 문제 1. TArray의 원소 삭제와 메모리 이동
다음 C++ 코드를 실행한 후, `MyArray`의 0번 인덱스에 들어있을 값은 무엇인가?

```cpp
TArray<int32> MyArray;
MyArray.Add(10);
MyArray.Add(20);
MyArray.Add(30);
MyArray.Add(40);

// RemoveAtSwap은 삭제 후 빈자리를 채우는 방식이 일반 RemoveAt과 다릅니다.
MyArray.RemoveAtSwap(0);
```

1) 10
2) 20
3) 30
4) 40

## 문제 2. TSet의 중복 처리와 해시
다음 코드를 실행한 후 `MySet.Num()`이 반환하는 원소의 총 개수는 몇 개인가?

```cpp
TSet<FString> MySet;
MySet.Add(TEXT("Apple"));
MySet.Add(TEXT("Banana"));
MySet.Add(TEXT("Apple"));
MySet.Add(TEXT("Cherry"));
MySet.Remove(TEXT("Banana"));
```

1) 1개
2) 2개
3) 3개
4) 4개

## 문제 3. TMap의 검색(Find) 반환형과 널 체크
`TMap<int32, FString> Inventory;` 가 선언되어 있을 때, Key값 100번에 해당하는 아이템 이름을 안전하게 찾아 콘솔에 출력하려고 한다. 
다음 중 언리얼 C++의 표준 문법으로 가장 올바르게 작성된 코드는 무엇인가?

1) 
```cpp
FString Item = Inventory.Find(100);
if(Item != nullptr) { UE_LOG(LogTemp, Warning, TEXT("%s"), *Item); }
```

2) 
```cpp
FString* ItemPtr = Inventory.Find(100);
if(ItemPtr) { UE_LOG(LogTemp, Warning, TEXT("%s"), **ItemPtr); }
```

3) 
```cpp
if(Inventory.Contains(100)) { 
    UE_LOG(LogTemp, Warning, TEXT("%s"), Inventory[100]); 
}
```

4) 
```cpp
FString Item = Inventory.Get(100);
UE_LOG(LogTemp, Warning, TEXT("%s"), *Item);
```


<br><br><br><br><br><br>
---
# 정답 및 해설

### 문제 1 정답: 4번 (40)
**해설:** `RemoveAt(0)`을 사용하면 10이 지워진 후 20, 30, 40이 모두 한 칸씩 앞으로 당겨져서 0번 인덱스가 20이 됩니다. 하지만 성능 최적화를 위해 사용하는 **`RemoveAtSwap`**은 빈자리를 메꾸기 위해 전체를 당기지 않고, **맨 마지막에 있는 원소(40)를 뽑아서 지워진 0번 자리에 꽂아 넣습니다.** 따라서 0번 인덱스의 값은 40이 됩니다. 배열의 순서가 망가져도 상관없을 때 최고의 성능을 내는 함수입니다.

### 문제 2 정답: 2번 (2개)
**해설:** `TSet`은 집합이므로 중복된 값을 허용하지 않습니다. "Apple"을 두 번 Add 했지만 한 번만 들어가고, "Banana", "Cherry"가 추가되어 총 3개였다가, "Banana"를 Remove 했으므로 최종적으로 남은 것은 "Apple"과 "Cherry" **2개**입니다.

### 문제 3 정답: 2번
**해설:** `TMap`의 `Find()` 함수는 값을 복사해 주지 않고 해당 값의 **포인터(`*`)**를 반환합니다. 만약 키가 없으면 `nullptr`을 반환하므로, 2번처럼 포인터로 받고 널 체크(`if(ItemPtr)`)를 거친 뒤, `**ItemPtr`로 이중 역참조하여 출력하는 것이 크래시를 방지하는 가장 완벽한 언리얼 C++ 정석 코드입니다. (3번도 동작은 하나 두 번 검색하므로 비효율적입니다.)
