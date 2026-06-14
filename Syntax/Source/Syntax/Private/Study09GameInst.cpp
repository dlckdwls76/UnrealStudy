// 자신이 선언된 헤더 파일을 포함합니다.
#include "Study09GameInst.h"

void UStudy09GameInst::Init()
{
    // 부모 클래스(UGameInstance)가 원래 해야 할 필수 초기화 작업을 누락하지 않도록 Super를 부릅니다.
    Super::Init();

    // 초기화 과정: 게임이 막 켜졌으므로 전역 점수를 0으로 셋팅합니다.
    GlobalTotalScore = 0;
    
    // 이 로그는 에디터에서 플레이(PIE) 버튼을 누르는 그 순간 단 한 번만 출력됩니다.
    UE_LOG(LogTemp, Warning, TEXT("[GameInstance] 시스템이 초기화되었습니다. 점수를 0으로 세팅합니다."));
}
