#include "StdAfx.h"
#include "GlobalCenter.h"

CGlobalCenter Global2;			// 实体
IGlobal* Global = &Global2;		// App全局访问接口

CGlobalCenter::CGlobalCenter(void)
{
}


CGlobalCenter::~CGlobalCenter(void)
{
}

HRESULT CGlobalCenter::Initialize( IModule* UpperFrame/*=NULL*/ )
{
	_InitializeLog();		// 所有地方都依赖log，所以当最先初始化
	_InitializeConfig();
	return S_OK;
}

HRESULT CGlobalCenter::UnInitialize()
{
	_UnInitializeConfig();
	_UnInitializeLog();
	return S_OK;
}

HRESULT CGlobalCenter::Run()
{
	return S_OK;
}

HRESULT CGlobalCenter::Terminate()
{
	return S_OK;
}

HRESULT CGlobalCenter::GetIConfig( IConfig** pConfig )
{
	*pConfig = dynamic_cast<IConfig*>(&m_config);
	return S_OK;
}

void CGlobalCenter::_InitializeConfig()
{
	m_config.Initialize(NULL);
}

void CGlobalCenter::_UnInitializeConfig()
{
	m_config.UnInitialize();
}

HRESULT CGlobalCenter::SetThreadName( CString name )
{
	return S_OK;
}

