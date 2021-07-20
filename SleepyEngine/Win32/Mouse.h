#pragma once
#include <queue>
#include <optional>
#include "../Utilities/NumericDataTypes.h"

class Mouse
{
	friend class Win32Window;
public:
	struct RawDelta
	{
		u32 x, y;
	};
	class Event
	{
	public:
		enum class Type
		{
			LPress,
			LRelease,
			RPress,
			RRelease,
			WheelUp,
			WheelDown,
			Move,
			Enter,
			Leave,
		};
	private:
		Type type;
		bool leftIsPressed;
		bool rightIsPressed;
		u32 x;
		u32 y;
	public:
		Event( Type type, const Mouse& parent ) noexcept
			:
			type( type ),
			leftIsPressed( parent.m_bLeftIsPressed ),
			rightIsPressed( parent.m_bRightIsPressed ),
			x( parent.m_iX ),
			y( parent.m_iY )
		{}
		Type GetType() const noexcept
		{
			return type;
		}
		std::pair<u32, u32> GetPos() const noexcept
		{
			return{ x,y };
		}
		u32 GetPosX() const noexcept
		{
			return x;
		}
		u32 GetPosY() const noexcept
		{
			return y;
		}
		bool LeftIsPressed() const noexcept
		{
			return leftIsPressed;
		}
		bool RightIsPressed() const noexcept
		{
			return rightIsPressed;
		}
	};
public:
	Mouse() = default;
	Mouse( const Mouse& ) = delete;
	Mouse& operator=( const Mouse& ) = delete;
	std::pair<u32, u32> GetPos() const noexcept;
	std::optional<RawDelta> ReadRawDelta() noexcept;
	u32 GetPosX() const noexcept;
	u32 GetPosY() const noexcept;
	bool IsInWindow() const noexcept;
	bool LeftIsReleased() const noexcept;
	bool LeftIsPressed() const noexcept;
	bool RightIsPressed() const noexcept;
	std::optional<Mouse::Event> Read() noexcept;
	bool IsEmpty() const noexcept
	{
		return m_qBuffer.empty();
	}
	void Flush() noexcept;
	void EnableRaw() noexcept;
	void DisableRaw() noexcept;
	bool RawEnabled() const noexcept;
private:
	void OnMouseMove( u32 x, u32 y ) noexcept;
	void OnMouseLeave() noexcept;
	void OnMouseEnter() noexcept;
	void OnRawDelta( u32 dx, u32 dy ) noexcept;
	void OnLeftPressed( u32 x, u32 y ) noexcept;
	void OnLeftReleased( u32 x, u32 y ) noexcept;
	void OnRightPressed( u32 x, u32 y ) noexcept;
	void OnRightReleased( u32 x, u32 y ) noexcept;
	void OnWheelUp( u32 x, u32 y ) noexcept;
	void OnWheelDown( u32 x, u32 y ) noexcept;
	void TrimBuffer() noexcept;
	void TrimRawInputBuffer() noexcept;
	void OnWheelDelta( u32 x, u32 y, u32 delta ) noexcept;
private:
	static constexpr unsigned int m_iBufferSize = 16u;
	u32 m_iX;
	u32 m_iY;
	bool m_bLeftIsPressed = false;
	bool m_bRightIsPressed = false;
	bool m_bIsInWindow = false;
	u32 m_iWheelDeltaCarry = 0;
	bool m_bRawEnabled = false;
	std::deque<Event> m_qBuffer;
	std::queue<RawDelta> m_qRawDeltaBuffer;
};