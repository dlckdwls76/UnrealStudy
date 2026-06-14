#include "Study06Collision.h"
#include "Components/BoxComponent.h"

AStudy06Collision::AStudy06Collision()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    RootComponent = CollisionBox;

    // 프로필 세팅
    CollisionBox->SetCollisionProfileName(TEXT("BlockAllDynamic")); // 블록(막힘) 반응으로 변경
    
    // 오버랩 이벤트를 켭니다.
    CollisionBox->SetGenerateOverlapEvents(true);

    // Hit(물리적 충돌) 이벤트를 켜려면 이 옵션이 true여야 합니다. (블루프린트의 "Simulation Generates Hit Events")
    CollisionBox->SetNotifyRigidBodyCollision(true);

    // 델리게이트 바인딩
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AStudy06Collision::OnMyOverlapBegin);
    CollisionBox->OnComponentHit.AddDynamic(this, &AStudy06Collision::OnMyComponentHit);
}

void AStudy06Collision::BeginPlay()
{
    Super::BeginPlay();
    
    // 런타임에 위치를 변경할 때 bSweep(두번째 인자)을 true로 주면 가다가 부딪힙니다.
    // SetActorLocation(FVector(1000, 0, 0), true);
}

void AStudy06Collision::OnMyOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        UE_LOG(LogTemp, Warning, TEXT("[Collision] %s와(과) 스치듯 겹쳤습니다! (Overlap)"), *OtherActor->GetName());
    }
}

void AStudy06Collision::OnMyComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this)
    {
        // HitResult 객체 안에는 충돌한 지점의 정확한 좌표(Location), 표면의 방향(Normal) 등 엄청난 정보가 들어있습니다.
        UE_LOG(LogTemp, Error, TEXT("[Collision] %s와(과) 쾅 하고 부딪혔습니다! (Hit)"), *OtherActor->GetName());
        UE_LOG(LogTemp, Warning, TEXT("충돌 지점: %s"), *Hit.ImpactPoint.ToString());
    }
}
