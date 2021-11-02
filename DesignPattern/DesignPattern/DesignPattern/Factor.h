#pragma once


class Produc;
class Factor
{
public:
	enum PuodctType
	{
		A1,
		A2,
		B1,
		B2
	};

	virtual Produc* CreatProduc(PuodctType);
};

