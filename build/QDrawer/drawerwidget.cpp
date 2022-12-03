#include <drawerwidget.h>
#include <QDebug>
//------------------------------------------------------------------------Drawer-----------------------------------------------------------------//
//------------------------------------------------------------------------begin------------------------------------------------------------------//
QDrawerWidget::QDrawerWidget(QWidget *parent):
    QWidget(parent),
    _vlayout(new QVBoxLayout),
    _lockerButtonHeight(20),
    _spacer(new QSpacerItem(20,80,QSizePolicy::Preferred,QSizePolicy::Expanding))
{
    setLayout(_vlayout);
    _vlayout->setSpacing(0);
    _vlayout->setMargin(0);

    _spacer->setAlignment(Qt::AlignVCenter);
}

void QDrawerWidget::addLocker(Locker *locker)
{
    _vlayout->removeItem(_spacer);
    _vlayout->addWidget(locker);
    _vlayout->insertItem(_vlayout->count(),_spacer);
    locker->setButtonHeight(_lockerButtonHeight);
}

Locker *QDrawerWidget::addLocker(const QString &text)
{
    _vlayout->removeItem(_spacer);
    Locker *locker = new Locker(text,this);
    locker->setButtonHeight(_lockerButtonHeight);
    _vlayout->addWidget(locker);
    _vlayout->insertItem(_vlayout->count(),_spacer);
    _lockers.push_back(locker);
    return locker;
}

void QDrawerWidget::setLockerButtonHeight(int lockerHeight)
{
    for (auto iter = _lockers.begin();iter != _lockers.end(); iter++) {
        (*iter)->setButtonHeight(lockerHeight);
    }
    _lockerButtonHeight = lockerHeight;
}
//--------------------------------------------------------------------------end------------------------------------------------------------------//




//------------------------------------------------------------------------Locker-----------------------------------------------------------------//
//------------------------------------------------------------------------beign------------------------------------------------------------------//
Locker::Locker(const QString &Title, QWidget *parent):
    QWidget(parent),
    _openstate(true),
    _lockerBtn(new LockerButton(Title,this)),
    _container(new LockerContainer(this)),
    _vlayout(new QVBoxLayout(this)),
    _animation(new LockerAnimation(this,this))
{
    setLayout(_vlayout);
    _vlayout->setSpacing(0);
    _vlayout->setMargin(0);
    _vlayout->addWidget(_lockerBtn);
    _vlayout->addWidget(_container);

    connect(_lockerBtn,&QPushButton::clicked,[=](){
        setOPenState(!_openstate);
    });
}

void Locker::setOPenState(bool openState)
{
  _container->setVisible(openState);
  _openstate = openState;
  _lockerBtn->setOpenState(openState);
  if( openState )
  {
  _animation->playOpenAnimation();
  }else{
  _animation->playCloseAnimation();
  }
}

void Locker::setButtonHeight(int buttonHeight)
{
    _lockerBtn->setMinimumHeight(buttonHeight);
}

void Locker::addLockerItem(LockerItem *item)
{
    _container->addItem(item);
}


LockerItem *Locker::addLockerItem(const QString &iconPath, const QString &text, QWidget *parent)
{
    LockerItem *lockerItem = new LockerItem(iconPath,text,parent);
    _container->addItem(lockerItem);
    return lockerItem;
}
//------------------------------------------------------------------------end-------------------------------------------------------------------//




//------------------------------------------------------------------------LockerButton-----------------------------------------------------------------//
//------------------------------------------------------------------------begin-----------------------------------------------------------------------//
LockerButton::LockerButton(const QString &btnText, QWidget *parent):
    QToolButton(parent),
    _textLabel(new QLabel(this))
{
    setText(btnText);
    setArrowType(Qt::ArrowType::RightArrow);

    setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Minimum));
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QHBoxLayout *hlayout = new QHBoxLayout(this);
    hlayout->setAlignment(Qt::AlignHCenter);
    hlayout->addWidget(_textLabel);
    setLayout(hlayout);
}


