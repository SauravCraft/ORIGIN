#include "Actors/PickupActor.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Components/InventoryComponent.h"

APickupActor::APickupActor()
{
    PrimaryActorTick.bCanEverTick = false;

    Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    RootComponent = Sphere;

    Sphere->InitSphereRadius(60.f);
    Sphere->SetCollisionProfileName(TEXT("Trigger"));

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);

    Sphere->OnComponentBeginOverlap.AddDynamic(
        this,
        &APickupActor::OnSphereBeginOverlap);
}

void APickupActor::BeginPlay()
{
    Super::BeginPlay();
}

void APickupActor::OnSphereBeginOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (!OtherActor)
    {
        return;
    }

    UInventoryComponent* Inventory =
        OtherActor->FindComponentByClass<UInventoryComponent>();

    if (!Inventory)
    {
        return;
    }

    if (Inventory->AddItem(ItemData, Quantity))
    {
        Destroy();
    }
}