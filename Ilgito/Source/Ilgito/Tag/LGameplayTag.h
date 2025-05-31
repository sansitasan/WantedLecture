#pragma once

#include "GameplayTagContainer.h"

#define LTAG(name) FGameplayTag::RequestGameplayTag(FName(name))
#define LTAG_ACTOR_ROTATE LTAG("Actor.Action.Rotate")
#define LTAG_ACTOR_ROTATING LTAG("Actor.Action.Rotate")