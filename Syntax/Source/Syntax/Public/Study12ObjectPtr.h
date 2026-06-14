// 헤더 중복 포함 방지
#pragma once

// 코어 헤더
#include "CoreMinimal.h"
// 부모 클래스 액터 헤더
#include "GameFramework/Actor.h"
// 리플렉션 자동 생성 헤더
#include "Study12ObjectPtr.generated.h"

// 언리얼 에디터 노출 매크로
UCLASS()
class SYNTAX_API AStudy12ObjectPtr : public AActor
{
    GENERATED_BODY() // 필수 매크로
    
public:    
    // 기본 생성자
    AStudy12ObjectPtr();

protected:
    // 게임 시작 시 호출
    virtual void BeginPlay() override;

private:
    // ==============================================================================
    // [12] TObjectPtr, TSubclassOf 심화
    // ==============================================================================
    
    // TObjectPtr: 
    // 언리얼 5부터 기존 C++의 로우 포인터(AActor*)를 완벽하게 대체하는 스마트 포인터입니다.
    // 에디터 빌드에서 이 변수에 접근할 때 타입 안정성을 검사하고, 미사용 객체의 지연 로딩을 지원하여 훨씬 빠르고 안전합니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Study|Pointers", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<AActor> TargetActor;

    // TSubclassOf: 
    // 실제 눈에 보이는 객체(인스턴스)를 담는 것이 아니라, "설계도(클래스 타입) 자체"를 보관하는 특수한 변수입니다.
    // 에디터 디테일 패널에서 아무 클래스나 고를 수 있는 게 아니라, 반드시 <AActor>를 상속받은 자식들만 목록에 뜨도록 강력하게 필터링해 줍니다.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Study|Pointers", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AActor> ActorClassToSpawn;

    // 런타임에 에디터에서 고른 클래스(설계도)를 바탕으로 실제 객체를 스폰하는 테스트 함수
    void TestSpawning();

    // ==============================================================================
    // [예시 문제: TSubclassOf]
    // Q: "AMonster" 라는 C++ 클래스를 상속받아 여러 마리의 블루프린트 몬스터(BP_Orc, BP_Troll 등)를 만들었습니다.
    //    개발자가 에디터 창에서 이 수많은 몬스터 템플릿 중 하나를 '선택'할 수 있는 변수를 만들려고 합니다.
    //    타입란(빈칸)에 들어가야 할 올바른 템플릿 코드는 무엇일까요?
    //    UPROPERTY(EditAnywhere)
    //    [        빈 칸        ] MonsterClassToSpawn;
    // 
    // A: TSubclassOf<AMonster>
    //    해설: 이렇게 하면 디테일 패널에 다른 액터들은 싹 사라지고, 오직 AMonster를 상속받은 
    //         BP_Orc, BP_Troll만 목록에 나타나게 되므로 기획자가 엉뚱한 클래스를 할당하는 휴먼 에러를 방지합니다.
    // ==============================================================================
};
