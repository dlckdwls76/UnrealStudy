#include "Study05Macro.h"

AStudy05Macro::AStudy05Macro()
{
    PrimaryActorTick.bCanEverTick = false;
    MacroTestValue = 0;
}

void AStudy05Macro::ExecuteMacroAction()
{
    MacroTestValue += 10;
    UE_LOG(LogTemp, Warning, TEXT("MacroTestValue: %d"), MacroTestValue);
    
    // 블루프린트로 구현부를 넘긴 이벤트를 C++ 코드 특정 시점에 호출할 수 있습니다.
    OnMyCustomEventTriggered();
}

int32 AStudy05Macro::GetMacroValue() const
{
    // BlueprintPure의 예시
    return MacroTestValue;
}
