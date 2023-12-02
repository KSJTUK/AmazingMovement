#include "pch.h"
#include "Util/Timer.h"

Timer::Timer() { }
Timer::~Timer() { }

void Timer::SetTimeScale(float timeScale) {
    m_timeScale = timeScale;
}

float Timer::GetDeltaTime() const {
    return m_deltaTime;
}

float Timer::GetTimeScale() const {
    return m_timeScale;
}

float Timer::GetFrame() const {
    return m_fps;
}

void Timer::Init() {
    QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&m_tick));
    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_prev));
}

void Timer::Update() {
    // 현재 프레임의 시간 계산
    uint64 currentFrameTime;
    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentFrameTime));

    // 이전 프레임과 현재 프레임 사이의 시간 간격 계산
    m_deltaTime = (currentFrameTime - m_prev) / static_cast<float>(m_tick);

    // 현재까지 흐른 시간 계산
    m_timeElapsed += m_deltaTime;

    // 프레임 계산
    m_frameCount++;
    // 흐른 시간이 1초보다 크다면
    if (m_timeElapsed >= 1.0f) {
        // 프레임 률 계산후 다시 흐른 시간 초기화
        m_fps = (float)m_frameCount / m_timeElapsed;
        m_frameCount = 0;
        m_timeElapsed = 0.0f;
        //std::cout << m_fps << std::endl;
    }

    // 이전 시간을 현재시간으로 변경
    m_prev = currentFrameTime;
}