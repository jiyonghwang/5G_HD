#pragma once

struct Linear
{
    float a, b;
};

struct CYBData
{
	double fGray, fSensing;
};


class CLSM
{
public:
	CLSM(void);
	~CLSM(void);
	int Count() { return m_nCount; };

	void Reset()
	{
		m_lnResult.a = 0; 
		m_lnResult.b = 0;

		m_nCount = 0;

		m_fTotalX    = 0.0f;
		m_fTotalY    = 0.0f;
		m_fDeltaX    = 0.0f;
		m_fDeltaY    = 0.0f;
		m_fDeltaXX    = 0.0f;
		m_fDeltaXY    = 0.0f;
	}

	void AddData(const CYBData& data);
	Linear GetTrendency();

private:
	void Update(const CYBData& data);

	Linear m_lnResult;
	int    m_nCount;

	double  m_fTotalX, m_fTotalY;
	double  m_fDeltaX, m_fDeltaY;
	double  m_fDeltaXX, m_fDeltaXY;

};