void LockerButton::setOpenState(bool openState)
{
    if( openState )
    {
        setArrowType(Qt::ArrowType::DownArrow);
    }else{
        setArrowType(Qt::ArrowType::RightArrow);
    }
}

void LockerButton::setText(const QString &btnText)
{
        _textLabel->setText(btnText);
}

//--------------------------------------------------------------------------end-----------------------------------------------------------------//




//------------------------------------------------------------------------LockerContainer---------------------------------------------------------//
//------------------------------------------------------------------------beign-------------------------------------------------------------------//

LockerContainer::LockerContainer(QWidget *parent):
    QWidget(parent),
    _vlayOut(new QVBoxLayout(this))
{
    setLayout(_vlayOut);
    _vlayOut->setSpacing(0);
    _vlayOut->setMargin(0);
    lower();
}

void LockerContainer::addItem(LockerItem *item)
{
    _vlayOut->addWidget(item);
}


//
//-------------------------------------------------------------------------end------------------------------------------------------------------//




//------------------------------------------------------------------------LockerItem-------------------------------------------------------------//
//------------------------------------------------------------------------beign------------------------------------------------------------------//
LockerItem::LockerItem(const QString &iconPath, const QString &text, QWidget *parent):
    QWidget(parent),
    _iconLabel(new QLabel(this)),
    _textLabel(new QLabel(this)),
    _hlayOut(new QHBoxLayout(this))
{
    setLayout(_hlayOut);
    setIcon(iconPath);
    setTitile(text);
    _hlayOut->addWidget(_iconLabel);
    _hlayOut->addWidget(_textLabel);
    _hlayOut->setStretch(0,1);
    _hlayOut->setStretch(1,3);
}

void LockerItem::setIcon(const QString &iconPath)
{
     QPixmap *pix = new QPixmap(iconPath);
    _iconLabel->setPixmap(*pix);
}

void LockerItem::setTitile(const QString &text)
{
    _textLabel->setText(text);
}

void LockerItem::setStrech(int strideIcon, int strideText)
{
    _hlayOut->setStretch(0,strideIcon);
    _hlayOut->setStretch(1,strideText);
}

//---------------------------------------------------------------------------end-----------------------------------------------------------------//


LockerAnimation::LockerAnimation(Locker *locker, QWidget *parent):
    QObject(parent),
    _locker(locker),
    _animationOpen(new QPropertyAnimation(locker->_container,"geometry",parent)),
    _aniamtionClose(new QPropertyAnimation(locker->_container,"geometry",parent))
{
    setOpenAnimationCurve(QEasingCurve::Type::InSine);
    setCloseAnimationCurve(QEasingCurve::Type::InSine);
    setAniamtionDuration(200);
}

void LockerAnimation::playOpenAnimation()
{
    _animationOpen->setTargetObject(_locker->_container);
    _animationOpen->setStartValue(QRect(_locker->_container->geometry().x(),
                                        _locker->_container->geometry().y()-40,
                                        _locker->_container->geometry().width(),
                                        _locker->_container->geometry().height()-40));


    _animationOpen->setEndValue(QRect(_locker->_container->geometry().x(),
                                      _locker->_container->geometry().y(),
                                      _locker->_container->geometry().width(),
                                      _locker->_container->geometry().height()));

    _animationOpen->start();


}

void LockerAnimation::playCloseAnimation()
{

}

void LockerAnimation::setOpenAnimationCurve(QEasingCurve::Type curveType)
{
    _animationOpen->setEasingCurve(QEasingCurve(curveType));
}

void LockerAnimation::setCloseAnimationCurve(QEasingCurve::Type curveType)
{
    _aniamtionClose->setEasingCurve(QEasingCurve(curveType));
}

void LockerAnimation::setAniamtionDuration(int duration)
{
    _animationOpen->setDuration(duration);
    _aniamtionClose->setDuration(duration);
}
