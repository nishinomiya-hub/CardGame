#include "AppDelegate.h"
#include "GameScene.h"
#include "configs/models/LayoutConfig.h"


AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
    // 初始化导演
    auto director = cocos2d::Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        // 直接使用设计分辨率创建窗口
        glview = cocos2d::GLViewImpl::createWithRect("Card Game", 
            cocos2d::Rect(0, 0, 
                LayoutConfig::DESIGN_RESOLUTION.width, 
                LayoutConfig::DESIGN_RESOLUTION.height));
#else
        glview = cocos2d::GLViewImpl::create("Card Game");
#endif
        director->setOpenGLView(glview);
    }

    // 设置设计分辨率适配策略
    glview->setDesignResolutionSize(
        LayoutConfig::DESIGN_RESOLUTION.width, 
        LayoutConfig::DESIGN_RESOLUTION.height, 
        ResolutionPolicy::SHOW_ALL
    );

    // 设置FPS显示
    director->setDisplayStats(true);

    // 设置FPS
    director->setAnimationInterval(1.0 / 60);

    // 创建游戏场景并运行
    auto scene = GameScene::create(1);
    director->runWithScene(scene);

    return true;
}
void AppDelegate::applicationDidEnterBackground() {
    cocos2d::Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
    cocos2d::Director::getInstance()->startAnimation();
}
