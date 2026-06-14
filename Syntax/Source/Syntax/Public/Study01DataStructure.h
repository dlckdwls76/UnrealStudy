#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Study01DataStructure.generated.h"

UCLASS()
class SYNTAX_API AStudy01DataStructure : public AActor
{
    GENERATED_BODY()
    
public:    
    AStudy01DataStructure();

protected:
    virtual void BeginPlay() override;

private:
    // ==============================================================================
    // [1] TArray (동적 배열)
    // ==============================================================================
    // 특징: 가장 흔하게 쓰이는 자료구조입니다. 데이터가 순서대로 나열되며, 인덱스를 통해 빠르게 접근 가능합니다.
    // 에디터 작용: UPROPERTY를 붙이면 디테일 패널에서 '+' 버튼을 눌러 배열의 길이를 늘리고 값을 셋팅할 수 있습니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Study|DataStructure", meta = (AllowPrivateAccess = "true"))
    TArray<FString> InventoryArray;

    // ==============================================================================
    // [2] TSet (집합)
    // ==============================================================================
    // 특징: 중복된 값을 허용하지 않고 순서가 없는 자료구조입니다. 내부적으로 해시(Hash)를 사용하여 데이터 검색(Contains)이 매우 빠릅니다.
    // 에디터 작용: 블루프린트에서 고유한 항목 리스트(예: 이미 열어본 보물상자 ID, 달성한 업적 등 중복되면 안 되는 리스트)를 제어할 때 유용합니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Study|DataStructure", meta = (AllowPrivateAccess = "true"))
    TSet<int32> UniqueItemIDs;

    // ==============================================================================
    // [3] TMap (딕셔너리 / 맵)
    // ==============================================================================
    // 특징: 키(Key)와 값(Value)의 쌍으로 이루어집니다. 어떤 고유한 키(단어, ID)를 던지면 그에 연결된 값을 즉시 찾아옵니다.
    // 에디터 작용: 디테일 패널에 Key와 Value를 각각 입력하는 두 칸이 세트로 생성됩니다. 아이템 이름별 가격표, ID별 몬스터 타입 등 매핑 테이블을 짤 때 사용합니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Study|DataStructure", meta = (AllowPrivateAccess = "true"))
    TMap<FString, int32> ItemPrices;


    // 자료구조들을 어떻게 사용하는지 C++로 보여주는 테스트 함수입니다.
    void RunDataStructureTest();
};
