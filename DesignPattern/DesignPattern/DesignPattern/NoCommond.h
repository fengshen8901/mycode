#pragma once
#include "Commond.h"
class NoCommond :
	public Commond
{
public:
	void execute() override
	{}
	void undo() override
	{}
};

