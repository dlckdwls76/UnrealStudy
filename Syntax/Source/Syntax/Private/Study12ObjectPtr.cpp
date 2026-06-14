#include "Study12ObjectPtr.h"

AStudy12ObjectPtr::AStudy12ObjectPtr()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AStudy12ObjectPtr::BeginPlay()
{
    Super::BeginPlay();
    TestSpawning();
}

void AStudy12ObjectPtr::TestSpawning()
{
    // 클래스 변수에 정보가 제대로 채워져 있는지 검사 (nullptr 체크)
    if (ActorClassToSpawn && GetWorld())
    {
        // GetWorld()->SpawnActor 함수는 런타임에 액터를 소환합니다.
        // 이때 첫 번째 인자로 "어떤 클래스(타입)를 스폰할지" TSubclassOf 변수를 넘겨줍니다.
        AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorClassToSpawn, GetActorLocation(), GetActorRotation());
    }
}
