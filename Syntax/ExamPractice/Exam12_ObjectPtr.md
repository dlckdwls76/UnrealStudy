# [12장] TSubclassOf 와 클래스 스폰 예상 문제

## 문제 1
런타임에 에디터에서 지정한 몬스터를 월드에 소환(Spawn)하려고 한다. 개발자가 블루프린트 디테일 패널에서 **"AMonster 클래스를 상속받은 자식 블루프린트들(예: BP_Orc, BP_Goblin)만"** 선택할 수 있도록 강력하게 필터링해주는 안전한 변수 타입은 무엇인가?

1) `TObjectPtr<AMonster>`
2) `AMonster*`
3) `TArray<AMonster>`
4) `TSubclassOf<AMonster>`

---
### 정답 및 해설
**정답: 4번 (TSubclassOf)**
**해설:** `TObjectPtr`나 `*`(로우 포인터)는 월드에 이미 소환되어 있는 '실체(인스턴스)'를 가리키는 변수입니다. 반면 `TSubclassOf`는 실체가 아니라, 붕어빵을 찍어낼 '틀(클래스 설계도 자체)'을 담는 변수이며 꺾쇠 안의 클래스를 상속받은 것만 담을 수 있도록 에디터 UI를 완벽하게 제약해 줍니다.
