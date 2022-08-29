// Fill out your copyright notice in the Description page of Project Settings.


#include "An_PlayerCameraComp.h"

#include "Camera/CameraAnim.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

UAn_PlayerCameraComp::UAn_PlayerCameraComp()
{
	PrimaryComponentTick.bCanEverTick = true;

	//spring arm������
	//springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	//springArm->TargetArmLength = 500;

	//ī�޶� �����浹 ����
	//springArm->bDoCollisionTest = false;

	//camera ������
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));
	//camera->SetupAttachment(springArm);

	//ī�޶�� ĳ���Ͱ� �ۿ��� ����
	//springArm->bUsePawnControlRotation = true; //springArm�� ��Ʈ�ѷ��� ������ ���������� ����
	camera->bUsePawnControlRotation = false; //ī�޶�� springArm�� �̹� �������ޱ⿡ ���� �����ʰԲ� off

}


void UAn_PlayerCameraComp::BeginPlay()
{
	Super::BeginPlay();

	me->bUseControllerRotationPitch = false; //Yaw���� ���� ĳ���Ͱ� ȸ���ϴ°��� ����
	me->bUseControllerRotationYaw = false;
	me->bUseControllerRotationRoll = false;

	cameraState = EcameraState::stage1;
}

void UAn_PlayerCameraComp::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch(cameraState)
	{
	case EcameraState::stage1:
		currntCameraState = cameraPositions_1;
		break;
	case EcameraState::stage2:
		currntCameraState = cameraPositions_2;
		break;
	case EcameraState::stage3:
		currntCameraState = cameraPositions_3;
		break;
	default:
		break;
	}

	//ī�޶� �̵��� clamp��
	FVector cameraMove = FVector(UKismetMathLibrary::Clamp(me->GetActorLocation().X, currntCameraState[0].X, currntCameraState[1].X)
		, UKismetMathLibrary::Clamp(me->GetActorLocation().Y, currntCameraState[0].Y, currntCameraState[1].Y)
		, UKismetMathLibrary::Clamp(me->GetActorLocation().Z, currntCameraState[0].Z, currntCameraState[1].Z)+50);

	//clamp�� �̾Ƴ����� Lerp�� �̵�
	camera->SetWorldLocation(FVector(UKismetMathLibrary::Lerp(camera->GetComponentLocation().X, cameraMove.X, moveSpeed)
	, UKismetMathLibrary::Lerp(camera->GetComponentLocation().Y, cameraMove.Y, moveSpeed)
	, UKismetMathLibrary::Lerp(camera->GetComponentLocation().Z, cameraMove.Z, moveSpeed)));
	

	//ī�޶� Look lerp�̵�
	FRotator lookcamera = UKismetMathLibrary::FindLookAtRotation(camera->GetComponentLocation(), me->GetActorLocation());
	camera->SetWorldRotation(FRotator(UKismetMathLibrary::Lerp(camera->GetComponentRotation().Pitch, lookcamera.Pitch, turnSpeed)
	,UKismetMathLibrary::Lerp(camera->GetComponentRotation().Yaw, lookcamera.Yaw, turnSpeed)
	, UKismetMathLibrary::Lerp(camera->GetComponentRotation().Roll, lookcamera.Roll, turnSpeed)));
}
