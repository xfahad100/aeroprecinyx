#include "hud.h"

HUD::HUD( QGraphicsView* gv)
{
    hudScene = new QGraphicsScene;
    hudView = gv;
    hudBasePixmap = new QPixmap;
    visible = false;
    hudBasePixmap->load(":/images/hud/hud_base.png");
    hudScene->addPixmap(*hudBasePixmap);
    hudView->setStyleSheet("background-color : rgba(0,0,0,0)");
    hudView->setScene(hudScene);
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
    delete hudBasePixmap;
}
