// Fill out your copyright notice in the Description page of Project Settings.


#include "An_PlayerMoveComp.h"
#include "An_Player.h"
#include "GameFramework/CharacterMovementComponent.h"

UAn_PlayerMoveComp::UAn_PlayerMoveComp()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAn_PlayerMoveComp::BeginPlay()
{
	Super::BeginPlay();
	
	me->GetCharacterMovement()->MaxWalkSpeed = walkSpeed;

}

void UAn_PlayerMoveComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Player이동
	dir = FTransform(me->GetControlRotation()).TransformVector(dir);
	dir.Normalize();

	me->AddMovementInput(dir);

	dir = FVector::ZeroVector;
}

void UAn_PlayerMoveComp::PlayerInputBinding(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &UAn_PlayerMoveComp::OnAxisMoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &UAn_PlayerMoveComp::OnAxisMoveRight);

	PlayerInputComponent->BindAction(TEXT("JUMP"), IE_Pressed, this, &UAn_PlayerMoveComp::OnActionJump);

	PlayerInputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &UAn_PlayerMoveComp::OnActionRunPressed);
	PlayerInputComponent->BindAction(TEXT("Run"), IE_Released, this, &UAn_PlayerMoveComp::OnActionRunReleased);

	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &UAn_PlayerMoveComp::OnActionCruchPressed);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &UAn_PlayerMoveComp::OnActionCruchReleased);

	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Released, this, & UAn_PlayerMoveComp::OnActionClimbPressed);
}


void UAn_PlayerMoveComp::OnAxisMoveForward(float value)
{
	dir.X = value;
}

void UAn_PlayerMoveComp::OnAxisMoveRight(float value)
{
	dir.Y = value;
}

void UAn_PlayerMoveComp::OnActionJump()
{
	me->ACharacter::Jump();
}

void UAn_PlayerMoveComp::OnActionRunPressed()
{
	if (!isCrouch)
	{
		me->GetCharacterMovement()->MaxWalkSpeed = runSpeed;
	}
}

void UAn_PlayerMoveComp::OnActionRunReleased()
{
	me->GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

void UAn_PlayerMoveComp::OnActionCruchPressed()
{
	me->GetCharacterMovement()->MaxWalkSpeed = CruchSpeed;
	isCrouch = true;
}

void UAn_PlayerMoveComp::OnActionCruchReleased()
{
	me->GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	isCrouch = false;
}

void UAn_PlayerMoveComp::OnActionClimbPressed()
{
	//만약 isClimb가 이미 true라면 (이미 벽을타고 있다면)
	if (isClimb)
	{
		//isClimb를 false로바꾸고 
		isClimb = false;
		//movemode를 walk로 변경
	}
	else
	{
		//인터렉션키를 눌렀을때 lineTrace 발사
		//앞에 타고올라갈수 있는 벽이있다면
		//isClib를 트루로 변경
		isClimb = true;
		
		//나의 movemode를 fly로 바꾸고 벽타는 행동
	}

}

void UAn_PlayerMoveComp::OnActionClimbReleased()
{
	//미지정
}
