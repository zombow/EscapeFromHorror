// Fill out your copyright notice in the Description page of Project Settings.


#include "An_Player.h"
#include "GameFramework/SpringArmComponent.h"
#include "An_PlayerAnim.h"
#include "An_PlayerCameraComp.h"
#include "An_PlayerMoveComp.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAn_Player::AAn_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	moveComp = CreateDefaultSubobject<UAn_PlayerMoveComp>(TEXT("moveComp"));
	//cameraComp = CreateDefaultSubobject <UAn_PlayerCameraComp>(TEXT("cameraComp"));
	//springArmComp = CreateDefaultSubobject<UAn_PlayerCameraComp>(TEXT("springArmComp"));
	//spring arm생성부
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->TargetArmLength = 500;
	springArmComp->SetWorldLocation(FVector(0, 0, 100));
	//카메라 물리충돌 끄기
	springArmComp->bDoCollisionTest = false;

	//camera 생성부
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));
	cameraComp->SetupAttachment(springArmComp);
	// +카메라 위치설정 추후 수정필요!
	
	//카메라와 캐릭터간 작용을 구분
	bUseControllerRotationPitch = false; //Yaw값에 의해 캐릭터가 회전하는것을 차단
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
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

}

// Called every frame
void AAn_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAn_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	onPlayerInputBindingDelegate.Broadcast(PlayerInputComponent);
}


