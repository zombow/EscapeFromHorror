// Fill out your copyright notice in the Description page of Project Settings.


#include "An_PlayerCameraComp.h"

#include "Camera/CameraAnim.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

UAn_PlayerCameraComp::UAn_PlayerCameraComp()
{
	PrimaryComponentTick.bCanEverTick = true;

	//spring arm생성부
	//springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	//springArm->TargetArmLength = 500;

	//카메라 물리충돌 끄기
	//springArm->bDoCollisionTest = false;

	//camera 생성부
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));
	//camera->SetupAttachment(springArm);

	//카메라와 캐릭터간 작용을 구분
	//springArm->bUsePawnControlRotation = true; //springArm이 컨트롤러의 영향을 독립적으로 받음
	camera->bUsePawnControlRotation = false; //카메라는 springArm이 이미 영향을받기에 적용 받지않게끔 off

}


void UAn_PlayerCameraComp::BeginPlay()
{
	Super::BeginPlay();

	me->bUseControllerRotationPitch = false; //Yaw값에 의해 캐릭터가 회전하는것을 차단
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

	//카메라 이동시 clamp값
	FVector cameraMove = FVector(UKismetMathLibrary::Clamp(me->GetActorLocation().X, currntCameraState[0].X, currntCameraState[1].X)
		, UKismetMathLibrary::Clamp(me->GetActorLocation().Y, currntCameraState[0].Y, currntCameraState[1].Y)
		, UKismetMathLibrary::Clamp(me->GetActorLocation().Z, currntCameraState[0].Z, currntCameraState[1].Z)+50);

	//clamp로 뽑아낸값을 Lerp로 이동
	camera->SetWorldLocation(FVector(UKismetMathLibrary::Lerp(camera->GetComponentLocation().X, cameraMove.X, moveSpeed)
	, UKismetMathLibrary::Lerp(camera->GetComponentLocation().Y, cameraMove.Y, moveSpeed)
	, UKismetMathLibrary::Lerp(camera->GetComponentLocation().Z, cameraMove.Z, moveSpeed)));
	

	//카메라 Look lerp이동
	FRotator lookcamera = UKismetMathLibrary::FindLookAtRotation(camera->GetComponentLocation(), me->GetActorLocation());
	camera->SetWorldRotation(FRotator(UKismetMathLibrary::Lerp(camera->GetComponentRotation().Pitch, lookcamera.Pitch, turnSpeed)
	,UKismetMathLibrary::Lerp(camera->GetComponentRotation().Yaw, lookcamera.Yaw, turnSpeed)
	, UKismetMathLibrary::Lerp(camera->GetComponentRotation().Roll, lookcamera.Roll, turnSpeed)));
}
