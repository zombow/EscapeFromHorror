// Fill out your copyright notice in the Description page of Project Settings.


#include "An_PlayerAnim.h"
#include "An_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UAn_PlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto owner = TryGetPawnOwner();
	auto player = Cast<AAn_Player>(owner);
	if (player)
	{
		speedForward = FVector::DotProduct(owner->GetVelocity(), owner->GetActorForwardVector());

		auto movement = player->GetMovementComponent();
		isInAir = movement->IsFalling();
		isCrouch = player->isCrouch;
	}
}

void UAn_PlayerAnim::WalkSoundPlay()
{
	int index = UKismetMathLibrary::RandomIntegerInRange(0, walkSound.Num() - 1);
	UGameplayStatics::PlaySound2D(this, walkSound[index]);
}

void UAn_PlayerAnim::RunSoundPlay()
{

}

