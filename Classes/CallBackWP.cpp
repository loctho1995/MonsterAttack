#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
#include "CallBackWP.h"
#include "cocos2d.h"

using namespace cocos2d;

namespace cocos2d
{
	ICallBack^ m_callBackPtr = nullptr;

	PlatformCenter::PlatformCenter()
	{

	}

	Platform::String^ PlatformCenter::callFunc(Platform::String^ mess)
	{
		if(mess == "landscape")
			Director::getInstance()->getOpenGLView()->setDesignResolutionSize(800, 480, ResolutionPolicy::SHOW_ALL);

		if(mess == "portrait")
			Director::getInstance()->getOpenGLView()->setDesignResolutionSize(480, 800, ResolutionPolicy::SHOW_ALL);

		return m_callBackPtr->CallFunc(mess);
	}

	void PlatformCenter::setCallBack(ICallBack^ callBack)
	{
		m_callBackPtr = callBack;
	}
}

BackButtonPressed* BackButtonPressed::m_backPressedPtr = nullptr;
BackButtonPressed::BackButtonPressed()
{
	m_backPressedPtr = this;
}

void BackButtonPressed::onBackButtonPressed()
{

}

BackButtonPressed* BackButtonPressed::getInstance()
{
	return m_backPressedPtr;
}
#endif

