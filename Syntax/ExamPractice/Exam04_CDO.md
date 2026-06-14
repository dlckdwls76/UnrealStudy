# [4장] CDO (Class Default Object) 예상 문제

## 문제 1
개발자가 무기 액터(`AWeapon`)의 C++ 코드에서 3D 메시 에셋(`.uasset`)을 불러와 컴포넌트에 입히기 위해 `ConstructorHelpers::FObjectFinder`를 사용했다. 
다음 중 이 코드가 **안전하게(크래시 없이) 실행될 수 있는 위치**로 알맞은 것은?

1) `AWeapon::AWeapon()` (생성자 내부)
2) `AWeapon::BeginPlay()` (게임 시작 함수 내부)
3) `AWeapon::Tick(float DeltaTime)` (매 프레임 호출 내부)
4) 아무 커스텀 함수 내부

---
### 정답 및 해설
**정답: 1번 (AWeapon::AWeapon() 생성자 내부)**
**해설:** `ConstructorHelpers`는 언리얼 엔진이 시작될 때 CDO(Class Default Object)를 굽어내는(생성하는) 과정, 즉 **클래스 생성자 내부에서만 동작하도록 설계된 유틸리티**입니다. 런타임(`BeginPlay` 이후)에 이 함수를 호출하면 엔진 크래시가 발생합니다.
