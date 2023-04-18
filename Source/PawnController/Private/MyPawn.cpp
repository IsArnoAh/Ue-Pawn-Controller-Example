// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

#include "Camera/CameraComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//设置默认玩家为玩家0
	AutoPossessPlayer=EAutoReceiveInput::Player0;
	//创建根组件
	RootComponent=CreateDefaultSubobject<USceneComponent>(TEXT("RootComponet"));
	//创建相机和可见pawn组件
	UCameraComponent* MyCamera=CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
	MyComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyComponet"));
	//相机附着Pawn上
	
	MyCamera->SetupAttachment(RootComponent);
	MyCamera->SetRelativeLocation(FVector(250.0f,0.0f,250.0f));
	MyCamera->SetRelativeLocation(FVector(-500.0f,0.0f,0.0f));
	MyComponent->SetupAttachment(RootComponent);
	

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//物体大小变化的逻辑
	{
		float ChangeScale=MyComponent->GetComponentScale().X;
		if (bChangeSize)
		{
			ChangeScale+=DeltaTime;
		}
		else
		{
			ChangeScale-=(DeltaTime*0.5f);
		}
		ChangeScale=FMath::Clamp(ChangeScale,1.0f,2.0f);
		MyComponent->SetWorldScale3D(FVector(ChangeScale));
	}
	//处理物体移动逻辑
	{
		if (!MyVelocity.IsZero())
		{
			FVector NewLocation=GetActorLocation()+(MyVelocity*DeltaTime);
			SetActorLocation(NewLocation);
		}
	}
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//操作绑定响应
	InputComponent->BindAction("ChangeSize",IE_Pressed,this,&AMyPawn::StartChangeSize);
	InputComponent->BindAction("ChangeSize",IE_Released,this,&AMyPawn::StopChangeSize);
	//轴映射绑定
	InputComponent->BindAxis("MoveX",this,&AMyPawn::MoveX);
	InputComponent->BindAxis("MoveY",this,&AMyPawn::MoveY);
}
//轴映射绑定
void AMyPawn::MoveX(float AxisValue)
{
	MyVelocity.X=FMath::Clamp(AxisValue,-1.0f,1.0f)*100.0f;
}

void AMyPawn::MoveY(float AxisValue)
{
	MyVelocity.Y=FMath::Clamp(AxisValue,-1.0f,1.0f)*100.0f;
}

void AMyPawn::StartChangeSize()
{
	bChangeSize=true;
}

void AMyPawn::StopChangeSize()
{
	bChangeSize=false;
}




