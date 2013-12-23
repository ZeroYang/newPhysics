#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void setPhyWorld(PhysicsWorld* world){m_world = world;}
    
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    void addNewSpriteAtPosition(Point p);

private:
    PhysicsWorld* m_world;
    
    bool onContactBegin(EventCustom* event, const PhysicsContact& contact);
};

#endif // __HELLOWORLD_SCENE_H__
