// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Person.h"
#include "MyObject.h"
#include "Staff.h"
#include "Card.h"
#include "CourseInfo.h"
#include "Student.h"
#include "JsonObjectConverter.h"
#include "UObject/SavePackage.h"

//cpp 내부에서만 쓸 거라 헤더에 넣지 않음
FString MakeRandomName() {
	TCHAR FirstChar[] = TEXT("Alice");
	TCHAR MiddleChar[] = TEXT("Bob");
	TCHAR LastChar[] = TEXT("Eve");

	TArray<TCHAR> RandArray;
	RandArray.SetNum(3);
	RandArray[0] = FirstChar[FMath::RandRange(0, 4)];
	RandArray[1] = FirstChar[FMath::RandRange(0, 2)];
	RandArray[2] = FirstChar[FMath::RandRange(0, 2)];

	return RandArray.GetData();
}

UMyGameInstance::UMyGameInstance()
{
	//CDO 객체에 들어감
	//템플릿 클래스 객체로 생성이 됨
	SchoolName = TEXT("WantedSchool");

	//Strong Ref Loading
	FString ObjectPath =
		TEXT("/Script/UEI.Student'/Game/Student.Student'");

	static ConstructorHelpers::FObjectFinder<UStudent> UASSET_Student
	(
		*ObjectPath
	);

	if (UASSET_Student.Succeeded()) 
	{
		UE_LOG(LogTemp, Log, TEXT("[Constructor] Name: %s, Order: %d"),
			*UASSET_Student.Object->GetName(), UASSET_Student.Object->GetOrder());
	}
}

