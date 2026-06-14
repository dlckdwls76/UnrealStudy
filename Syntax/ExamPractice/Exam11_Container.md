# [11장] 컨테이너 자료구조 (TArray, TSet, TMap) 심화 예상 문제

## 문제 1. TMap의 Find 함수와 방어적 프로그래밍
`TMap<int32, FString> Inventory;` 가 선언되어 있을 때, C++의 정석이자 크래시를 방지하는 가장 안전한 Find 문법은 무엇인가?

1) 
```cpp
FString Item = Inventory.Find(1);
UE_LOG(LogTemp, Warning, TEXT("%s"), *Item);
```
2) 
```cpp
if (FString* FoundItem = Inventory.Find(1)) {
    UE_LOG(LogTemp, Warning, TEXT("%s"), **FoundItem);
}
```
3) 
```cpp
FString* FoundItem = &Inventory[1];
UE_LOG(LogTemp, Warning, TEXT("%s"), *FoundItem);
```
4) 
```cpp
FString FoundItem = Inventory.Get(1);
UE_LOG(LogTemp, Warning, TEXT("%s"), FoundItem);
```

## 문제 2. Emplace와 Add의 성능 차이
`TArray`나 `TMap`에 구조체나 객체 데이터를 새로 집어넣을 때, 언리얼 에픽게임즈 공식 문서에서 `Add`보다 **`Emplace`**의 사용을 적극 권장하는 이유는 무엇인가?

1) `Emplace`는 가비지 컬렉션(GC)을 무시하고 강제로 메모리를 할당해 주기 때문이다.
2) `Add`는 무조건 배열의 맨 앞에 데이터를 넣기 때문에 속도가 느리다.
3) `Emplace`는 임시 객체를 생성하여 복사(Copy)하는 과정을 거치지 않고, 배열의 해당 메모리 주소에서 데이터를 직접 생성(Construct)하여 오버헤드와 성능 낭비를 크게 줄여주기 때문이다.
4) `Emplace`는 중복된 값이 들어오는 것을 자동으로 막아주는 해시 기능이 포함되어 있기 때문이다.

## 문제 3. TSet의 특징
다음 중 `TArray` 대신 `TSet` 자료구조를 사용했을 때 얻을 수 있는 가장 큰 알고리즘적 이점은 무엇인가?

1) 들어간 순서(인덱스)가 완벽하게 보장되어 정렬이 쉽다.
2) Key와 Value가 한 쌍으로 묶여 딕셔너리 구조를 가진다.
3) 내부적으로 해시(Hash) 알고리즘을 사용하므로, 데이터가 수만 개가 쌓여도 `Contains`나 `Remove` 함수를 사용할 때의 검색 속도가 `O(1)`에 가깝게 압도적으로 빠르다.
4) 3D 벡터나 트랜스폼 데이터를 수학적으로 내적 연산해 주는 기능이 있다.


<br><br><br><br><br><br>
---
# 정답 및 해설

### 문제 1 정답: 2번
**해설:** `TMap`의 `Find()` 함수는 찾는 키값이 없을 경우 프로그램이 터지는 것을 막기 위해 '값'이 아니라 '메모리 주소(포인터 `*`)'를 반환하도록 설계되었습니다. 따라서 `if`문 안에서 포인터 변수를 선언함과 동시에 `nullptr` 체크를 수행하고, 사용할 때는 `**`로 이중 역참조를 해주는 것이 가장 안전하고 완벽한 코드입니다.

### 문제 2 정답: 3번
**해설:** `Add`는 `MyStruct(1, 2)`처럼 임시 객체를 만들어 배열로 '복사'해서 넣습니다. 반면 `Emplace(1, 2)`는 배열 내부의 빈 공간을 먼저 확보한 후, 그 메모리 번지에서 직접 객체의 생성자를 호출합니다. 쓸데없는 메모리 복사가 생략되므로 실무에서는 성능을 위해 무조건 `Emplace`를 애용합니다.

### 문제 3 정답: 3번
**해설:** `TSet`은 순서(인덱스)가 없는 대신, 데이터를 해시 숫자로 변환해 저장하는 집합 자료구조입니다. 배열(`TArray`)은 특정 값을 찾기 위해 0번부터 끝까지 싹 다 뒤져야 하지만(O(N)), `TSet`은 해시 함수를 통해 데이터가 있는 방 번호를 한 번에 찾아내므로 검색 속도가 압도적으로 빠릅니다(O(1)).
