#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Study04CDO.generated.h"

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
    // [4] CDO (Class Default Object)
    // ==============================================================================
    // 특징: 엔진이 초기화될 때 각 클래스별로 "단 1개만" 생성되는 기본 템플릿(원본) 객체입니다.
    //      레벨에 스폰되는 모든 인스턴스들은 처음 생성될 때 이 CDO를 복사해서 태어납니다.
    // 에디터 작용: 블루프린트를 열었을 때 우측 디테일 패널에 적혀있는 값들이 바로 CDO의 값입니다.
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Study|CDO", meta = (AllowPrivateAccess = "true"))
    int32 BaseDamage;
};
