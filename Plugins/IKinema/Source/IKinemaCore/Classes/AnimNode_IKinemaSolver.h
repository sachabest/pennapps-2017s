#pragma once
#include "IKinemaRig.h"
#include "Animation/AnimNodeBase.h"
#include "AnimNode_IKinemaSolver.generated.h"

USTRUCT()
struct IKINEMACORE_API FAnimNode_IKinemaSolver : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()

	// The input pose is segmented into two:
	// - The FK input pose that serves as a bias for the solver.
	// - The task targets appended at the end.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	FPoseLink InPose;

	// This is set by the anim graph node, so don't allow further edits.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	class UIKinemaRig* IKinemaRig;

	// This is set by the anim graph node, so don't allow further edits.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	int32 MaxIteration;

	// The targets for the IKinema solver to try and achieve.
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category=Links, meta=(PinShownByDefault))
	TArray<FIKinemaSolverTask> Tasks;

	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = Links, meta = (PinShownByDefault))
	FIKinemaCOMTask CoMTask;

	// The targets for the IKinema solver to try and achieve.
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = Links, meta = (PinShownByDefault))
	TArray<FIKinemaSolverLookAtTask> LookAtTasks;

	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category=Links, meta=(PinHiddenByDefault))
	TArray<FIKinemaTaskProperties> TaskProperties;

	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = Links, meta = (PinHiddenByDefault))
	FIKinemaCOMTaskProperties CoMTaskProperties;

	UPROPERTY(EditFixedSize, EditAnywhere, Category=Links)
	TArray<FIKinemaTaskOverride> PinTaskProperties;

	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category=Links, meta=(PinHiddenByDefault))
	TArray<FIKinemaSegmentProperties> SegmentProperties;

	UPROPERTY(EditFixedSize, EditAnywhere, Category=Links)
	TArray<FIKinemaSegmentOverride> PinSegmentProperties;

	UPROPERTY(EditFixedSize, EditAnywhere, Category = Links)
	FIKinemaCOMTaskOverride PinCoMTaskProperties;

	/*
	* Max LOD that this node is running with MaxIteration
	* For example if you have LODHalfThreshold to be 2, it will run until LOD 2 (based on 0 index)
	* when the component LOD becomes 3, it will half the MaxIterations for the solver
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Performance, meta = (DisplayName = "LOD Threshold for Max Iterations"))
	int32 LODHalfThreshold;
	
	/*
	* Max LOD that this node is allowed to run
	* For example if you have LODThreadhold to be 2, it will run until LOD 2 (based on 0 index)
	* when the component LOD becomes 3, it will stop update/evaluate
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Performance, meta = (DisplayName = "LOD Threshold"))
	int32 LODThreshold;

private:
	bool isBound = false;
protected:

	// Keep the binding here.
	FIKinemaRigToSkeletonBinding mSkeletonBinding;

	// The IKinema solver instance data (solver and tasks).
	FIKinemaSolverInstance mSolverInstance;

	int32	UpdateVersion;
	class UWorld* currentWorld;
	// Ensures the specified object is preloaded.  ReferencedObject can be NULL.
	void PreloadObject(UObject* ReferencedObject);

public:	
	/**
		Map of LookAtTasks to SolverDefTasks
	*/
	UPROPERTY()
	TArray<int16> LookAtTasksMap;
	FAnimNode_IKinemaSolver();
	virtual ~FAnimNode_IKinemaSolver();

	void Dump(const FString& Folder);
	void SetTaskTarget(FIKinemaSolverTask& task, FTransform& animTarget, const FTransform& ToSolverSpace, const FTransform& SolverToWorld, const FIKinemaTaskDef& taskDef, bool drawDebug = true);
	// Set the rig on this.
	virtual void SetAsset(class UIKinemaRig* rig);
	virtual void UpdateSolverSettings(class UIKinemaRig* rig);

	// FAnimNode_Base interface
	virtual void Initialize(const FAnimationInitializeContext& Context) override;
	virtual void Update(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate(FPoseContext& Output) override;
	virtual void CacheBones(const FAnimationCacheBonesContext & Context) override;

	void GenerateLookAtTarget(const FIKinemaSolverLookAtTask& LookAtTask, const FTransform& animTarget, const FTransform& ToSolverSpace, const int taskIndex);
	/**
		Get the last IKinemaRig version used to set the assets for the Node.
	*/
	const int32 GetRigVersion() const; 
	// End of FAnimNode_Base interface
};
