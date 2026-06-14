// C++의 기본 문법으로, 이 헤더 파일이 컴파일러에 의해 여러 번 중복 포함되는 것을 막아줍니다.
#pragma once

// 언리얼 엔진의 필수 코어 기능들을 담고 있는 헤더입니다.
#include "CoreMinimal.h"
// 부모 클래스인 UGameInstance를 사용하기 위해 포함합니다.
#include "Engine/GameInstance.h"
// 리플렉션 시스템을 위한 자동 생성 헤더입니다. 무조건 가장 마지막에 포함되어야 합니다.
#include "Study09GameInst.generated.h"

// 리플렉션 매크로: 언리얼 엔진이 이 클래스의 존재를 인식하게 만들어줍니다.
UCLASS()
class SYNTAX_API UStudy09GameInst : public UGameInstance // 게임의 뼈대(Instance)를 상속받습니다.
{
    // 리플렉션 코드가 들어갈 자리입니다. (필수)
    GENERATED_BODY()
    
public:
    // ==============================================================================
    // [9] 게임 인스턴스 (Game Instance)
    // ==============================================================================
    // 특징: 일반적인 액터(AActor)는 레벨을 이동하면 파괴(Destroy)되고 새로 스폰됩니다.
    //       하지만 UGameInstance는 게임 프로세스가 켜질 때 단 한 번 생성되고, 
    //       게임을 완전히 종료하기 전까지 절대 파괴되지 않는 '싱글톤(Singleton)' 형태의 최상위 객체입니다.
    
    // Init()는 일반 액터의 BeginPlay()처럼, 게임 인스턴스가 최초로 생성될 때 호출되는 초기화 함수입니다.
    virtual void Init() override;

private:
    // 레벨이 넘어가도 무조건 유지되어야 하는 전역 변수(예: 총 점수, 플레이어 인벤토리 데이터)를 선언하기 가장 좋습니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Study|Data", meta = (AllowPrivateAccess = "true"))
    int32 GlobalTotalScore;

    // ==============================================================================
    // [예시 문제: 게임 인스턴스]
    // Q: 액터 내부의 C++ 코드에서 현재 실행 중인 게임 인스턴스를 가져와서, 
    //    우리가 만든 UStudy09GameInst 클래스로 형변환(Casting)하여 포인터 변수에 저장하려고 합니다.
    //    빈칸에 들어갈 올바른 함수와 코드는 무엇인가요?
    //    UStudy09GameInst* MyGI = (A) ( (B) );
    // 
    // A: (A) Cast<UStudy09GameInst>
    //    (B) GetGameInstance()  또는  GetWorld()->GetGameInstance()
    // ==============================================================================
};
