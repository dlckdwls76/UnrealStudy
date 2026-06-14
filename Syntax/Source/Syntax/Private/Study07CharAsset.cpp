// 자신이 선언된 헤더 파일을 가장 먼저 포함해야 합니다.
#include "Study07CharAsset.h"
// 무브먼트 컴포넌트의 기능(이동 속도, 점프력 등)을 제어하기 위해 포함합니다.
#include "GameFramework/CharacterMovementComponent.h"
// 입력 컴포넌트(키 바인딩)를 다루기 위해 포함합니다.
#include "Components/InputComponent.h"

AStudy07CharAsset::AStudy07CharAsset()
{
    // 매 프레임마다 Tick() 함수를 호출할지 결정합니다. 성능 최적화를 위해 불필요하면 false로 끄는 것이 전공자의 정석입니다.
    PrimaryActorTick.bCanEverTick = false;

    // GetMesh()는 ACharacter가 기본적으로 가지고 있는 뼈대(Skeletal) 메시 컴포넌트를 가져옵니다.
    if (GetMesh())
    {
        // 캡슐 컴포넌트 정중앙에 위치한 메시를 바닥으로 내리기 위해 Z축을 -90 깎습니다.
        GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
        // 메시가 정면(X축)을 바라보게 하기 위해 Z축(Yaw) 회전을 -90도 돌려줍니다.
        GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
    }

    // GetCharacterMovement()는 걷기, 점프, 수영, 낙하를 모두 처리하는 만능 물리 컴포넌트를 가져옵니다.
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = 500.0f; // 최대 걷기 속도를 초당 500 유닛(cm)으로 제한
        GetCharacterMovement()->JumpZVelocity = 400.0f; // 스페이스바를 눌렀을 때 위로 튀어오르는 초기 속도(힘)
        
        // ----------------------------------------------------
        // 심화: 캐릭터의 몸체 회전 제어 (3인칭 RPG 국룰 세팅)
        // ----------------------------------------------------
        
        // 1. 마우스를 돌린다(컨트롤러 회전)고 해서 캐릭터 몸체가 바로 휙휙 따라 돌아가지 않게 차단합니다.
        bUseControllerRotationPitch = false; // 위아래 끄덕임 무시
        bUseControllerRotationYaw = false;   // 좌우 도리도리 무시
        bUseControllerRotationRoll = false;  // 옆으로 기울기 무시

        // 2. 대신, 무브먼트 컴포넌트가 알아서 "이동하는 방향(키보드를 누른 방향)"을 쳐다보며 몸을 부드럽게 돌리도록 허용합니다.
        GetCharacterMovement()->bOrientRotationToMovement = true;
        
        // 3. 몸이 회전하는 속도입니다. Z축(Yaw)으로 초당 540도 속도로 휙 돌아갑니다.
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
    }
}

void AStudy07CharAsset::BeginPlay()
{
    // 부모 클래스(ACharacter -> APawn -> AActor)의 BeginPlay를 먼저 실행하여 엔진 필수 초기화를 보장합니다.
    Super::BeginPlay();
}

void AStudy07CharAsset::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // 부모의 기본 입력 세팅을 먼저 호출합니다.
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // ----------------------------------------------------
    // C++ 코어 입력 바인딩 (Input Binding)의 정석
    // ----------------------------------------------------
    
    // BindAxis: 조이스틱 아날로그 스틱이나 W,S,A,D 처럼 "계속 누르고 있는 수치(-1.0 ~ 1.0)"를 매 프레임 전달받습니다.
    // 인자 설명: ("프로젝트 세팅의 이름", 바인딩될 객체(this), &호출할 C++ 함수 주소)
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AStudy07CharAsset::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AStudy07CharAsset::MoveRight);

    // BindAction: 스페이스바나 마우스 클릭처럼 "딱 한 번 눌렸을 때(IE_Pressed)" 1회성으로 실행됩니다.
    // 엔진에 이미 내장되어 있는 점프 함수(ACharacter::Jump)를 직접 연결한 예시입니다.
    PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
}

void AStudy07CharAsset::MoveForward(float Value)
{
    // 컨트롤러(영혼)가 존재하고, 플레이어가 키보드를 눌러 Value가 0이 아닐 때만 실행합니다.
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        // 단순히 "월드의 절대적인 앞(X축)"이 아니라, 카메라(컨트롤러)가 바라보고 있는 시점에서의 "앞"이 어딘지 알아내야 합니다.
        const FRotator Rotation = Controller->GetControlRotation(); // 카메라의 현재 회전값
        const FRotator YawRotation(0, Rotation.Yaw, 0); // 고개를 들거나 숙인 각도(Pitch)는 무시하고, 지면과 평행한 좌우(Yaw) 방향만 추출합니다. (하늘로 날아가는 것 방지)

        // 수학의 회전 행렬(RotationMatrix)을 이용해, 해당 Yaw 각도가 가리키는 X축(전방) 단위 벡터(길이가 1인 방향 벡터)를 추출해냅니다.
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        
        // 이동 컴포넌트에게 해당 방향으로 Value(-1 또는 1)만큼의 힘(의지)을 가하라고 명령합니다.
        AddMovementInput(Direction, Value);
    }
}

void AStudy07CharAsset::MoveRight(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // 앞뒤 이동과 원리는 완전히 같으나, 이번엔 X축(전방)이 아니라 Y축(우측) 벡터를 추출해 우측으로 이동시킵니다.
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}
