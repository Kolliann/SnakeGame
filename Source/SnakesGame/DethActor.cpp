#include "DethActor.h"
#include "SnakeActor.h"

// Sets default values
ADethActor::ADethActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_rootComponent = CreateDefaultSubobject<UBoxComponent>("DeadRoot");
	RootComponent = _rootComponent;

	UStaticMesh* deadMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Cube")).Object;

	_objectMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/SnakeAsset/Materials/Instance/Stop_material_Inst.Stop_material_Inst'")).Get();
	
	UStaticMeshComponent* eatChank = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall"));
	eatChank->SetStaticMesh(deadMesh);
	eatChank->SetRelativeLocation(FVector(0, 0, 0));
	eatChank->SetMaterial(0, _objectMaterial);
	eatChank->AttachTo(_rootComponent);

}

// Called when the game starts or when spawned
void ADethActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADethActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Collide();
}

void ADethActor::Collide()
{
	TArray<AActor*> collectedCollideActors;
	GetOverlappingActors(collectedCollideActors);
	for (size_t i = 0; i < collectedCollideActors.Num(); ++i) {
		ASnakeActor* const castItem = Cast<ASnakeActor>(collectedCollideActors[i]);
		if (castItem) {
			castItem->HaveDamage();
		}
		else {
			collectedCollideActors[i]->Destroy(true, true);
		}	
	}
}

