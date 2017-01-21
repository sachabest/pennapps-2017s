#pragma once
#include "Animation/AnimNodeBase.h"
#include "AnimNode_IKinemaFootPlacement.h"
#include "AnimNode_IKinemaVR.generated.h"


USTRUCT()
struct IKINEMACORE_API FAnimNode_IKinemaVR : public FAnimNode_IKinemaFootPlacement
{
	GENERATED_USTRUCT_BODY()

	// FAnimNode_Base interface
	virtual void Update(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate(FPoseContext& Output) override;
	// End of FAnimNode_Base interface

	FAnimNode_IKinemaVR();
	~FAnimNode_IKinemaVR();

	// FAnimNode_Base interface
	virtual void Initialize(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones(const FAnimationCacheBonesContext & Context) override;
	// End of FAnimNode_Base interface
};
