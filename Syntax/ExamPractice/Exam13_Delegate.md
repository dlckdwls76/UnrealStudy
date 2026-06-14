# [13장] 이벤트(Event)와 델리게이트(Delegate) 예상 문제

## 문제 1
보스 몬스터가 죽을 때 발동하는 `FOnBossDied`라는 델리게이트를 만들었다. 외부의 다른 클래스(UI 팝업창, 업적 시스템 등)들이 이 델리게이트에 자신의 함수를 자유롭게 추가(Bind)하게 하되, 
**오직 보스 몬스터 클래스(자신) 내부에서만 `Broadcast()`를 호출하여 터뜨릴 수 있도록 안전망을 걸어두고 싶다.** 
이때 언리얼에서 제공하는 가장 적합한 델리게이트 매크로는 무엇인가?

1) `DECLARE_MULTICAST_DELEGATE`
2) `DECLARE_DYNAMIC_DELEGATE`
3) `DECLARE_EVENT`
4) `DECLARE_DELEGATE_OneParam`

---
### 정답 및 해설
**정답: 3번 (DECLARE_EVENT)**
**해설:** 일반적인 멀티캐스트 델리게이트를 public으로 열어두면, 외부 클래스에서 실수로 `Broadcast()`를 호출해 보스가 죽지도 않았는데 이벤트를 터뜨리는 버그가 생길 수 있습니다. `DECLARE_EVENT`는 두 번째 매개변수로 소유자 클래스를 지정받아, **오직 지정된 클래스 안에서만 Broadcast를 허용**하는 보안성이 몹시 높은 델리게이트입니다.
