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
	//Player�̵�
	dir = FTransform(me->GetControlRotation()).TransformVector(dir);
	dir.Normalize();

	if (isClimb)
	{
		me->AddMovementInput(climbUp, me->GetInputAxisValue("MoveForward"));//�Է�Ű �ޱ�
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
		me->ACharacter::LaunchCharacter(FVector(climbJump.X, climbJump.Y, 0), false, false); //Ŭ���̹��� �����̽��� �Է½� �÷��̾� �߻�
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
	//���� isClimb�� �̹� true��� (�̹� ����Ÿ�� �ִٸ�)
	if (isClimb)
	{
		OutClimb();
	}
	else
	{
		//���ͷ���Ű�� �������� lineTrace �߻�
		//LinTracer ������-------
		FVector start = me->GetMesh()->GetComponentLocation() + FVector(0, 0, 50);
		FVector end = start + me->GetMesh()->GetRightVector()* 40;

		FHitResult hitInfo;
		FCollisionQueryParams params;
		params.AddIgnoredActor(me);
		//bool UWorld::LineTraceSingleByChannel(struct FHitResult& OutHit, const FVector & Start, const FVector & End, ECollisionChannel TraceChannel, const FCollisionQueryParams & Params /* = FCollisionQueryParams::DefaultQueryParam */, const FCollisionResponseParams & ResponseParam /* = FCollisionResponseParams::DefaultResponseParam */) const
		//{
		//	return FPhysicsInterface::RaycastSingle(this, OutHit, Start, End, TraceChannel, Params, ResponseParam, FCollisionObjectQueryParams::DefaultObjectQueryParam);
		//}
		bool isHit = GetWorld()->LineTraceSingleByChannel(hitInfo, start, end, ECC_Visibility, params); //���� ������ //���ϴ� ��ü�� �����Ҽ� �ֵ��� ä�μ��� �ʿ�!
		DrawDebugLine(GetWorld(), start, end, FColor(255, 0, 0), false, -1, 0, 12.33);
		//LinTracer ������ ��-------
		//�տ� Ÿ��ö󰥼� �ִ� �����ִٸ�
		//FString myinfo = hitInfo.GetActor()->GetFName().ToString();
		//UE_LOG(LogTemp, Warning, TEXT("%s"), myinfo);
		
		if (isHit && (hitInfo.GetActor()->GetFName() == "BP_Climble"))
		{
			//isClib�� Ʈ��� ����
			isClimb = true;
			auto climbwallNormal = hitInfo.Normal;
			me->SetActorRotation(FRotator(0, (UKismetMathLibrary::Conv_VectorToRotator(climbwallNormal).Yaw - 180), 0)); //���� Yaw���� ������ Yaw���� �����ϰ� ȸ��
			//���� movemode�� fly�� �ٲٰ� ��Ÿ�� �ൿ(tick)
			//auto myMovement = me->GetCharacterMovement(); //UCharacterMovementComponent*
			myMovement->Velocity = FVector::ZeroVector; // velocity�� 0���� �����
			myMovement->SetMovementMode(MOVE_Flying);
			myMovement->bOrientRotationToMovement = false; //ĳ����ȸ�� �ڵ����� ��뿩��
			//Ŭ���ӽ� �����ΰ��º��͸� �������� �ٲ���
			climbUp = UKismetMathLibrary::GetUpVector(FRotator(0, 0, 0));
			InClimb();
		}
	}

}

void UAn_PlayerMoveComp::OnActionClimbReleased()
{
	//������
}

void UAn_PlayerMoveComp::InClimb()
{
	if (!isClimbUp)
	{
		//���� ���� ����Ʈ���̽�
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
	// ���� ����Ʈ���̽�
	FVector start = me->GetMesh()->GetComponentLocation() + FVector(0, 0, 50);
	FVector end = start + me->GetMesh()->GetRightVector() * 40;

	FHitResult hitInfo;
	FCollisionQueryParams params;
	params.AddIgnoredActor(me);
	//bool UWorld::LineTraceSingleByChannel(struct FHitResult& OutHit, const FVector & Start, const FVector & End, ECollisionChannel TraceChannel, const FCollisionQueryParams & Params /* = FCollisionQueryParams::DefaultQueryParam */, const FCollisionResponseParams & ResponseParam /* = FCollisionResponseParams::DefaultResponseParam */) const
	//{
	//	return FPhysicsInterface::RaycastSingle(this, OutHit, Start, End, TraceChannel, Params, ResponseParam, FCollisionObjectQueryParams::DefaultObjectQueryParam);
	//}
	bool isHit = GetWorld()->LineTraceSingleByChannel(hitInfo, start, end, ECC_Visibility, params); //���� ������ //���ϴ� ��ü�� �����Ҽ� �ֵ��� ä�μ��� �ʿ�!
	DrawDebugLine(GetWorld(), start, end, FColor(255, 0, 0), false, -1, 0, 12.33);
	if (!isHit)
	{
		OutClimb();
	}
}

	//Ŭ������ ������ ���� ���·ε��ƿ���
void UAn_PlayerMoveComp::OutClimb()
{
	//isClimb�� false�ιٲٰ� 
	isClimb = false;
	//movemode�� walk�� ����
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





