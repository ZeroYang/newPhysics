#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    //add physicals
    auto scene = Scene::createWithPhysics();
    //DrawMask参数可以选择打开绘制哪些部分比如，Joint、Shape、Contact等等
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    //创建一个边界
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //使用PhysicalsBody的create方法创建自己想要的物体。
    //PHYSICSBODY_MATERIAL_DEFAULT宏表示的是创建的Body的默认材质，3是边线宽度。编译运行我们会看到场景边上有红色的边界。
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	edgeNode->setPhysicsBody(body);
	scene->addChild(edgeNode);
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    //将这个World传到Layer中。所以我们在HelloWorld类中加入一个函数。将这个world存起来。
    layer->setPhyWorld(scene->getPhysicsWorld());
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                 origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    // new way to enable touch
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    // 碰撞检测回调
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_2(HelloWorld::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    return true;
}

bool HelloWorld::onContactBegin(EventCustom *event, const PhysicsContact& contact)
{
    auto sp = (Sprite*)contact.getShapeA()->getBody()->getNode();
    int tag = sp->getTag();
    CCLOG("onContactBegin: %d", tag);
    return true;
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
    auto location = touch->getLocation();
    addNewSpriteAtPosition(location);
}

//然后我们来实现addNewSpriteAtPosition函数。
//关联body与sprite从未如此简单，我们只需创建一个body，创建一个sprite然后将body设置为sprite的body即可。
void HelloWorld::addNewSpriteAtPosition(Point p)
{
    auto sprite = Sprite::create("circle.png");
	sprite->setTag(1);
	auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2);
    sprite->setPhysicsBody(body);
    sprite->setPosition(p);
	this->addChild(sprite);
}

void HelloWorld::menuCloseCallback(Object* pSender)
{
    //控制PhysicsWorld debugDraw的绘制
	if(m_world->getDebugDrawMask() != PhysicsWorld::DEBUGDRAW_NONE) {
        m_world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	} else {
		m_world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	}
}
