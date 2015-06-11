#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
#ifndef __CALL_BACK_WP__
#define __CALL_BACK_WP__
#include "cocos2d.h"
using namespace cocos2d;

namespace cocos2d
{
	//[Windows::Foundation::Metadata::WebHostHidden]
	public interface class ICallBack
	{
	public:
		virtual Platform::String^ CallFunc(Platform::String^ mess);
	};

	public ref class PlatformCenter sealed
	{
	public:
		PlatformCenter();
		static void setCallBack(ICallBack^ callBack);
		static Platform::String^ callFunc(Platform::String^ mess);
	};
}

//public: failed because it's Native type
class BackButtonPressed
	{
	public:		
		static BackButtonPressed* getInstance();
		virtual void onBackButtonPressed();
		BackButtonPressed();

	private:
		static BackButtonPressed* m_backPressedPtr;
	};
#endif
#endif