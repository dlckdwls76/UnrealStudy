#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Study05Macro.generated.h"

UCLASS()
class SYNTAX_API AStudy05Macro : public AActor
{
    GENERATED_BODY()
    
public:    
    AStudy05Macro();

public:
    // ==============================================================================
    // [5] C++ 매크로 시스템 (UFUNCTION)
    // ==============================================================================
    
    // BlueprintCallable: 이 함수를 블루프린트 이벤트 그래프에서 실행 노드로 만들어줍니다. (일반 함수)
    UFUNCTION(BlueprintCallable, Category = "Study|Macro")
    void ExecuteMacroAction();

    // BlueprintPure: 실행 핀(하얀 줄) 없이 오직 값만 계산해서 반환해주는 초록색 노드가 됩니다. (Get 함수에 씀)
    UFUNCTION(BlueprintPure, Category = "Study|Macro")
    int32 GetMacroValue() const;

    // BlueprintImplementableEvent: C++ 헤더에 선언만 해두고, 구현은 블루프린트에서 노드로 짜도록 만듭니다.
    UFUNCTION(BlueprintImplementableEvent, Category = "Study|Macro")
    void OnMyCustomEventTriggered();

private:
    // ==============================================================================
    // [5] C++ 매크로 시스템 (UPROPERTY)
    // ==============================================================================
    
    // EditAnywhere: CDO 화면과 맵에 배치된 인스턴스의 디테일 창 양쪽 모두에서 값을 수정할 수 있습니다.
    // VisibleAnywhere: 편집은 불가능하고 보기만 가능합니다. (보통 컴포넌트 포인터에 씀)
    // BlueprintReadWrite: 블루프린트 변수처럼 Get / Set 노드를 둘 다 꺼내 쓸 수 있습니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Study|Macro", meta = (AllowPrivateAccess = "true"))
    int32 MacroTestValue;

    // ==============================================================================
    // [예시 문제: UFUNCTION 매크로]
    // Q: 캐릭터의 남은 체력을 반환하는 GetHealth() C++ 함수를 만들었습니다. 
    //    블루프린트에서 "실행 핀(하얀 줄)" 없이 오직 값만 꺼내 쓰는 노드(순수 노드)로 
    //    만들고 싶습니다. UFUNCTION 괄호 안에 어떤 키워드를 넣어야 할까요?
    // 
    // A: BlueprintPure 입니다. 
    //    (참고: 내부 상태를 변경하지 않는 Get 계열 함수는 보통 const를 붙이고 BlueprintPure를 적용합니다.)
    // ==============================================================================
};
