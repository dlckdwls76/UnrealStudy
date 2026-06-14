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
    
    OnMyCustomEventTriggered();
}

int32 AStudy05Macro::GetMacroValue() const
{
    return MacroTestValue;
}

// BlueprintNativeEvent의 실제 C++ 기본 동작 구현부입니다.
// 반드시 이름 뒤에 "_Implementation"을 붙여야 합니다.
void AStudy05Macro::Interact_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("C++로 짜여진 기본 상호작용(Interact) 기능이 실행되었습니다."));
    // 만약 블루프린트에서 이 이벤트를 덮어쓰고 커스텀 노드를 연결했다면, 이 C++ 로그는 호출되지 않고 블루프린트 쪽 내용만 실행됩니다.
    // (단, 블루프린트에서 해당 노드 우클릭 -> 'Parent: Interact' 노드를 연결해주면 둘 다 실행됩니다)
}
