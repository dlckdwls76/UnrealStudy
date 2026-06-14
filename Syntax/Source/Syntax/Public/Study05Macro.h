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
    // [5] C++ 매크로 시스템 (UFUNCTION 심화)
    // ==============================================================================
    
    UFUNCTION(BlueprintCallable, Category = "Study|Macro")
    void ExecuteMacroAction();

    UFUNCTION(BlueprintPure, Category = "Study|Macro")
    int32 GetMacroValue() const;

    UFUNCTION(BlueprintImplementableEvent, Category = "Study|Macro")
    void OnMyCustomEventTriggered();

    // BlueprintNativeEvent: C++에서 '기본 동작(Native)'을 구현해두되, 
    // 블루프린트에서 원한다면 그 기본 동작을 덮어쓰고(Override) 입맛대로 바꿀 수 있게 해줍니다.
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Study|Macro")
    void Interact();
    virtual void Interact_Implementation(); // BlueprintNativeEvent를 쓰면 무조건 "_Implementation" 함수를 같이 선언하고 구현해야 합니다.

private:
    // ==============================================================================
    // [5] C++ 매크로 시스템 (UPROPERTY 심화 메타데이터)
    // ==============================================================================
    
    // EditAnywhere, BlueprintReadWrite 외에도 다양한 메타(meta) 속성으로 에디터를 편하게 만들 수 있습니다.
    // ClampMin/ClampMax: 에디터에서 값을 입력할 때 최소/최대치를 제한합니다.
    // DisplayName: 실제 C++ 변수 이름은 MacroTestValue지만, 블루프린트에는 "매크로 테스트 값"이라는 예쁜 한글 이름으로 보여줍니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Study|Macro", meta = (AllowPrivateAccess = "true", ClampMin = "0", ClampMax = "100", DisplayName = "매크로 테스트 값 (0~100)"))
    int32 MacroTestValue;

    // ==============================================================================
    // [예시 문제 2: BlueprintNativeEvent]
    // Q: 아이템과 상호작용하는 Interact() 함수를 만들었습니다. 
    //    일반적인 무기는 C++에 짜놓은 기본 로직을 따르지만, '저주받은 무기'는 블루프린트에서 
    //    특수한 로직으로 덮어쓰기(Override) 하고 싶습니다. 
    //    UFUNCTION 괄호 안에 어떤 매크로를 넣어야 하며, C++ .cpp 파일에는 함수 이름을 어떻게 적어 구현해야 할까요?
    // 
    // A: 1) 매크로: BlueprintNativeEvent
    //    2) C++ 구현 함수명: Interact_Implementation()
    // ==============================================================================
};
