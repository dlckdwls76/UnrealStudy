# [9장] 게임 인스턴스 (Game Instance) 예상 문제

## 문제 1
플레이어의 인벤토리 정보나 총점(Total Score)을 저장해두려고 한다. 이 데이터는 '레벨(맵)이 전환'되거나 '플레이어 캐릭터가 사망 후 리스폰' 되어도 절대 소멸하거나 초기화되지 않고 유지되어야 한다. 
언리얼 엔진 구조상 이러한 데이터를 보관하기 가장 적합한 C++ 클래스는 무엇인가?

1) `AActor`
2) `AGameModeBase`
3) `APlayerController`
4) `UGameInstance`

---
### 정답 및 해설
**정답: 4번 (UGameInstance)**
**해설:** `AActor`, `AGameMode`, `APlayerController`는 모두 현재 레벨(World)에 속해 있으므로, 맵을 이동하거나 재시작하면 객체가 파괴되고 메모리에서 날아갑니다. 반면 `UGameInstance`는 게임 프로세스 전체를 관장하는 최상위 싱글톤 객체이므로 게임을 끄기 전까지 유일하게 데이터가 영구 보존됩니다.
