// 본인 헤더 포함
#include "Study12ObjectPtr.h"

AStudy12ObjectPtr::AStudy12ObjectPtr()
{
    // 최적화를 위한 틱 비활성화
    PrimaryActorTick.bCanEverTick = false;
}

void AStudy12ObjectPtr::BeginPlay()
{
    Super::BeginPlay();
    // 시작 시 스폰 테스트 실행
    TestSpawning();
}

void AStudy12ObjectPtr::TestSpawning()
{
    // 클래스 변수에 정보가 제대로 채워져 있는지, 그리고 현재 월드(레벨)가 존재하는지 검사 (nullptr 체크)
    if (ActorClassToSpawn && GetWorld())
    {
        // GetWorld()->SpawnActor 함수는 런타임에 월드상에 실제로 객체를 소환(Spawn)하는 강력한 함수입니다.
        // 이때 첫 번째 인자로 "어떤 클래스(타입) 설계도를 보고 만들지" TSubclassOf 변수를 넘겨줍니다.
        // 그리고 현재 이 액터의 위치(GetActorLocation)와 회전(GetActorRotation) 값에 그대로 겹쳐서 스폰시킵니다.
        AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorClassToSpawn, GetActorLocation(), GetActorRotation());
        
        // 스폰 성공 시 로그
        if (SpawnedActor)
        {
            UE_LOG(LogTemp, Warning, TEXT("성공적으로 스폰되었습니다: %s"), *SpawnedActor->GetName());
        }
    }
}
