// Fill out your copyright notice in the Description page of Project Settings.


#include "An_PlayerAnim.h"
#include "An_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "An_PlayerMoveComp.h"

void UAn_PlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto owner = TryGetPawnOwner();
	auto player = Cast<AAn_Player>(owner);
	if (player)
	{
		speedForward = FVector::DotProduct(owner->GetVelocity(), owner->GetActorForwardVector()); // �̵� �ִϸ��̼� ��������� forward ��
		speedUp = FVector::DotProduct(owner->GetVelocity(), owner->GetActorUpVector()); // climb�ִϸ��̼��� ���� Up��

		auto movement = player->GetMovementComponent();
		isInAir = movement->IsFalling();
		auto myMoveComp = Cast<UAn_PlayerMoveComp>(player->moveComp);
		isCrouch = myMoveComp->UAn_PlayerMoveComp::isCrouch;
		isClimb = myMoveComp->UAn_PlayerMoveComp::isClimb;
	};

}

void UAn_PlayerAnim::WalkSoundPlay()
{
	UGameplayStatics::PlaySound2D(this, walkSound);
}

void UAn_PlayerAnim::RunSoundPlay()
{
	UGameplayStatics::PlaySound2D(this, runSound);
}

void UAn_PlayerAnim::CrouchSoundPlay()
{
	UGameplayStatics::PlaySound2D(this, crouchSound);
}

void UAn_PlayerAnim::JumpSoundPlay()
{
	UGameplayStatics::PlaySound2D(this, jumpSound);
}

void UAn_PlayerAnim::RandSoundPlay()
{
	UGameplayStatics::PlaySound2D(this, randSound);
}




