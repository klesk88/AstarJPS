#pragma once

//base config class that is used as interface by all configs
class CConfigBase
{
public:
	CConfigBase() = default;
	virtual ~CConfigBase() = default;

	//load data from file
	virtual void Load() = 0;
};

