// 헤더 파일이 여러 번 포함(Include)되는 것을 방지하는 전처리 명령어입니다. (C++ 기본 문법)
#pragma once

// 언리얼 엔진의 필수적인 기본 타입과 매크로들을 포함하는 가장 핵심적인 헤더입니다.
#include "CoreMinimal.h"
// 캐릭터 클래스의 부모인 ACharacter를 사용하기 위해 포함합니다.
#include "GameFramework/Character.h"
// 언리얼 헤더 툴(UHT)이 리플렉션 코드를 자동 생성하여 저장하는 파일입니다. 무조건 맨 마지막에 include 해야 합니다.
#include "Study07CharAsset.generated.h"

// UCLASS 매크로: 이 클래스가 언리얼 리플렉션 시스템(에디터, 가비지 컬렉션 등)의 관리를 받게 해줍니다.
UCLASS()
class SYNTAX_API AStudy07CharAsset : public ACharacter // ACharacter 상속: 사람 형태의 폰(Pawn)을 만드는데 최적화된 클래스입니다.
{
    // 리플렉션 시스템이 필요로 하는 내부 코드를 자동으로 삽입해주는 매크로입니다. (클래스 최상단에 필수)
    GENERATED_BODY()

public:
    // 생성자(Constructor): 게임이 시작되기 전, 에디터에 배치되거나 메모리에 올라갈 때 단 한 번 호출되어 기본값을 세팅합니다.
    AStudy07CharAsset();

protected:
    // 게임이 시작되거나 액터가 레벨에 스폰되었을 때 딱 한 번 호출되는 가상 함수입니다. (주로 초기 상태 설정에 쓰임)
    virtual void BeginPlay() override;

public:
    // 폰(Pawn)이 플레이어 컨트롤러에 빙의(Possess)될 때 키보드/마우스 입력을 바인딩하는 핵심 함수입니다.
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    // 전진/후진 입력을 처리할 콜백 함수 (Value는 1.0(W), -1.0(S), 0.0(안누름) 값으로 들어옵니다)
    void MoveForward(float Value);
    
    // 좌/우 입력을 처리할 콜백 함수 (Value는 1.0(D), -1.0(A) 값으로 들어옵니다)
    void MoveRight(float Value);

    // ==============================================================================
    // [7] 캐릭터와 컨트롤러의 깊은 관계 (Possess와 Input 심화)
    // ==============================================================================
    // ACharacter 자체는 뇌(Controller)가 없는 빈 껍데기(육신)에 불과합니다.
    // 플레이어가 게임에 접속하면 눈에 보이지 않는 APlayerController(영혼/뇌)가 생성되고, 
    // 이 컨트롤러가 ACharacter의 몸에 빙의(Possess)해야 비로소 키보드 입력을 캐릭터가 받을 수 있습니다.

    // ==============================================================================
    // [예시 문제 3: 빙의(Possess)와 입력 해제]
    // Q: 캐릭터의 HP가 0이 되어 사망(래그돌) 상태가 되었습니다. 
    //    이때 플레이어가 키보드를 눌러도 더 이상 이 시체가 움직이지 못하게 하려면, 
    //    컨트롤러가 캐릭터에게 걸고 있는 빙의를 끊어야 합니다. 어떤 함수를 호출해야 할까요?
    // 
    // A: Controller->UnPossess() (또는 GetController()->UnPossess())
    //    해설: 빙의가 풀리는 순간, SetupPlayerInputComponent로 연결해둔 모든 입력 신호가 
    //         캐릭터로 전달되지 않고 차단되므로 가장 깔끔한 사망 입력 제한 방법입니다.
    // ==============================================================================
};
