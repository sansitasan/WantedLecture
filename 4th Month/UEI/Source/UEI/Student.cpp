// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"

UStudent::UStudent()
	: Order(-1), Name(TEXT("Student"))
{

}

void UStudent::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
}
