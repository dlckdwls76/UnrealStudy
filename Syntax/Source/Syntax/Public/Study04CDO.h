#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Study04CDO.generated.h"

class UStaticMeshComponent;

UCLASS()
class SYNTAX_API AStudy04CDO : public AActor
{
    GENERATED_BODY()
    
public:    
    AStudy04CDO();

protected:
    virtual void BeginPlay() override;

private:
    // ==============================================================================
    // [4] CDO (Class Default Object) 심화
    // ==============================================================================
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Study|CDO", meta = (AllowPrivateAccess = "true"))
    int32 BaseDamage;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Study|CDO", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UStaticMeshComponent> MeshComp;

    // ==============================================================================
    // [예시 문제 2: CDO와 에셋 로드(ConstructorHelpers)]
    // Q: 생성자(Constructor)에서 ConstructorHelpers::FObjectFinder를 이용해 특정 3D 메시(.uasset)를 
    //    불러와 컴포넌트에 입혀두려고 합니다. 만약 이 코드를 BeginPlay() 안으로 옮겨서 실행하면 어떻게 될까요?
    // 
    // A: 에디터 크래시(Crash)가 발생하거나 컴파일 타임 에러가 납니다.
    //    이유: ConstructorHelpers는 오직 "CDO를 생성하는 생성자 타임(초기화 시점)"에만 
    //         동작하도록 설계된 엔진 전용 유틸리티입니다. 런타임(BeginPlay 이후)에 에셋을 
    //         동적으로 로드하려면 LoadObject나 동기/비동기 에셋 로딩 방식(StreamableManager)을 써야 합니다.
    // ==============================================================================
};
