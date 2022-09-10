// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
//#include "MyPawnCamera.h"
#include "SnakeActor.generated.h"

UCLASS()
class SNAKESGAME_API ASnakeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateSnakeBody();
	void SetVisibleNode();
	void MoveSnake();
	void HaveDamage();

	int32 GetStartVisibleNode() const { return _startVisibleNode; }
	int32 GetScore() const { return _score; }
	bool IsNeedDestroyObj() const { return _isNeedDestroyObj; }

	void SetDirectionMoveSnake(FVector2D);
	void AddStartVisibleNode(int32);
	void AddScore(int32);
private:
	//максамальная длина тела (нельзя проперти size_t)
	UPROPERTY(EditAnywhere)
    int32 _startVisibleNode = 3;

	UPROPERTY(EditAnywhere)
	FVector2D _directionMoveSnake;

	//максамальная длина тела 
	size_t _maxSnakeSize = 40;
	
	//отклонение компонентов тела змеи
	float _stepSnakeBody = 45.f;

	TArray<UStaticMeshComponent*> _snakeBody;

	USphereComponent* _myRootComponent;


	float _deley = 0.2f;
	float _bufferTime = 0;

	int32 _score = 0;
	bool _isNeedDestroyObj = false;

};
