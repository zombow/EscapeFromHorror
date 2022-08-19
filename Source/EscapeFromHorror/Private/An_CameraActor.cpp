// Fill out your copyright notice in the Description page of Project Settings.


#include "An_CameraActor.h"

#include "Kismet/KismetMathLibrary.h"

void AAn_CameraActor::BeginPlay()
{
	Super::BeginPlay();
	me = GetOwner();
	player = Cast<AAn_Player>(GetWorld()->GetFirstPlayerController()->GetOwner());

	//UKismetMathLibrary::FindLookAtRotation(FVector(me->GetActorLocation()) ,FVector(player->GetActorLocation()));
}

void AAn_CameraActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
