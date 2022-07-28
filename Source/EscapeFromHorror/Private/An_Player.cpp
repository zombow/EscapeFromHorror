// Fill out your copyright notice in the Description page of Project Settings.


#include "An_Player.h"
#include "Camera/CameraComponent.h"

// Sets default values
AAn_Player::AAn_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("SkeletalMesh'/Game/An/an_Source/an_player/an_all/LittleNightmareMarine.LittleNightmareMarine'"));
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));
	cameraComp->SetupAttachment(RootComponent);
	cameraComp->SetRelativeLocation(FVector(-200, 0, 50));

	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}
}

// Called when the game starts or when spawned
void AAn_Player::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAn_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAn_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

