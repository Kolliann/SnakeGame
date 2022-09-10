#include "EatActor.h"

// Sets default values
AEatActor::AEatActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_myRootComponent = CreateDefaultSubobject<USphereComponent>("EatRoot");
	RootComponent = _myRootComponent;

	_eatMeshObject = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Sphere")).Object;

	UMaterialInstance* eatMaterialColor;
	eatMaterialColor = ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/SnakeAsset/Materials/Instance/M_Metal_Gold_Inst.M_Metal_Gold_Inst'")).Get();


	FVector size = FVector(0.5f, 0.5f, 0.5f);

	UStaticMeshComponent* eatObjectNode = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Eat"));
	eatObjectNode->SetStaticMesh(_eatMeshObject);
	eatObjectNode->SetRelativeScale3D(size);
	eatObjectNode->SetRelativeLocation(FVector(0, 0, 0));
	eatObjectNode->SetMaterial(0, eatMaterialColor);
	eatObjectNode->AttachTo(_myRootComponent);
	eatObjectNode->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AEatActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEatActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	_bufferTime += DeltaTime;
	if (_bufferTime > _objectLifetime) {
		Destroy(true, true);
	}
	CollectEat();

}

void AEatActor::CollectEat()
{
	TArray<AActor*> collectedCollideActors;
	GetOverlappingActors(collectedCollideActors);
	for (size_t i = 0; i < collectedCollideActors.Num(); ++i) {
		ASnakeActor* const castItem = Cast<ASnakeActor>(collectedCollideActors[i]);

		if (castItem)
		{
			castItem->AddStartVisibleNode(1);
			castItem->AddScore(1);
			Destroy(true, true);
			break;
		}
	}
}

