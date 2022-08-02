// Fill out your copyright notice in the Description page of Project Settings.


#include "An_Player.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAn_Player::AAn_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//spring arm생성부
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->TargetArmLength = 500;
	springArmComp->SetWorldLocation(FVector(0, 0, 100));

	//camera 생성부
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));
	cameraComp->SetupAttachment(springArmComp);
	// +카메라 위치설정 추후 수정필요!
	
	//카메라와 캐릭터간 작용을 구분
	bUseControllerRotationYaw = false; //Yaw값에 의해 캐릭터가 회전하는것을 차단
	springArmComp->bUsePawnControlRotation = true; //springArm이 컨트롤러의 영향을 독립적으로 받음
	cameraComp->bUsePawnControlRotation = false; //카메라는 springArm이 이미 영향을받기에 적용 받지않게끔 off

	//mesh 적용부
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("SkeletalMesh'/Game/An/an_Source/an_player/an_all/LittleNightmareMarine.LittleNightmareMarine'"));

	if (tempMesh.Succeeded()) //mesh가 성공적으로 받아져왔는지를 체크
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

}

// Called when the game starts or when spawned
void AAn_Player::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;

}

// Called every frame
void AAn_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Player이동
	dir = FTransform(GetControlRotation()).TransformVector(dir);
	dir.Normalize();

	AddMovementInput(dir);

	dir = FVector::ZeroVector;
}

// Called to bind functionality to input
void AAn_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AAn_Player::OnAxisMoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AAn_Player::OnAxisMoveRight);
	PlayerInputComponent->BindAction(TEXT("JUMP"), IE_Pressed, this, &AAn_Player::OnActionJump);
	PlayerInputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &AAn_Player::OnActionRunPressed);
	PlayerInputComponent->BindAction(TEXT("Run"), IE_Released, this, &AAn_Player::OnActionRunReleased);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AAn_Player::OnActionCruchPressed);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &AAn_Player::OnActionCruchReleased);
}

void AAn_Player::OnAxisMoveForward(float value)
{
	dir.X = value;
}

void AAn_Player::OnAxisMoveRight(float value)
{
	dir.Y = value;
}

void AAn_Player::OnActionJump()
{
	ACharacter::Jump();
}

void AAn_Player::OnActionRunPressed()
{
	if (!isCrouch)
	{
		GetCharacterMovement()->MaxWalkSpeed = runSpeed;
	}
}

void AAn_Player::OnActionRunReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

void AAn_Player::OnActionCruchPressed()
{
	GetCharacterMovement()->MaxWalkSpeed = CruchSpeed;
	isCrouch = true;
}

void AAn_Player::OnActionCruchReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	isCrouch = false;
}

