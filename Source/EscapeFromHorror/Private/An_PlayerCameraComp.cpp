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
	// +카메라 위치설정 추후 수정필요!
	camera->SetWorldLocation(FVector(-200, 0, 100));

	//카메라와 캐릭터간 작용을 구분
	//springArm->bUsePawnControlRotation = true; //springArm이 컨트롤러의 영향을 독립적으로 받음
	//camera->bUsePawnControlRotation = false; //카메라는 springArm이 이미 영향을받기에 적용 받지않게끔 off

}

void UAn_PlayerCameraComp::BeginPlay()
{
	Super::BeginPlay();


	me->bUseControllerRotationPitch = false; //Yaw값에 의해 캐릭터가 회전하는것을 차단
	me->bUseControllerRotationYaw = false;
	me->bUseControllerRotationRoll = false;
}

void UAn_PlayerCameraComp::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	UE_LOG(LogTemp, Warning, TEXT("TEQ"));
	//springArm->SetRelativeLocation(me->GetActorLocation());
	//UKismetMathLibrary::FindLookAtRotation(springArm->GetRelativeLocation(), me->GetActorLocation());
}
