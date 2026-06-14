#include "Study03Reflection.h"

AStudy03Reflection::AStudy03Reflection()
{
    PrimaryActorTick.bCanEverTick = false;
    
    // ----------------------------------------------------
    // 리플렉션 구조체 및 Enum 초기화 예시
    // ----------------------------------------------------
    
    // FName은 대소문자를 구분하지 않습니다. 단순 문자열이 아니라 내부적으로 숫자형태로 변환해 저장합니다.
    MyItemData.ItemID = FName(TEXT("Sword_01")); 
    
    // FString은 우리가 아는 일반 문자열입니다. 자유자재로 자르고 붙일 수 있습니다.
    MyItemData.ItemDescription = FString(TEXT("아주 평범한 쇠검입니다."));
    
    // FText는 다국어 처리(예: 한국어 '검', 영어 'Sword')를 대비하여 FromString 등의 변환 함수를 거쳐야 합니다.
    MyItemData.DisplayName = FText::FromString(TEXT("기본 철검")); 
    
    // Enum 초기화
    MyItemType = EStudyItemType::Weapon;
}
