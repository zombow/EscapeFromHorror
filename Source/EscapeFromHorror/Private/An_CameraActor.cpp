// Fill out your copyright notice in the Description page of Project Settings.


#include "An_CameraActor.h"

#include "Kismet/KismetMathLibrary.h"

void AAn_CameraActor::BeginPlay()
{
	Super::BeginPlay();
	me = GetOwner();
	UE_LOG(LogTemp, Warning, TEXT("!!!"));
}

void AAn_CameraActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(player == nullptr)
	{
		player = Cast<AAn_Player>(GetWorld()->GetFirstPlayerController()->GetOwner());
		UE_LOG(LogTemp, Warning,TEXT("!!!"));
	}
	
	UKismetMathLibrary::FindLookAtRotation(FVector(me->GetActorLocation()), FVector(player->GetActorLocation()));
	UE_LOG(LogTemp, Warning, TEXT("!!!"));
	
}
