#include "Study13Delegate.h"

AStudy13Delegate::AStudy13Delegate()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AStudy13Delegate::TriggerAllEvents()
{
    // AStudy13Delegate 클래스 내부 영역입니다.
    // 자신이 선언한 델리게이트와 이벤트이므로 둘 다 마음대로 Broadcast(발사) 할 수 있습니다.
    MyDelegate.Broadcast();
    MyEvent.Broadcast();
}
