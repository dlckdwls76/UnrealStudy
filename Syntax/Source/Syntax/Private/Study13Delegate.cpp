// 본인 헤더
#include "Study13Delegate.h"

AStudy13Delegate::AStudy13Delegate()
{
    // 불필요 연산 차단
    PrimaryActorTick.bCanEverTick = false;
}

void AStudy13Delegate::TriggerAllEvents()
{
    // 여기는 AStudy13Delegate 클래스 '내부' 영역입니다.
    // 자신이 직접 선언한 델리게이트와 이벤트이므로 컴파일 에러 없이 둘 다 마음대로 Broadcast(발사) 할 수 있습니다.
    
    // 확성기 발사! (바인딩된 모든 함수 일제히 실행)
    MyDelegate.Broadcast();
    
    // 방송국 스피커 발사! (바인딩된 모든 함수 일제히 실행)
    MyEvent.Broadcast();
}
