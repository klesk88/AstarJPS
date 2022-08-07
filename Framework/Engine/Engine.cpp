#include "Framework/Engine/Engine.h"

#include "Framework/Engine/Camera/CameraTypes/BaseCamera.h"
#include "Framework/Engine/Core/Timer.h"
#include "Framework/Engine/ManagerUpdateInput.h"
#include "Framework/Utils/DebugMacros.h"
#include "Framework/Utils/Imgui/imgui.h"

namespace EngineHelpers
{
	static constexpr int kMaxTickSamples = 100;
	static constexpr float kfMaxTargetFrameTime = 1000.f / 60.f;
}

////////////////////////////////////////////////////////////////

CEngine::CEngine()
	: CSingleton<CEngine>(*this)
	, m_tickSamples(EngineHelpers::kMaxTickSamples, 0)
{}

bool CEngine::Init()
{
	m_config.Load();
	m_window.Init(m_config.GetWindowConfig());
	if (!m_renderer.Initialize(m_config.GetWindowConfig(), m_window.GetHWND()))
	{
		return false;
	}

	m_inputManager.Init();
	m_cameraManager.Init(m_config);
	m_picker.Init();
	m_gameManager.Init(m_config);
	m_imguiEventId = GetRenderer().GetImguiEventHandler().Attach([this]() { OnImguiUpdate(); });
	return true;
}

void CEngine::Run()
{
	// Loop until there is a quit message from the window or the user.
	while (true)
	{
		if (IterateWindowsMessagesGetIfQuit())
		{
			break;
		}
		
		const float fPrevDeltaTime = m_flastDeltaTimeSec;
		m_flastDeltaTimeSec = Update();

		OnPostUpdate(fPrevDeltaTime);
	}

	Shutdown();
}

void CEngine::Shutdown()
{
	GetRenderer().GetImguiEventHandler().Detach(m_imguiEventId);

	m_gameManager.Shutdown();
    m_picker.Shutdown();
	m_cameraManager.Shutdown();
	m_inputManager.Shutdown();
	m_renderer.Shutdown();
}

void CEngine::StoreTickCount()
{
	m_tickSamples[m_iTickIndex] = m_iCurrentTickCount;
	m_iTickSum += m_iCurrentTickCount;
	m_iCurrentTickCount = 0;
	m_iTickIndex = (m_iTickIndex + 1) % m_tickSamples.size();
	m_iTickSum -= m_tickSamples[m_iTickIndex];

	if (m_iTickIndex == 0)
	{
		//we did a full iteration of the array
		m_bHasFilledTickSampleArray = true;
	}
}

bool CEngine::IterateWindowsMessagesGetIfQuit() const
{
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

	bool bShouldQuit = false;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

		bShouldQuit |= (msg.message == WM_QUIT || m_inputManager.IsEscapePressed());
    }

	return bShouldQuit;
}

float CEngine::Update()
{
	float fFrameTimeMs = 0.f;

	{
        CScopedTimer frameTimer(fFrameTimeMs);

        m_renderer.PreUpdate();

		m_inputManager.Update(m_flastDeltaTimeSec);

		const CInputKeyboardState* pKeyboardState = m_inputManager.GetKeyboardState();
        const CInputMouseState* pMouseState = m_inputManager.GetMouseState();

		const CManagerUpdateInput updateInput{*pKeyboardState , *pMouseState, m_flastDeltaTimeSec };

        m_cameraManager.Update(updateInput);
        m_picker.Update(updateInput);
        m_gameManager.Update(updateInput);

        const CBaseCamera& rCurrentCamera = m_cameraManager.GetCurrentCamera();
        m_renderer.Update(rCurrentCamera.GetViewMatrix(), rCurrentCamera.GetProjMatrix());

        m_renderer.PostUpdate(m_config.GetWindowConfig().GetVSyncEnable());

		m_inputManager.EndFrame();
	}

	return fFrameTimeMs;
}

void CEngine::OnPostUpdate(const float fPrevDeltaTime)
{
#if _DEBUG
    static constexpr float fMaxAcceptableDeltaTime = 1.f;
    if (m_flastDeltaTimeSec > fMaxAcceptableDeltaTime)
    {
        //if we are debugging then avoid to get crazy delta times
        //due to breakpoints
        m_flastDeltaTimeSec = fPrevDeltaTime;
    }
#endif

    // Frame rate limiter
    if (m_flastDeltaTimeSec < EngineHelpers::kfMaxTargetFrameTime)
    {
        Sleep(static_cast<DWORD>(EngineHelpers::kfMaxTargetFrameTime - m_flastDeltaTimeSec));
        m_flastDeltaTimeSec = EngineHelpers::kfMaxTargetFrameTime / 1000.f;
    }

    if (m_fLastTickSampleStartTime < 1.f)
    {
        AddTickCount();
        m_fLastTickSampleStartTime += m_flastDeltaTimeSec;
    }
    else
    {
        m_fLastTickSampleStartTime = 0.f;
        StoreTickCount();
    }
}

void CEngine::OnImguiUpdate()
{
	if (m_iTickIndex == 0)
	{
		return;
	}

	const float fFPS = static_cast<float>(m_iTickSum) / (m_bHasFilledTickSampleArray ? EngineHelpers::kMaxTickSamples : m_iTickIndex);
    ImGui::Text("FPS: %.3f", fFPS);
}