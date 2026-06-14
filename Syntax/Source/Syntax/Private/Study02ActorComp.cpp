#include "Study02ActorComp.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/MovementComponent.h"

AStudy02ActorComp::AStudy02ActorComp()
{
    PrimaryActorTick.bCanEverTick = false;

    // ----------------------------------------------------
    // 1. 씬 컴포넌트 (USceneComponent 상속) 생성 및 부착
    // ----------------------------------------------------
    RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RootBox"));
    RootComponent = RootBox; // 트랜스폼의 가장 상위 기준점

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(RootComponent);

    // 스프링암(SpringArm): 벽이나 장애물에 가려지면 카메라를 캐릭터 쪽으로 자동으로 당겨주는 스마트 지지대
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
    SpringArmComp->SetupAttachment(RootComponent);
    SpringArmComp->TargetArmLength = 300.0f; // 카메라를 뒤로 300 유닛만큼 거리를 둠

    // 카메라(Camera): 실제 플레이어의 화면이 되는 눈
    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
    CameraComp->SetupAttachment(SpringArmComp); // 스프링암의 끝자락에 매달아둠

    // ----------------------------------------------------
    // 2. 액터 컴포넌트 (UActorComponent 상속) 생성
    // ----------------------------------------------------
    LogicMovementComp = CreateDefaultSubobject<UMovementComponent>(TEXT("LogicMovementComp"));
    // ❌ 주의: 액터 컴포넌트는 Transform 정보가 없기 때문에 SetupAttachment()를 쓰면 컴파일/런타임 에러가 납니다!
    
    // ==============================================================================
    // [예시 문제 1: 액터와 컴포넌트 (런타임 생성)]
    // Q: 게임 플레이 도중(BeginPlay 이후) 새로운 컴포넌트를 액터에 동적으로 추가하려고 할 때,
    //    생성자에 쓰인 CreateDefaultSubobject를 써도 될까요?
    // 
    // A: 사용할 수 없습니다. (엔진이 켜지는 초기화 '생성자' 단계 전용 함수입니다.)
    //    런타임에는 NewObject<UType>(this) 함수로 메모리에 할당한 뒤, 
    //    컴포넌트의 RegisterComponent()를 직접 호출해 엔진 시스템에 수동 등록해야 합니다.
    // ==============================================================================
}

void AStudy02ActorComp::BeginPlay()
{
    Super::BeginPlay();

    // ----------------------------------------------------
    // 3. 런타임 컴포넌트 검색 (GetComponentByClass)
    // ----------------------------------------------------
    // 내가 어떤 컴포넌트를 들고 있는지 외부에서 찾거나 검색할 때 가장 많이 쓰는 함수입니다.
    if (UBoxComponent* FoundBox = GetComponentByClass<UBoxComponent>())
    {
        UE_LOG(LogTemp, Warning, TEXT("[ActorComp] 박스 컴포넌트를 성공적으로 찾아냈습니다: %s"), *FoundBox->GetName());
    }

    // ==============================================================================
    // [예시 문제 2: 컴포넌트 클래스 최적화]
    // Q: 캐릭터의 인벤토리 아이템 목록과 무게를 계산하는 전용 컴포넌트 "UInventoryComponent"를 
    //    만들려고 합니다. 이 컴포넌트는 화면에 보일 필요도, 물리적 위치 정보(X,Y,Z)를 가질 필요도 없습니다.
    //    이때 C++ 부모 클래스로 USceneComponent 와 UActorComponent 중 무엇을 선택해야 최적화에 좋을까요?
    // 
    // A: UActorComponent 입니다.
    //    이유: USceneComponent는 내부적으로 위치, 회전, 크기(Transform)를 계산하고 부모-자식 간 
    //         행렬(Matrix) 연산을 수행하는 꽤 무거운 클래스입니다.
    //         단순 논리/데이터 보관이 목적이라면 트랜스폼 기능이 쏙 빠져 훨씬 가벼운 
    //         UActorComponent를 상속받는 것이 언리얼 개발의 기본 정석입니다.
    // ==============================================================================
}
