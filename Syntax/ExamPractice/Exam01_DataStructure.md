# [1장] 자료구조 (TArray, TSet, TMap) 예상 문제

## 문제 1
다음 C++ 코드를 보고 실행 결과를 예측하시오.

```cpp
TArray<int32> Scores;
Scores.Add(10);
Scores.Add(20);
Scores.Add(30);

Scores.RemoveAt(1);
int32 Result = Scores[1];
```

**Result 변수에 들어갈 값으로 알맞은 것은?**

1) 10
2) 20
3) 30
4) 배열 인덱스 초과로 인한 크래시(에러) 발생

---
### 정답 및 해설
**정답: 3번 (30)**
**해설:** `RemoveAt(1)`을 호출하면 1번 인덱스에 있던 `20`이 삭제됩니다. TArray의 특성상 빈 공간을 채우기 위해 뒤에 있던 `30`이 앞으로 당겨지며(Shift) 1번 인덱스로 이동합니다. 따라서 `Scores[1]`은 30이 됩니다.
