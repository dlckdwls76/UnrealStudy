#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Study02ActorComp.generated.h"

// 컴포넌트 전방 선언
class UBoxComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UMovementComponent; // 논리 전용 컴포넌트 예시

UCLASS()
class SYNTAX_API AStudy02ActorComp : public AActor
{
    GENERATED_BODY()
    
public:    
    AStudy02ActorComp();

protected:
    virtual void BeginPlay() override;

private:
    // ==============================================================================
    // [2] 언리얼의 액터와 컴포넌트 (심화)
    // ==============================================================================
    // 💡 컴포넌트의 두 가지 거대한 부류 (아주 중요)
    // 1. USceneComponent: 위치(Location), 회전(Rotation), 크기(Scale) 등 '트랜스폼(Transform)'을 
    //                     가지며 화면에 배치될 수 있는 물리적 컴포넌트입니다. (Box, Mesh, Camera 등)
    // 2. UActorComponent: 트랜스폼이 아예 없습니다! 오직 '기능(Logic)'과 데이터만을 전담하는 
    //                     눈에 보이지 않는 가벼운 컴포넌트입니다. (Movement, Inventory, Status 등)

    // ----------------------------------------------------
    // [씬 컴포넌트들] - 부모-자식 형태의 계층 구조를 짤 수 있습니다.
    // ----------------------------------------------------
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Study|Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UBoxComponent> RootBox;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Study|Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UStaticMeshComponent> MeshComp;

    // 3인칭 게임의 필수품: 카메라 붐(스프링암)과 카메라 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Study|Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USpringArmComponent> SpringArmComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Study|Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCameraComponent> CameraComp;

    // ----------------------------------------------------
    // [액터 컴포넌트] - 트랜스폼이 없어 물리적으로 부착(SetupAttachment) 불가
    // ----------------------------------------------------
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Study|Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UMovementComponent> LogicMovementComp;
};