void UMyGameInstance::Init()
{
	Super::Init();

	//2025/04/07 Serialize & Package
	{
		FStudentData RawDataSource(31, TEXT("Korean"));

		const FString SavedPath = FPaths::Combine(
			FPlatformMisc::ProjectDir(),
			TEXT("Saved")
		);

		UE_LOG(LogTemp, Log, TEXT("Saved file folder: %s"), *SavedPath);

		//Raw Serialized && Deserialized
		{
			const FString RawDataFileName(TEXT("RawData.bin"));

			FString RawDataAbsolutePath = FPaths::Combine(SavedPath, RawDataFileName);

			UE_LOG(LogTemp, Log, TEXT("Saved file all path: %s"), *RawDataAbsolutePath);

			FPaths::MakeStandardFilename(RawDataAbsolutePath);

			UE_LOG(LogTemp, Log, TEXT("Saved file folder: %s"), *RawDataAbsolutePath);

			//Serialized
			{
				//CreateFileWriter는 new로 생성 후 반환하기에 delete로 정리해야 한다.
				//fopen
				FArchive* RawFileWriteAr = IFileManager::Get().CreateFileWriter(
					*RawDataAbsolutePath
				);

				if (RawFileWriteAr) {
					//put data
					*RawFileWriteAr << RawDataSource;

					//closed archive(fclose)
					RawFileWriteAr->Close();

					delete RawFileWriteAr;
					RawFileWriteAr = nullptr;
				}
			}

			//Deserialized
			{
				FStudentData RawDataDeserialized;
				FArchive* RawFileReadAr = IFileManager::Get().CreateFileReader(
					*RawDataAbsolutePath
				);

				if (RawFileReadAr)
				{
					*RawFileReadAr << RawDataDeserialized;

					RawFileReadAr->Close();
					delete RawFileReadAr;
					RawFileReadAr = nullptr;

					UE_LOG(LogTemp, Log, TEXT("[RawData] Name: %s, Order: %d"), *RawDataDeserialized.Name, RawDataDeserialized.Order);
				}
			}
		}

		StudentSource = NewObject<UStudent>();
		StudentSource->SetOrder(40);
		StudentSource->SetName(TEXT("San"));

		//UObject Serialized && Deserialized
		{
			const FString ObjectDataFileName(TEXT("ObjectData.bin"));

			FString ObjectDataAbsolutePath = FPaths::Combine(
				*SavedPath,
				*ObjectDataFileName
			);

			FPaths::MakeStandardFilename(ObjectDataAbsolutePath);

			//TArray<uint8> BufferArray;
			//FMemoryWriter MemoryWriterAr(BufferArray);
			//StudentSource->Serialize(MemoryWriterAr);

			if (TUniquePtr<FArchive> FileWriterAr = TUniquePtr<FArchive>(
				IFileManager::Get().CreateFileWriter(*ObjectDataAbsolutePath)
			))
			{
				//*FileWriterAr << BufferArray;
				StudentSource->Serialize(*FileWriterAr);
				FileWriterAr->Close();
			}

			if (TUniquePtr<FArchive> FileReaderAr = TUniquePtr<FArchive>(
				IFileManager::Get().CreateFileReader(*ObjectDataAbsolutePath)
			))
			{
				TObjectPtr<UStudent> StudentDes = NewObject<UStudent>();
				StudentDes->Serialize(*FileReaderAr);

				UE_LOG(LogTemp, Log, TEXT("Student's Name: %s, Order: %d"), *StudentDes->GetName(), StudentDes->GetOrder());
			}
		}

		//Json Serialized && Deserialized
		{
			const FString JsonDataFileName(TEXT("StudentJsonData.json"));
			
			FString JsonDataAbsolutePath = FPaths::Combine(
				*SavedPath,
				*JsonDataFileName
			);
			FPaths::MakeStandardFilename(JsonDataAbsolutePath);

			//Serialized
			{
				//Make Json Object
				TSharedRef<FJsonObject> JsonObjectSource = MakeShared<FJsonObject>();

				//Convert UObject to Json Object
				FJsonObjectConverter::UStructToJsonObject
				(
					StudentSource->GetClass(),
					StudentSource,
					JsonObjectSource
				);

				//Json Object to Json String
				FString JsonString;
				TSharedRef<TJsonWriter<TCHAR>> JsonWriterAr = TJsonWriterFactory<TCHAR>::Create(&JsonString);

				if (FJsonSerializer::Serialize(JsonObjectSource, JsonWriterAr))
				{
					FFileHelper::SaveStringToFile(JsonString, *JsonDataAbsolutePath);
				}
			}

			//Deserialized
			{
				FString JsonFromFile;
				FFileHelper::LoadFileToString(JsonFromFile, *JsonDataAbsolutePath);

				//Json String to Json Object
				TSharedRef<TJsonReader<TCHAR>> JsonReaderAr = TJsonReaderFactory<TCHAR>::Create(JsonFromFile);

				TSharedPtr<FJsonObject> JsonObjectResult;
				if (FJsonSerializer::Deserialize(JsonReaderAr, JsonObjectResult)) 
				{
					TObjectPtr<UStudent> JsonStudent = NewObject<UStudent>();
					if (FJsonObjectConverter::JsonObjectToUStruct
					(
						JsonObjectResult.ToSharedRef(),
						JsonStudent->GetClass(),
						JsonStudent
					)) {
						UE_LOG(LogTemp, Log, TEXT("[JsonData] Student Name: %s, Order: %d"), 
							*JsonStudent->GetName(), JsonStudent->GetOrder());
					}
				}
			}
		}

		//SaveStudentPackage();
		//LoadStudentPackage();
		FString ObjectPath = FString::Printf
		(
			TEXT("%s.%s"), 
			TEXT("/Game/Student"),
			TEXT("Student")
		);

		StreamableHandle = StreamableManager.RequestAsyncLoad
		(
			ObjectPath,
			[&]() {

				TObjectPtr<UStudent> Student = Cast<UStudent>(StreamableHandle->GetLoadedAsset());
				
				if (Student) {
					UE_LOG(LogTemp, Log,
						TEXT("[AsyncLoad] Name: %s, Order: %d"),
						*Student->GetName(), Student->GetOrder());
				}

				StreamableHandle->ReleaseHandle();
				StreamableHandle.Reset();
			}
		);
	}

	/*
	CourseInfo = NewObject<UCourseInfo>(this);
	
	UStaff* Staff1 = NewObject<UStaff>();
	Staff1->SetName(TEXT("1"));

	UStaff* Staff2 = NewObject<UStaff>();
	Staff2->SetName(TEXT("2"));

	UStaff* Staff3 = NewObject<UStaff>();
	Staff3->SetName(TEXT("3"));

	CourseInfo->OnChanged.BindUObject(Staff1, &UStaff::GetNotification);//AddUObject(Staff1, &UStaff::GetNotification);
	CourseInfo->OnChanged.BindUObject(Staff1, &UStaff::GetNotification);//AddUObject(Staff2, &UStaff::GetNotification);
	CourseInfo->OnChanged.BindUObject(Staff1, &UStaff::GetNotification);//AddUObject(Staff3, &UStaff::GetNotification);

	CourseInfo->ChangeCourseInfo(SchoolName, TEXT("New CourseInfo"));
	
	const int32 StudentCount = 300;
	for (int32 i = 0; i < StudentCount; ++i) {
		StudentData.Emplace(FStudentData(i, MakeRandomName()));
	}
	
	TArray<FString> AllStudentNames;
	Algo::Transform(StudentData, AllStudentNames, 
		[](const FStudentData& Val) {
			return Val.Name;
		});
	
	UE_LOG(LogTemp, Log, TEXT("All Student Name Count: %d"), AllStudentNames.Num());
	
	TSet<FString> AllUniqueNames;
	
	Algo::Transform(StudentData, AllUniqueNames,
		[](const FStudentData& Val) {
			return Val.Name;
		});
	
	UE_LOG(LogTemp, Log, TEXT("All Student Unique Name Count: %d"), AllUniqueNames.Num());

	TMap<FString, int32> StudentMapByName;

	Algo::Transform(StudentData, StudentMapByName,
		[](const FStudentData& Val) {
			return TPair<FString, int32> (Val.Name, Val.Order);
		});

	UE_LOG(LogTemp, Log, TEXT("All Student Unique Name Count: %d"), StudentMapByName.Num());

	TSet<FStudentData> StudentSet;
	for (int i = 0; i < StudentCount; ++i) {
		StudentSet.Emplace(FStudentData(i, MakeRandomName()));
	}
	*/

	//TArray<UPerson*> Persons =
	//{
	//	NewObject<UPerson>(),
	//	NewObject<UStaff>(),
	//	NewObject<UMyObject>()
	//};
	//
	//for (const auto Person : Persons) {
	//	IITest* Interface = Cast<IITest>(Person);
	//	if (Interface) {
	//		Interface->DoLesson();
	//	}
	//
	//	const UCard* OwnCard = Person->GetCard();
	//	ensure(OwnCard);
	//
	//	const UEnum* CardEnumType = FindObject<UEnum>(nullptr, TEXT("/Script/UEI.ECardType"));
	//
	//	if (CardEnumType) {
	//		FString CardMetaData = CardEnumType->GetDisplayNameTextByValue(
	//			(int64)OwnCard->GetCardType()).ToString();
	//
	//		UE_LOG(LogTemp, Log, TEXT("%s's Card Type: %s"), *Person->GetName(), *CardMetaData);
	//	}
	//}
}

