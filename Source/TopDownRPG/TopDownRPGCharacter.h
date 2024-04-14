// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "TopDownRPGCharacter.generated.h"


UCLASS(config=Game)
class ATopDownRPGCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

public:

	// Array of characters to group
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Characters;

	// Array of points for members to follow
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> GroupLocations;

	// Radius from center of group
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float GroupRadius = 200.0f;

	// Constructor
	ATopDownRPGCharacter();

	// Method for adding characters to group
	UFUNCTION(BlueprintCallable)
	void AddCharacterToGroup(AActor* Character);

	// Method for removing characters from group
	UFUNCTION(BlueprintCallable)
	void RemoveCharacterFromGroup(AActor* Character);

	// Method for calculating locations for each member
	// of the group to move to
	void CalculateGroupLocations();

	// Getter for group character index
	int GetCharacterIndex(AActor* Character);
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

