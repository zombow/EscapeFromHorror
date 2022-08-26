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
	// +ī�޶� ��ġ���� ���� �����ʿ�!
	camera->SetWorldLocation(FVector(-200, 0, 100));

	//ī�޶�� ĳ���Ͱ� �ۿ��� ����
	//springArm->bUsePawnControlRotation = true; //springArm�� ��Ʈ�ѷ��� ������ ���������� ����
	//camera->bUsePawnControlRotation = false; //ī�޶�� springArm�� �̹� �������ޱ⿡ ���� �����ʰԲ� off

}

void UAn_PlayerCameraComp::BeginPlay()
{
	Super::BeginPlay();


	me->bUseControllerRotationPitch = false; //Yaw���� ���� ĳ���Ͱ� ȸ���ϴ°��� ����
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
