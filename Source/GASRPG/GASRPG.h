// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define CUSTOM_DEPTH_RED 250

// Custom trace channel for navigation - blocks navigable surfaces (floors, stairs)
// while ignoring obstacles, allowing click-through navigation
#define ECC_Navigation ECC_GameTraceChannel1