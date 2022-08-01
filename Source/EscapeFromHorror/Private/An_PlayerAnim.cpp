// Fill out your copyright notice in the Description page of Project Settings.


#include "An_PlayerAnim.h"

void UAn_PlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto owner = TryGetPawnOwner();
	if (nullptr != owner)
	{
		speedForward = FVector::DotProduct(owner->GetVelocity(), owner->GetActorForwardVector());

	}
}
