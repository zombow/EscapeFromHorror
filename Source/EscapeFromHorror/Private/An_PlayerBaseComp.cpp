// Fill out your copyright notice in the Description page of Project Settings.


#include "An_PlayerBaseComp.h"
#include "An_Player.h"

// Sets default values for this component's properties
UAn_PlayerBaseComp::UAn_PlayerBaseComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	// ...
}

void UAn_PlayerBaseComp::InitializeComponent()
{
	me = Cast<AAn_Player>(GetOwner());
	myMovement = me->GetCharacterMovement();
	me->onPlayerInputBindingDelegate.AddUObject(this, &UAn_PlayerBaseComp::PlayerInputBinding);
}

// Called when the game starts
void UAn_PlayerBaseComp::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UAn_PlayerBaseComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

