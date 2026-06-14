#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Study07CharAsset.generated.h"

UCLASS()
class SYNTAX_API AStudy07CharAsset : public ACharacter
{
    GENERATED_BODY()

public:
    AStudy07CharAsset();

protected:
    virtual void BeginPlay() override;

private:
    // ==============================================================================
    // [7] 캐릭터를 구성하는 주요 에셋 (심화: 회전과 컨트롤러)
    // ==============================================================================
    // 캐릭터(ACharacter)는 단순히 껍데기일 뿐이고, 그 껍데기에 빙의(Possess)해서 조종하는 '영혼'이 바로 Controller입니다.
    // 무브먼트 컴포넌트는 이 컨트롤러의 입력(마우스/키보드)을 받아 물리적인 이동을 처리합니다.

    // ==============================================================================
    // [예시 문제 2: 폰의 회전 방식 차이 (매우 중요)]
    // Q: 1) 1인칭 슈팅(FPS) 게임처럼 캐릭터가 무조건 마우스가 보는 방향(카메라 방향)을 따라 똑같이 회전해야 할 때 켜는 옵션과, 
    //    2) 3인칭 RPG(원신, 젤다 등)처럼 카메라 방향과 상관없이 캐릭터가 "내가 이동하는 방향"을 바라보며 자연스럽게 몸을 돌리게 할 때 켜는 옵션은 무엇인가요?
    // 
    // A: 1) 마우스 방향 강제 일치(FPS/TPS 타겟팅): 
    //       bUseControllerRotationYaw = true;
    //    2) 이동 방향으로 몸 회전(3인칭 RPG): 
    //       GetCharacterMovement()->bOrientRotationToMovement = true;
    //       (참고: 2번 RPG 방식을 제대로 쓰려면 반드시 1번의 bUseControllerRotationYaw를 false로 꺼줘야 엔진이 헷갈리지 않습니다.)
    // ==============================================================================
};
