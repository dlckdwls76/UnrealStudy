#include "Study06Collision.h"
#include "Components/BoxComponent.h"

AStudy06Collision::AStudy06Collision()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    RootComponent = CollisionBox;

    // ----------------------------------------------------
    // 충돌 프로필(Profile) 및 반응 설정
    // ----------------------------------------------------
    
    // SetCollisionProfileName: 언리얼 에디터의 '프로젝트 세팅 -> 콜리전'에 정의된 프리셋 이름을 적용합니다.
    CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    
    // 오버랩 이벤트를 발생시킬지 여부. 블루프린트의 "Generate Overlap Events" 체크박스와 동일합니다.
    CollisionBox->SetGenerateOverlapEvents(true);

    // ----------------------------------------------------
    // 동적 델리게이트 바인딩 (이벤트 연결)
    // ----------------------------------------------------
    // 무언가 이 박스에 겹쳤을 때(BeginOverlap), OnMyOverlapBegin 함수를 실행해달라고 엔진에 예약(바인딩)합니다.
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AStudy06Collision::OnMyOverlapBegin);
}

void AStudy06Collision::OnMyOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // 충돌한 OtherActor가 자기 자신이 아닌 경우에만 처리
    if (OtherActor && OtherActor != this)
    {
        UE_LOG(LogTemp, Warning, TEXT("[Collision] %s와(과) 오버랩 되었습니다!"), *OtherActor->GetName());
    }
}
