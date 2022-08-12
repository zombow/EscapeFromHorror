// Fill out your copyright notice in the Description page of Project Settings.


#include "An_PlayerMoveComp.h"
#include "An_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

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
	if (isClimb)
	{
		//클라임시 앞으로가는벡터를 윗방향을 바꿔줌
	}

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
		UE_LOG(LogTemp, Warning, TEXT("Un Line"));
		auto myMovestate = me->GetCharacterMovement(); //UCharacterMovementComponent*
		me->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
	else
	{
		//인터렉션키를 눌렀을때 lineTrace 발사
		//LinTracer 구현부-------
		FVector start = me->GetMesh()->GetComponentLocation() + FVector(0, 0, 50);
		FVector end = start + me->GetMesh()->GetRightVector()* 50;

		FHitResult hitInfo;
		FCollisionQueryParams params;
		params.AddIgnoredActor(me);
		//bool UWorld::LineTraceSingleByChannel(struct FHitResult& OutHit, const FVector & Start, const FVector & End, ECollisionChannel TraceChannel, const FCollisionQueryParams & Params /* = FCollisionQueryParams::DefaultQueryParam */, const FCollisionResponseParams & ResponseParam /* = FCollisionResponseParams::DefaultResponseParam */) const
		//{
		//	return FPhysicsInterface::RaycastSingle(this, OutHit, Start, End, TraceChannel, Params, ResponseParam, FCollisionObjectQueryParams::DefaultObjectQueryParam);
		//}
		bool isHit = GetWorld()->LineTraceSingleByChannel(hitInfo, start, end, ECC_Visibility, params); //받은 정보값 //원하는 물체만 감지할수 있도록 채널설정 필요!
		DrawDebugLine(GetWorld(), start, end, FColor(255, 0, 0), false, -1, 0, 12.33);
		//LinTracer 구현부 끝-------
		//앞에 타고올라갈수 있는 벽이있다면
		if (isHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("get line"));
			
			//isClib를 트루로 변경
			isClimb = true;
			auto climbwallNormal = hitInfo.Normal;
			me->SetActorRotation(FRotator(0, (UKismetMathLibrary::Conv_VectorToRotator(climbwallNormal).Yaw -180), 0)); //나의 Yaw값을 상대방의 Yaw값과 동일하게 회전
			//나의 movemode를 fly로 바꾸고 벽타는 행동(tick)
			auto myMovestate = me->GetCharacterMovement(); //UCharacterMovementComponent*
			myMovestate->SetMovementMode(MOVE_Flying);
		}
		
	}

}

void UAn_PlayerMoveComp::OnActionClimbReleased()
{
	//미지정
}
