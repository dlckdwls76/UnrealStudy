#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Study13Delegate.generated.h"

// ==============================================================================
// [13] 이벤트(Event)와 멀티캐스트 델리게이트(Delegate)의 차이점
// ==============================================================================
// 공통점: 둘 다 여러 함수를 한 번에 바인딩해 두고, Broadcast()를 외치면 다 같이 실행되는 구조입니다.

// [멀티캐스트 델리게이트] - 누구나 방송(Broadcast) 가능한 확성기
DECLARE_MULTICAST_DELEGATE(FMyStudyMulticastDelegate);

// [이벤트] - 방송국(AStudy13Delegate 클래스) 전용 스피커
// 이벤트는 반드시 두 번째 인자로 '자신을 소유하는 클래스'를 명시해야 합니다.
DECLARE_EVENT(AStudy13Delegate, FMyStudyEvent);


UCLASS()
class SYNTAX_API AStudy13Delegate : public AActor
{
    GENERATED_BODY()
    
public:    
    AStudy13Delegate();

public:
    // 외부 클래스들이 마음껏 바인딩(Add) 할 수 있게 둘 다 public으로 열어둡니다.
    FMyStudyMulticastDelegate MyDelegate;
    FMyStudyEvent MyEvent;

    // 정상적으로 소유자가 이벤트를 터뜨리는 함수
    void TriggerAllEvents();

    // ==============================================================================
    // [예시 문제: 이벤트와 델리게이트]
    // Q: 외부 클래스(예: SomeOtherActor)에서 AStudy13Delegate의 인스턴스에 접근했습니다.
    //    그 다음, 아래 두 코드를 연달아 실행하려고 합니다. 과연 컴파일이 성공할까요?
    //    Target->MyDelegate.Broadcast();
    //    Target->MyEvent.Broadcast();
    // 
    // A: 컴파일에 실패(에러)합니다!
    //    이유: 첫 번째 MyDelegate.Broadcast()는 통과합니다. 하지만 두 번째 MyEvent.Broadcast()는 막힙니다.
    //         이벤트(Event)는 오직 이벤트를 선언하고 소유한 원본 클래스 내부에서만 
    //         Broadcast()를 부를 수 있도록 권한을 꽉 잠가버린 안전한 델리게이트이기 때문입니다.
    // ==============================================================================
};
