#pragma once

#include "cocos2d.h"

/**
 * @brief 游戏应用委托类
 * @details 负责应用程序生命周期管理，初始化游戏环境
 */
class AppDelegate : private cocos2d::Application {
public:
    /**
     * @brief 构造函数
     */
    AppDelegate();

    /**
     * @brief 析构函数
     */
    virtual ~AppDelegate();

    /**
     * @brief 应用程序启动时调用
     * @return 初始化成功返回true
     */
    virtual bool applicationDidFinishLaunching() override;

    /**
     * @brief 应用程序进入后台时调用
     */
    virtual void applicationDidEnterBackground() override;

    /**
     * @brief 应用程序回到前台时调用
     */
    virtual void applicationWillEnterForeground() override;
};
