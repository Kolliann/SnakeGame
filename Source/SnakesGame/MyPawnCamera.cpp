#include "MyPawnCamera.h"
#include "EatActor.h"

// Sets default values
AMyPawnCamera::AMyPawnCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_myRootComponent = CreateDefaultSubobject<UBoxComponent>("RootModel");

	RootComponent = _myRootComponent;

	_cameraSpring = CreateDefaultSubobject<USpringArmComponent>("Spring");

	_cameraSpring->SetRelativeLocation(FVector(0, 0, 0));

	_cameraSpring->AttachTo(_myRootComponent);

	_myCamera = CreateDefaultSubobject<UCameraComponent>("Camera");

	_myCamera->AttachTo(_cameraSpring, USpringArmComponent::SocketName);

	_cameraSpring->SetRelativeRotation(FRotator(-90.f, 0, 0));
	_cameraSpring->TargetArmLength = 1700.f;
	_cameraSpring->bDoCollisionTest = false;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void AMyPawnCamera::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPawnCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_snakeActor && _snakeActor->IsNeedDestroyObj()) {
		_gameMode = 0;
		_snakeActor->Destroy(true, true);
	}

	if (_gameMode > 0) {
		_bufferTime += DeltaTime;
		if (_bufferTime > _deley) {
			if (!_isGameStatePause) {

				CreateEatByMap();
			}
			_bufferTime = 0;
		}
	}
}

// Called to bind functionality to input
void AMyPawnCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("SnakeMove", this, &AMyPawnCamera::FMove);

}

void AMyPawnCamera::CreateSnakeToMap()
{
	//actor location
	FVector startPoint = GetActorLocation();
	FRotator startPointRotation = GetActorRotation();

	if (GetWorld()) {
		_snakeActor = GetWorld()->SpawnActor<ASnakeActor>(startPoint, startPointRotation);
		_gameMode = 1;
	}
}

void AMyPawnCamera::FMove(float buttonVal)
{
	int32 key = buttonVal;
	if (_gameMode > 0) {
		if (key == 5) {
			_isGameStatePause = !_isGameStatePause;
		}

		if (!_isGameStatePause) {
			switch (key)
			{

			case 1: // w
				if (_keyboard.X != 1) {
					_keyboard = FVector2D(0, 0);
					_keyboard.X = -1;
				}
				break;

			case 2: // s
				if (_keyboard.X != -1) {
					_keyboard = FVector2D(0, 0);
					_keyboard.X = 1;
				}
				break;

			case 3: // d
				if (_keyboard.Y != -1) {
					_keyboard = FVector2D(0, 0);
					_keyboard.Y = 1;
				}
				break;

			case 4: // a
				if (_keyboard.Y != 1) {
					_keyboard = FVector2D(0, 0);
					_keyboard.Y = -1;
				}
				break;
			}

			if (_snakeActor) {
				_snakeActor->SetDirectionMoveSnake(_keyboard);
			}
		}
		else {
			_snakeActor->SetDirectionMoveSnake(FVector2D(0, 0));
		}
	}
}

int32 AMyPawnCamera::GetScore()
{
	if (_snakeActor) {
		return _snakeActor->GetScore();
	}
	return 0;
}

void AMyPawnCamera::CreateEatByMap()
{
	FRotator startPointRotation = FRotator(0, 0, 0);
	float spawnX = FMath::FRandRange(_minX, _maxX);
	float spawnY = FMath::FRandRange(_minY, _maxY);
	FVector starpPoint = FVector(spawnX, spawnY, _spawnHeightZ);

	if (_snakeActor) {
		if (GetWorld()) {
			GetWorld()->SpawnActor<AEatActor>(starpPoint, startPointRotation);
		}
	}
}