void UMyGameInstance::SaveStudentPackage()
{
	TObjectPtr<UPackage> StudentPackage = LoadPackage(nullptr, TEXT("/Game/Student"), LOAD_None);
	if (StudentPackage) {
		StudentPackage->FullyLoad();
	}

	StudentPackage = CreatePackage(TEXT("/Game/Student"));
	EObjectFlags ObjectFlag = RF_Public | RF_Standalone;

	TObjectPtr<UStudent> TopStudent = NewObject<UStudent>
		(
			StudentPackage, 
			UStudent::StaticClass(),
			TEXT("Student"),
			ObjectFlag
		);

	TopStudent->SetOrder(15);
	TopStudent->SetName(TEXT("Crust"));

	const FString PackageFileName = FPackageName::LongPackageNameToFilename
	(
		TEXT("/Game/Student"),
		FPackageName::GetAssetPackageExtension()
	);

	FSavePackageArgs SaveArgs;

	SaveArgs.TopLevelFlags = ObjectFlag;

	if (UPackage::SavePackage
	(
		StudentPackage,
		nullptr,
		*PackageFileName,
		SaveArgs
	)) 
	{
		UE_LOG(LogTemp, Log, TEXT("Save Package Success"));
	}
}

void UMyGameInstance::LoadStudentPackage()
{
	TObjectPtr<UPackage> StudentPackage = LoadPackage
	(
		nullptr, 
		TEXT("/Game/Student"), 
		LOAD_None
	);

	ensure(!StudentPackage);

	StudentPackage->FullyLoad();

	TObjectPtr<UStudent> Student = FindObject<UStudent>
		(
			StudentPackage,
			TEXT("Student")
		);

	ensure(!Student);

	UE_LOG(LogTemp, Log,
		TEXT("[FindObject Asset] Name: %s, Order: %d"),
		*Student->GetName(), Student->GetOrder());
}
