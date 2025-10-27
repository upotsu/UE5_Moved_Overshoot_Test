// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"


// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void MyTestFunction(float MyFloatParam,FString MyStringParam)
{
	UE_LOG(LogTemp, Display, TEXT("MyFloatParam is %f"),MyFloatParam);

	UE_LOG(LogTemp, Display, TEXT("MyStringParam is %s"), *MyStringParam);
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	FString MyName = GetName();
	MyTestFunction(3.5f,MyName);

	StartLocation = GetActorLocation();
	
}	 



// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); //Tick�֐��̌Ăяo��

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);

}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	//���ݒn���Ăяo��

	CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);

	//�t���[�����[�g�Ɉˑ����Ȃ��R�[�h�ɂ���

	SetActorLocation(CurrentLocation);

	DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);
	//Dist�̃A�N�Z�X��F�x�N�g���N���X���g�p
	//�N���X�֐��ɃA�N�Z�X�������ꍇ�̓X�R�[�v�������Z�q���g�p

	if (DistanceMoved >= MoveDistance) 
	{
		float Overshoot = DistanceMoved - MoveDistance;
		FString PlatformName = GetName();
		UE_LOG(LogTemp, Display, TEXT("%s overshoot by %f"), *PlatformName,Overshoot);

		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		FVector NewStartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(NewStartLocation);
		StartLocation = NewStartLocation;
		//�����F�x�N�g���̃C���X�^���X
		//�C���X�^���X�̒��ɂ���֐��ɃA�N�Z�X�������ꍇ�́A�ς��Ƀh�b�g���Z�q���g�p

		PlatformVelocity = -PlatformVelocity;
		
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{

	//Rotate the platform
}
