# [7장] 캐릭터 회전 제어와 입력 예상 문제

## 문제 1
3인칭 RPG(예: 젤다, 원신)와 같이, 마우스를 돌려 카메라를 움직여도 캐릭터 몸은 그대로 있고, 오직 "이동 키(WASD)를 눌러 걸어가는 방향"으로만 캐릭터가 몸을 부드럽게 돌리도록 세팅하려고 한다. 
다음 중 `ACharacter` 생성자에서 설정해야 할 올바른 변수 조작은 무엇인가?

1) `bUseControllerRotationYaw = true;`
2) `GetCharacterMovement()->bOrientRotationToMovement = false;`
3) `bUseControllerRotationYaw = false;` 와 `GetCharacterMovement()->bOrientRotationToMovement = true;`
4) `bUseControllerRotationPitch = true;`

---
### 정답 및 해설
**정답: 3번**
**해설:** 컨트롤러(마우스)의 좌우 회전에 캐릭터의 몸통이 즉각적으로 동기화되는 것을 막기 위해 폰의 `bUseControllerRotationYaw`를 `false`로 꺼야 합니다. 그런 다음 캐릭터 무브먼트 컴포넌트의 `bOrientRotationToMovement`를 `true`로 설정해야 현재 이동하고 있는 방향을 향해 캐릭터가 스스로 몸을 회전하게 됩니다.
