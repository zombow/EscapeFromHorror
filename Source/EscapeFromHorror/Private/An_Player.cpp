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
	//spring arm������
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->TargetArmLength = 500;
	springArmComp->SetWorldLocation(FVector(0, 0, 100));
	//ī�޶� �����浹 ����
	springArmComp->bDoCollisionTest = false;

	//camera ������
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));
	cameraComp->SetupAttachment(springArmComp);
	// +ī�޶� ��ġ���� ���� �����ʿ�!
	
	//ī�޶�� ĳ���Ͱ� �ۿ��� ����
	bUseControllerRotationPitch = false; //Yaw���� ���� ĳ���Ͱ� ȸ���ϴ°��� ����
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	springArmComp->bUsePawnControlRotation = true; //springArm�� ��Ʈ�ѷ��� ������ ���������� ����
	cameraComp->bUsePawnControlRotation = false; //ī�޶�� springArm�� �̹� �������ޱ⿡ ���� �����ʰԲ� off

	//mesh �����
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("SkeletalMesh'/Game/An/an_Source/an_player/an_all/LittleNightmareMarine.LittleNightmareMarine'"));

	if (tempMesh.Succeeded()) //mesh�� ���������� �޾����Դ����� üũ
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


