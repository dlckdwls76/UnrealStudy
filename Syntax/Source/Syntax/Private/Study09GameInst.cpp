#include "Study09GameInst.h"

void UStudy09GameInst::Init()
{
    Super::Init();

    // 초기화 과정
    GlobalTotalScore = 0;
    UE_LOG(LogTemp, Warning, TEXT("[GameInstance] 시스템이 초기화되었습니다. 점수를 0으로 세팅합니다."));
}
