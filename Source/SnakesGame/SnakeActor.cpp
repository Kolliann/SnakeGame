// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeActor.h"
// Sets default values
ASnakeActor::ASnakeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_myRootComponent = CreateDefaultSubobject<USphereComponent>("MyRoot");
	RootComponent = _myRootComponent;

	FVector position = GetActorLocation();
	_myRootComponent->SetRelativeLocation(position);

	CreateSnakeBody();
}

// Called when the game starts or when spawned
void ASnakeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnakeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetVisibleNode();
	_bufferTime += DeltaTime;
	if (_bufferTime > _deley) {
		MoveSnake();
		_bufferTime = 0;
	}
}

void ASnakeActor::CreateSnakeBody()
{
	//Создаем сетку 
	UStaticMesh* snakeMeshObject;
	//Загружаем дефолтный компонент из движка
	snakeMeshObject = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Sphere")).Object;


	//set texture
	UMaterialInstance* bodyMaterial;

	bodyMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/SnakeAsset/Materials/Instance/M_Tech_Hex_Tile_Inst.M_Tech_Hex_Tile_Inst'")).Get();

	UMaterialInstance* headMaterial;

	headMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/SnakeAsset/Materials/Instance/M_Tech_Hex_Tile_Pulse_Inst.M_Tech_Hex_Tile_Pulse_Inst'")).Get();

	//generate coordin snake
	FVector nextPoint = GetActorLocation();

	//name obj
	FName nameNode;
	FString nameFStr;

	for (size_t i = 0; i < _maxSnakeSize; i++)
	{
		nameFStr = "Chank" + FString::FromInt(i);
		nameNode = FName(*nameFStr);

		UStaticMeshComponent* bodyNode = CreateDefaultSubobject<UStaticMeshComponent>(nameNode);
		bodyNode->SetStaticMesh(snakeMeshObject);
		//create body snake
		bodyNode->SetRelativeLocation(nextPoint);

		_snakeBody.Add(bodyNode);
		nextPoint.X -= _stepSnakeBody;
		bodyNode->AttachTo(_myRootComponent);
		bodyNode->SetMaterial(0, bodyMaterial);

		if (i == 0) 
		{
			bodyNode->SetMaterial(0, headMaterial);
		}
		else {
			bodyNode->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		SetVisibleNode();
	}
}

void ASnakeActor::SetVisibleNode()
{
	for (size_t i = 0; i < _snakeBody.Num(); i++) {
		if (i < _startVisibleNode){
			_snakeBody[i]->SetVisibility(true, true);
		}
		else {
			_snakeBody[i]->SetVisibility(false, true);
		}
	}
}

void ASnakeActor::MoveSnake()
{
	if ((_directionMoveSnake.X != 0) || (_directionMoveSnake.Y != 0)) {
		for (size_t node = _snakeBody.Num() - 1; node > 0; node--) {
			FVector newCordinate = _snakeBody[node - 1]->GetRelativeLocation();
			_snakeBody[node]->SetRelativeLocation(newCordinate);
		}

		FVector headLocation = _snakeBody[0]->GetRelativeLocation();

		// <-------
		if (_directionMoveSnake.X > 0) {
			headLocation.X -= _stepSnakeBody;
		}
		// ------->
		if (_directionMoveSnake.X < 0) {
			headLocation.X += _stepSnakeBody;
		}

		// ^
		// |
		if (_directionMoveSnake.Y > 0) {
			headLocation.Y += _stepSnakeBody;
		}

		// |
		// v
		if (_directionMoveSnake.Y < 0) {
			headLocation.Y -= _stepSnakeBody;
		}

		_snakeBody[0]->SetRelativeLocation(headLocation);
	}
}

void ASnakeActor::HaveDamage()
{
	_isNeedDestroyObj = true;
}

void ASnakeActor::SetDirectionMoveSnake(FVector2D position)
{
	_directionMoveSnake = position;
}

void ASnakeActor::AddStartVisibleNode(int32 value)
{
	_startVisibleNode += value;
}

void ASnakeActor::AddScore(int32 value)
{
	_score += value;
}

