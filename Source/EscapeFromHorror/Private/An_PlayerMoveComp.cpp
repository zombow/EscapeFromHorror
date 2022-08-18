// Fill out your copyright notice in the Description page of Project Settings.


#include "An_PlayerMoveComp.h"
#include "An_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UAn_PlayerMoveComp::UAn_PlayerMoveComp()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAn_PlayerMoveComp::BeginPlay()
{
	Super::BeginPlay();
	
	myMovement->MaxWalkSpeed = walkSpeed;
	myMovement->MaxFlySpeed = climbSpeed;
	myMovement->BrakingDecelerationFlying = 500;

}

void UAn_PlayerMoveComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Player이동
	dir = FTransform(me->GetControlRotation()).TransformVector(dir);
	dir.Normalize();

	if (isClimb)
	{
		me->AddMovementInput(climbUp, me->GetInputAxisValue("MoveForward"));//입력키 받기
		InClimb();
	}
	else
	{
		me->AddMovementInput(dir);
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
	if (isClimb)
	{
		FVector climbJump = me->GetActorForwardVector() * -100;
		me->ACharacter::LaunchCharacter(FVector(climbJump.X, climbJump.Y, 0), false, false); //클라이밍중 스페이스바 입력시 플레이어 발사
		OutClimb();
	}
}

void UAn_PlayerMoveComp::OnActionRunPressed()
{
	if (!isCrouch)
	{
		myMovement->MaxWalkSpeed = runSpeed;
	}
}

void UAn_PlayerMoveComp::OnActionRunReleased()
{
	myMovement->MaxWalkSpeed = walkSpeed;
}

void UAn_PlayerMoveComp::OnActionCruchPressed()
{
	myMovement->MaxWalkSpeed = cruchSpeed;
	isCrouch = true;
}

void UAn_PlayerMoveComp::OnActionCruchReleased()
{
	myMovement->MaxWalkSpeed = walkSpeed;
	isCrouch = false;
}

void UAn_PlayerMoveComp::OnActionClimbPressed()
{
	//만약 isClimb가 이미 true라면 (이미 벽을타고 있다면)
	if (isClimb)
	{
		OutClimb();
	}
	else
	{
		//인터렉션키를 눌렀을때 lineTrace 발사
		//LinTracer 구현부-------
		FVector start = me->GetMesh()->GetComponentLocation() + FVector(0, 0, 50);
		FVector end = start + me->GetMesh()->GetRightVector()* 40;

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
		//FString myinfo = hitInfo.GetActor()->GetFName().ToString();
		//UE_LOG(LogTemp, Warning, TEXT("%s"), myinfo);
		
		if (isHit && (hitInfo.GetActor()->GetFName() == "BP_Climble"))
		{
			//isClib를 트루로 변경
			isClimb = true;
			auto climbwallNormal = hitInfo.Normal;
			me->SetActorRotation(FRotator(0, (UKismetMathLibrary::Conv_VectorToRotator(climbwallNormal).Yaw - 180), 0)); //나의 Yaw값을 상대방의 Yaw값과 동일하게 회전
			//나의 movemode를 fly로 바꾸고 벽타는 행동(tick)
			//auto myMovement = me->GetCharacterMovement(); //UCharacterMovementComponent*
			myMovement->Velocity = FVector::ZeroVector; // velocity를 0으로 만들기
			myMovement->SetMovementMode(MOVE_Flying);
			myMovement->bOrientRotationToMovement = false; //캐릭터회전 자동보간 사용여부
			//클라임시 앞으로가는벡터를 윗방향을 바꿔줌
			climbUp = UKismetMathLibrary::GetUpVector(FRotator(0, 0, 0));
			InClimb();
		}
	}

}

void UAn_PlayerMoveComp::OnActionClimbReleased()
{
	//미지정
}

void UAn_PlayerMoveComp::InClimb()
{
	if (!isClimbUp)
	{
		//정상 감지 라인트레이스
		FVector topStart = me->GetMesh()->GetComponentLocation() + FVector(0, 0, 55);
		FVector topEnd = topStart + me->GetMesh()->GetRightVector() * 40;
		DrawDebugLine(GetWorld(), topStart, topEnd, FColor(0, 255, 0), false, -1, 0, 12.33);

		FHitResult hitTopInfo;
		FCollisionQueryParams topParams;
		topParams.AddIgnoredActor(me);
		bool isTop = GetWorld()->LineTraceSingleByChannel(hitTopInfo, topStart, topEnd, ECC_Visibility, topParams);
		if (!isTop)
		{
			myYaw = me->GetActorRotation().Yaw;
			isClimbUp = true;
			isClimb = false;
			PlayClimbUpAnim();
		}
	}
	// 유지 라인트레이스
	FVector start = me->GetMesh()->GetComponentLocation() + FVector(0, 0, 50);
	FVector end = start + me->GetMesh()->GetRightVector() * 40;

	FHitResult hitInfo;
	FCollisionQueryParams params;
	params.AddIgnoredActor(me);
	//bool UWorld::LineTraceSingleByChannel(struct FHitResult& OutHit, const FVector & Start, const FVector & End, ECollisionChannel TraceChannel, const FCollisionQueryParams & Params /* = FCollisionQueryParams::DefaultQueryParam */, const FCollisionResponseParams & ResponseParam /* = FCollisionResponseParams::DefaultResponseParam */) const
	//{
	//	return FPhysicsInterface::RaycastSingle(this, OutHit, Start, End, TraceChannel, Params, ResponseParam, FCollisionObjectQueryParams::DefaultObjectQueryParam);
	//}
	bool isHit = GetWorld()->LineTraceSingleByChannel(hitInfo, start, end, ECC_Visibility, params); //받은 정보값 //원하는 물체만 감지할수 있도록 채널설정 필요!
	DrawDebugLine(GetWorld(), start, end, FColor(255, 0, 0), false, -1, 0, 12.33);
	if (!isHit)
	{
		OutClimb();
	}
}

	//클라임을 끝내고 원래 상태로돌아오기
void UAn_PlayerMoveComp::OutClimb()
{
	//isClimb를 false로바꾸고 
	isClimb = false;
	//movemode를 walk로 변경
	myMovement->SetMovementMode(MOVE_Walking);
	myMovement->bOrientRotationToMovement = true;
}

void UAn_PlayerMoveComp::PlayClimbUpAnim()
{
	int delaytime = me->ACharacter::PlayAnimMontage(climUpAnimMontage);
	FTimerHandle WaitHandle;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			isClimbUp = false;
			me->SetActorRotation(FRotator(0, myYaw, 0));
			OutClimb();
		}), delaytime, false);
}





