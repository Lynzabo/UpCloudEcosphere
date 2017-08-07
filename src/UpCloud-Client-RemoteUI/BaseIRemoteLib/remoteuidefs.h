#ifndef REMOTEUIDEFS
#define REMOTEUIDEFS
////定义远程UI常用代码

//移动当前视图到窗体中间
//UCR代表UpCloudRemoteUI
#ifndef UCR_MOVE_WINDOW_2_DESKTOP_CENTER
#define UCR_MOVE_WINDOW_2_DESKTOP_CENTER move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
//or    move(QApplication::desktop()->availableGeometry(this).center()- this->rect().center());
//上面两种方法都可以
#endif  //UCR_MOVE_WINDOW_2_DESKTOP_CENTER
#ifndef UCR_MOVE_WINDOW_2_DESKTOP_TOPLEFT
#define UCR_MOVE_WINDOW_2_DESKTOP_TOPLEFT move(QApplication::desktop()->availableGeometry(this).topLeft());
#endif  //UCR_MOVE_WINDOW_2_DESKTOP_TOPLEFT
#endif // REMOTEUIDEFS

