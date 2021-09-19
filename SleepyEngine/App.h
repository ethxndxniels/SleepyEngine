#pragma once
#include "./Win32/Win32Window.h"
#include "./GraphicsDeviceInterface/GraphicsDeviceInterface.h"
#include "./SceneManager/SceneManager.h"
#include "./Utilities/FrameTimer.h"
#include "./GUI/ImguiManager.h"

class App
{
public:
	App();
	u32 Launch();
	~App();
private:
	void ExecuteFrame();
private:
	ImguiManager imgui;
	Win32Window m_Win32Window;
	GraphicsDeviceInterface m_GDI;
	SceneManager m_SceneManager;
	FrameTimer timer;
	// TODO: 
	// - Raw Mouse Input
	// - Platform Interface
};