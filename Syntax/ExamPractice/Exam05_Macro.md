# [5장] C++ 매크로 시스템 (UFUNCTION) 예상 문제

## 문제 1
보물상자와 상호작용하는 `Interact()` 함수를 만들려고 한다. C++ 코드에 기본적인 상호작용 로직을 작성하되, 필요한 경우 블루프린트에서 이 로직을 덮어쓰거나(Override) 추가 동작을 구현할 수 있도록 허용하고 싶다.
이때 함수 선언부의 `UFUNCTION` 괄호 안에 들어가야 할 매크로와, C++에서 구현해야 할 함수 이름 규칙으로 올바른 것은?

1) 매크로: `BlueprintCallable` / 함수 구현명: `Interact()`
2) 매크로: `BlueprintImplementableEvent` / 함수 구현명: `Interact_Implementation()`
3) 매크로: `BlueprintNativeEvent` / 함수 구현명: `Interact_Implementation()`
4) 매크로: `BlueprintNativeEvent` / 함수 구현명: `Interact()`

---
### 정답 및 해설
**정답: 3번 (BlueprintNativeEvent / Interact_Implementation())**
**해설:** C++에 '기본(Native)' 동작을 만들어 두고 블루프린트에서 덮어쓸 수 있게 하려면 `BlueprintNativeEvent`를 사용해야 합니다. 그리고 이 매크로를 쓸 경우, C++의 소스 파일(`.cpp`)에서는 반드시 원래 함수명 뒤에 `_Implementation`을 붙여서 구현부를 작성해야 컴파일 에러가 나지 않습니다.
