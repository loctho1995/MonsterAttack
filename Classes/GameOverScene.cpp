#include "GameOverScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

bool GameOverScene::init()
{
    if( Scene::init() )
    {
        this->_layer = GameOverLayer::create();
        this->_layer->retain();
        this->addChild(_layer);

        return true;
    }
    else
    {
        return false;
    }
}

GameOverScene::~GameOverScene()
{
    if (_layer)
    {
        _layer->release();
        _layer = NULL;
    }
}


bool GameOverLayer::init()
{
	
    if ( LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        auto m_winSize = Director::getInstance()->getVisibleSize();
		
        this->_label = LabelTTF::create("","Artial", 32);
        _label->retain();
        _label->setColor(Color3B (100, 20, 40));
		
        _label->setPosition(Point(m_winSize.width/2, m_winSize.height/2));
        this->addChild(_label);

								
		//this->runAction( Sequence::create(
								//DelayTime::create(3),
								//CallFuncN::create(CC_CALLBACK_1(GameOverLayer::gameOverDone,this)), 
								//NULL) );
								
								this->runAction( Sequence::create(
                                DelayTime::create(3),
                                CallFunc::create(this, 
                                callfunc_selector(GameOverLayer::gameOverDone)),
                                NULL));

        return true;
    }
    else
    {
        return false;
    }
	

}

void GameOverLayer::gameOverDone()
{
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}

GameOverLayer::~GameOverLayer()
{
    if (_label)
    {
        _label->release();
        _label = NULL;
    }
}
