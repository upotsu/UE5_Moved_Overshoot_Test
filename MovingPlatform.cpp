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
	Super::Tick(DeltaTime); //Tick関数の呼び出し

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);

}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	//現在地を呼び出す

	CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);

	//フレームレートに依存しないコードにする

	SetActorLocation(CurrentLocation);

	DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);
	//DistのアクセスにFベクトルクラスを使用
	//クラス関数にアクセスしたい場合はスコープ解決演算子を使用

	if (DistanceMoved >= MoveDistance) 
	{
		float Overshoot = DistanceMoved - MoveDistance;
		FString PlatformName = GetName();
		UE_LOG(LogTemp, Display, TEXT("%s overshoot by %f"), *PlatformName,Overshoot);

		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		FVector NewStartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(NewStartLocation);
		StartLocation = NewStartLocation;
		//足場はFベクトルのインスタンス
		//インスタンスの中にある関数にアクセスしたい場合は、変わりにドット演算子を使用

		PlatformVelocity = -PlatformVelocity;
		
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{

	//Rotate the platform
}
