#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SnakeActor.h"
#include "MyPawnCamera.generated.h"

UCLASS()
class SNAKESGAME_API AMyPawnCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawnCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void FMove(float);
	void CreateEatByMap();

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void CreateSnakeToMap();
	UFUNCTION(BlueprintCallable, Category = "GameMode")
	int32 GetGameMode() const { return _gameMode; }
	UFUNCTION(BlueprintCallable, Category = "GameMode")
	int32 GetScore();
	UFUNCTION(BlueprintCallable, Category = "GameMode")
	int32 GetGamePause() const { return _isGameStatePause; }
	
private:
	UPROPERTY(EditAnywhere) UBoxComponent* _myRootComponent;

	UPROPERTY(EditAnywhere) USpringArmComponent* _cameraSpring;

	UPROPERTY(EditAnywhere) UCameraComponent* _myCamera;

	ASnakeActor* _snakeActor;

	FVector2D _keyboard;
	// size plane
	float _minX = -800.f;
	float _maxX = 800.f;
	float _minY = -1500.f;
	float _maxY = 1500.f;
	//spawn fly
	float _spawnHeightZ = 50.f;

	float _deley = 1.5f;
	float _bufferTime = 0;

	/* в этой версии нелзя в блюпринте
	 виджета использовать enum поэтому так*/
	int32 _gameMode = 0;

	bool _isGameStatePause = false;
};
