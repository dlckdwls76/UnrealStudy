#include "Study04CDO.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AStudy04CDO::AStudy04CDO()
{
    PrimaryActorTick.bCanEverTick = false;
    
    // CDO에 직접 기록되는 기본값
    BaseDamage = 100;

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    RootComponent = MeshComp;

    // ----------------------------------------------------
    // 생성자와 CDO의 강력한 연관성: 에셋 로딩
    // ----------------------------------------------------
    // ConstructorHelpers는 엔진이 시작될 때 CDO를 만들면서 단 한 번 실행됩니다.
    // 여기서 찾은 경로나 데이터를 CDO에 박아두면, 이후 스폰되는 모든 인스턴스는 
    // 파일 경로를 다시 찾을 필요 없이 CDO의 정보를 그대로 복사해오기 때문에 엄청나게 효율적입니다.
    /*
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Path/To/Your/Mesh.Mesh"));
    if (MeshAsset.Succeeded())
    {
        MeshComp->SetStaticMesh(MeshAsset.Object);
    }
    */
}

void AStudy04CDO::BeginPlay()
{
    Super::BeginPlay();
    
    // ----------------------------------------------------
    // 인스턴스의 런타임 변경
    // ----------------------------------------------------
    BaseDamage = 200; // 이건 CDO 원본이 아니라, 지금 스폰된 내 몸(인스턴스)에만 적용됨.

    // ----------------------------------------------------
    // 코드 상에서 클래스의 CDO 원본에 접근하는 법
    // ----------------------------------------------------
    // 이 클래스(AStudy04CDO)의 기본 템플릿(CDO)을 가져옵니다.
    // 만약 AStudy04CDO* DefaultObj = GetClass()->GetDefaultObject<AStudy04CDO>(); 이렇게 해서
    // DefaultObj->BaseDamage를 여기서 9999로 바꿔버리면? 
    // -> 앞으로 태어날 모든 AStudy04CDO 몹들은 태어나자마자 데미지가 9999로 설정되는 무서운 일이 발생합니다.
}
