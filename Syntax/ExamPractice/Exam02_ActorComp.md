# [2장] 액터와 컴포넌트 예상 문제

## 문제 1
캐릭터가 장착할 무기의 '인벤토리 데이터(무게, 공격력, 아이템 코드)'만을 관리하는 컴포넌트를 만들려고 한다. 이 컴포넌트는 화면에 렌더링될 필요도 없고 물리적 충돌 영역이나 좌표 정보(Transform)를 가질 필요도 없다. 
이때 언리얼 엔진의 최적화 관점에서 가장 적합한 C++ 부모 클래스는 무엇인가?

1) `AActor`
2) `UStaticMeshComponent`
3) `USceneComponent`
4) `UActorComponent`

---
### 정답 및 해설
**정답: 4번 (`UActorComponent`)**
**해설:** 물리적인 위치(Transform) 정보가 필요 없는 순수 로직/데이터 전용 컴포넌트는 `UActorComponent`를 상속받아야 연산 낭비 없이 가장 가볍게 동작합니다. `USceneComponent`는 Transform 행렬 연산이 포함되어 있어 데이터 저장용으로는 무겁습니다.
