// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

FItem::FItem()
{
	this->Name = FText::FromString("Item Name");
	this->bCanBeUsed = true;
	
	this->LimitedAmount = 1;
	this->Amount = 1;
	this->Description = FText::FromString("There need a Description");
}
