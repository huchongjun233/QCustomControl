#ifndef DRAWERWIDGET_H
#define DRAWERWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPixmap>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPropertyAnimation>
#pragma execution_character_set("utf-8")


//example:
//lockerWidget *widgetr = new locker Widget;
//locker = widget->addLocker("iconpath","text",patent);
//locker->addLockerItem()
class QDrawerWidget;
class Locker;
class LockerButton;
class LockerContainer;
class LockerItem;
class LockerAnimation;

/*抽屉*/
class QDrawerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QDrawerWidget(QWidget* parent = nullptr);

    void addLocker(Locker *locker);

    Locker *addLocker(const QString &text = "");

    void setLockerButtonHeight(int lockerHeight);

protected:
    int _lockerButtonHeight;

private:
    QSpacerItem *_spacer;
    QVBoxLayout *_vlayout;
    std::vector<Locker*> _lockers;

};


/*一个抽屉栏*/
class Locker : public QWidget
{
    Q_OBJECT
public:
    explicit Locker(const QString &Title = "", QWidget* parent = nullptr);

    void addLockerItem(LockerItem *item);

    LockerItem *addLockerItem(const QString &iconPath = "",const QString &text = "",QWidget* parent = nullptr);

    void setOPenState(bool openState);

    void setButtonHeight(int buttonHeight);

protected:
    bool _openstate;
    LockerButton    *_lockerBtn;
    LockerContainer *_container;

private:
    friend class LockerAnimation;

    QVBoxLayout *_vlayout;
    LockerAnimation *_animation;
};


/*抽屉按钮*/
class LockerButton :  public QToolButton
{
    Q_OBJECT
public:
    explicit LockerButton(const QString &btnText = "", QWidget* parent = nullptr);

    void setOpenState(bool openState);

    void setText(const QString &btnText);

protected:
    QLabel *_textLabel;

};


/*抽屉容器*/
class LockerContainer : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QRect geometry READ geometry WRITE setGeometry)
public:
    explicit LockerContainer(QWidget* parent = nullptr);

    void addItem(LockerItem *item);


private:
    QVBoxLayout *_vlayOut;
};


/*抽屉里装的Item*/
class LockerItem : public QWidget
{
    Q_OBJECT
public:
    explicit LockerItem(const QString &iconPath = "",const QString &text = "",QWidget* parent = nullptr);

    void setIcon(const QString &iconPath);

    void setTitile(const QString &text);

    void setStrech(int strideIcon,int strideText);

private:
    QLabel *_iconLabel;
    QLabel *_textLabel;
    QHBoxLayout *_hlayOut;
};


class LockerAnimation : public QObject
{
    Q_OBJECT

public:
    explicit LockerAnimation(Locker *locker,QWidget* parent = nullptr);

    void playOpenAnimation();

    void playCloseAnimation();

    void setOpenAnimationCurve(QEasingCurve::Type curveType);

    void setCloseAnimationCurve(QEasingCurve::Type curveType);

    void setAniamtionDuration(int duration/*msec*/);

private:
    Locker *_locker;
    QPropertyAnimation *_animationOpen;
    QPropertyAnimation *_aniamtionClose;
};



#endif // DRAWERWIDGET_H
