#include "hud.h"

HUD::HUD( QGraphicsView* gv)
{
    hudScene = new QGraphicsScene;
    hudView = gv;
    visible = false;
    pitch = roll = alpha = 0.0;
    ppd = 9.6;       // pixels per degree of pitch

    hudBasePixmap.load(":/images/hud/hud_base.png");
    hudScene->addPixmap(hudBasePixmap);

    horizonPixmap.load(":/images/hud/horizon.png");
    horizonItem = hudScene->addPixmap(horizonPixmap);
    horizonStartPos.setX(100);
    horizonStartPos.setY(185);
    horizonItem->setTransformOriginPoint(horizonPixmap.rect().center());
    horizonItem->setPos(horizonStartPos);

    fpmPixmap.load(":/images/hud/fpm.png");
    fpmItem = hudScene->addPixmap(fpmPixmap);
    fpmStartPos.setX(292);
    fpmStartPos.setY(182);
    fpmItem->setPos(fpmStartPos);

    hudView->setStyleSheet("background-color : rgba(0,0,0,0)");
    hudView->setScene(hudScene);

    update();
}

void HUD::setVisible(bool vis) {
    visible=vis;
    if (visible) {
        hudView->show();
    } else {
        hudView->hide();
    }
};

bool HUD::getVisible() { return visible; };

void HUD::show() { hudView->show(); }
void HUD::hide() { hudView->hide(); }

HUD::~HUD()
{
    delete hudScene;
}

void HUD::update()
{
   // horizon line
   QPoint pos = horizonStartPos;
   horizonItem->setRotation(-roll);
   pos.setY(horizonStartPos.y() + (int)(pitch * ppd));
   horizonItem->setPos(pos);

   // flight path marker
   QPoint fpmPos = fpmStartPos;
   fpmPos.setY(fpmStartPos.y() + (int)(alpha * ppd));
   fpmItem->setPos(fpmPos);
}
