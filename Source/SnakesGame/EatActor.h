#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "SnakeActor.h"
#include "EatActor.generated.h"

UCLASS()
class SNAKESGAME_API AEatActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEatActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void CollectEat();

private:
	float _objectLifetime = 15.f;
	float _bufferTime = 0.0f;

	USphereComponent* _myRootComponent;
	UStaticMesh* _eatMeshObject;

};
