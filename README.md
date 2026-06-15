# Unreal Engine 5 C++ Mastery & Exam Practice

## 폴더 구조

Source/Syntax/ (이론 및 코드)
- Public/ (.h) & Private/ (.cpp): 언리얼 C++의 핵심 주제들을 12개의 챕터로 나누어 구현한 코드 파일들입니다. 
- 모든 코드에는 가비지 컬렉션, CDO 작동 방식, 메모리 최적화 등을 설명하는 상세한 주석이 달려 있습니다.

Syntax/ExamPractice/ (연습문제)
- 각 챕터별로 학습한 내용을 테스트할 수 있는 마크다운(.md) 기반의 파일입니다.

## 학습내용

1. 자료구조 (Data Structure): TArray, TSet, TMap의 활용과 메모리 최적화
2. 액터와 컴포넌트 (Actor & Component): 계층 구조 조립과 동적 할당
3. 리플렉션 (Reflection): UPROPERTY, UFUNCTION 등 매크로와 GC의 이해
4. CDO (Class Default Object): 언리얼 객체 생성의 근간과 ConstructorHelpers
5. C++ 매크로 활용: BlueprintNativeEvent, BindWidget 등 UI/로직 연동
6. 충돌 시스템 (Collision): Overlap, Hit, FHitResult와 Sweep 검사
7. 입력 및 회전 (Input & Rotation): BindAxis, 3D 벡터 회전, 폰 빙의(Possess)
8. 애니메이션 (AnimInstance): NativeUpdateAnimation, 몽타주 강제 재생
9. 게임 인스턴스 (Game Instance): 싱글톤 수명 주기와 전역 데이터 관리
10. 게임 수학 (Vector Math): 내적(Dot), 외적(Cross)의 활용과 안전한 정규화
11. 컨테이너 심화 (Container): Emplace와 Add의 성능 차이, 이중 검색 오버헤드
12. 스마트 포인터 (Smart Pointer): TSubclassOf 타입 필터링과 TObjectPtr의 GC 규칙

## 학습 했던 방법

1. 먼저 Source 폴더에서 해당 챕터의 .h와 .cpp 파일을 엽니다.
2. 코드를 한 줄씩 읽어 내려가며, 상세하게 적힌 주석을 통해 언리얼 엔진의 규칙(왜 이렇게 써야만 하는지)을 이해합니다.
3. 코드를 모두 읽었다면 ExamPractice 폴더로 이동해 해당 챕터의 .md 파일을 엽니다.
4. 코드를 보지 않고 문제를 눈으로 풀며 코드 예측 및 빈칸 채우기를 진행합니다.
5. 파일 맨 아래의 해설을 보며 채점하고, 몰랐던 엔진의 함정(크래시 발생 원인 등)을 다시 숙지합니다.
