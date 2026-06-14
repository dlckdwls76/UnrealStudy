#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Study03Reflection.generated.h"

// ----------------------------------------------------
// 1. 열거형(Enum) 리플렉션
// ----------------------------------------------------
// 일반 C++ enum은 블루프린트에서 쓸 수 없지만, UENUM(BlueprintType)을 붙이면
// 언리얼 리플렉션 시스템이 인식하여 에디터의 드롭다운 메뉴로 사용할 수 있게 됩니다.
// 메모리 최적화를 위해 (uint8)을 기반으로 작성하는 것이 국룰입니다.
UENUM(BlueprintType)
enum class EStudyItemType : uint8
{
    Weapon      UMETA(DisplayName = "무기"),
    Armor       UMETA(DisplayName = "방어구"),
    Consumable  UMETA(DisplayName = "소비재")
};

// ----------------------------------------------------
// 2. 구조체(Struct) 리플렉션
// ----------------------------------------------------
// 구조체 역시 USTRUCT(BlueprintType)를 붙이고 내부에 GENERATED_BODY()를 넣으면 
// UPROPERTY() 변수들을 블루프린트에 노출할 수 있는 리플렉션 객체가 됩니다.
// 가벼운 데이터 묶음(인벤토리 슬롯 정보, 스탯 등)을 만들 때 클래스 대신 매우 자주 사용합니다.
USTRUCT(BlueprintType)
struct FStudyItemData
{
    GENERATED_BODY()

    // FName: 내부적으로 문자열을 해시(Hash) 숫자로 변환해 저장합니다. 
    // 문자열 '비교'가 압도적으로 빠르기 때문에 데이터 테이블의 Key나 에셋 식별자(이름표)로 쓰입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FName ItemID; 

    // FString: 동적으로 길이가 늘어나고 자유롭게 변형 가능한 일반적인 문자열입니다. (가장 무거움)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString ItemDescription; 

    // FText: 다국어 번역(Localization)을 완벽히 지원하는 언리얼 전용 텍스트 포맷입니다. UI에 띄울 글자는 무조건 FText를 써야 합니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText DisplayName; 
};


UCLASS()
class SYNTAX_API AStudy03Reflection : public AActor
{
    GENERATED_BODY() 
    
public:    
    AStudy03Reflection();

private:
    // ==============================================================================
    // [3] 리플렉션 시스템 심화 (가비지 컬렉션과 타입)
    // ==============================================================================

    // 객체 포인터는 반드시 UPROPERTY를 붙여야 가비지 컬렉터(GC)에 의해 보호됩니다. (이전 시간 복습)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Study|Reflection", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<AActor> SafeActorPtr;

    // 리플렉션이 적용된 위쪽의 Enum 변수
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Study|Reflection", meta = (AllowPrivateAccess = "true"))
    EStudyItemType MyItemType;

    // 리플렉션이 적용된 위쪽의 Struct 변수
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Study|Reflection", meta = (AllowPrivateAccess = "true"))
    FStudyItemData MyItemData;

    // ==============================================================================
    // [예시 문제 2: 구조체와 클래스의 가비지 컬렉션 차이]
    // Q: 데이터 관리를 위해 클래스(UCLASS) 대신 구조체(USTRUCT)를 선언했습니다. 
    //    이 구조체를 TArray<FStudyItemData> 형태로 1만 개 생성했습니다.
    //    이 구조체 객체들은 가비지 컬렉터(GC)의 메모리 관리 대상이 될까요?
    // 
    // A: 대상이 되지 않습니다.
    //    이유: 언리얼의 가비지 컬렉션(GC)은 오직 'UObject'를 상속받은 클래스 객체(UCLASS)만 
    //         추적하고 메모리를 해제합니다. 구조체(USTRUCT)는 값(Value) 타입이므로 
    //         일반 C++ 규칙을 따릅니다. 즉, 포함된 블록(스코프)이나 배열이 지워질 때 
    //         운영체제가 자동으로 즉시 파기해버립니다.
    //         (그래서 구조체가 클래스보다 메모리 할당/해제 오버헤드가 적고 훨씬 빠릅니다!)
    // ==============================================================================
};
