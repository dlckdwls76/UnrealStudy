#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Study09GameInst.generated.h"

UCLASS()
class SYNTAX_API UStudy09GameInst : public UGameInstance
{
    GENERATED_BODY()
    
public:
    // ==============================================================================
    // [9] 게임 인스턴스 (Game Instance)
    // ==============================================================================
    // 특징: 액터(AActor)는 레벨이 넘어가면 다 죽습니다(Destroy). 
    //      하지만 UGameInstance는 게임 프로그램이 켜질 때 단 1번 생성되고, 게임을 끄기 전까지 
    //      절대 파괴되지 않는 싱글톤(Singleton)과 유사한 최상위 객체입니다.
    // 용도: 레벨 1에서 레벨 2로 넘어가더라도 유지되어야 하는 플레이어의 전체 점수, 인벤토리, 옵션 설정 등을 저장합니다.
    
    // Init()는 게임 인스턴스가 최초로 생성될 때 호출되는 초기화 함수입니다.
    virtual void Init() override;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Study|Data", meta = (AllowPrivateAccess = "true"))
    int32 GlobalTotalScore;

    // ==============================================================================
    // [예시 문제: 게임 인스턴스]
    // Q: 액터 내부의 C++ 코드에서 현재 실행 중인 게임의 인스턴스를 얻어와서, 
    //    우리가 만든 UStudy09GameInst 클래스로 형변환(Casting)하여 포인터 변수에 저장하려고 합니다.
    //    빈칸에 들어갈 올바른 함수와 코드는 무엇인가요?
    //    UStudy09GameInst* MyGI = (A) ( (B) );
    // 
    // A: (A) Cast<UStudy09GameInst>
    //    (B) GetGameInstance()  또는  GetWorld()->GetGameInstance()
    // ==============================================================================
};
