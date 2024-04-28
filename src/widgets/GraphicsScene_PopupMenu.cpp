#include "GraphicsScene_PopupMenu.h"
#include "../widgets/ManeuverSettingsWidget.h"
#include <QDebug>

GraphicsScenePopupMenu* GraphicsScenePopupMenu::_instance = NULL;

GraphicsScenePopupMenu* GraphicsScenePopupMenu::instance ( QWidget *parent)
{
    if ( _instance == NULL)
        _instance = new GraphicsScenePopupMenu ( parent);

    return _instance;
}

void GraphicsScenePopupMenu::cleanup()
{
    if ( _instance != NULL)
    {
        delete _instance;
        _instance = NULL;
    }
}

GraphicsScenePopupMenu::GraphicsScenePopupMenu ( QWidget *parent ) :
    QMenu ( parent )
{
    connect ( this, SIGNAL ( triggered ( QAction* ) ), this, SLOT ( slotHandlingAction ( QAction* ) ) );
}

GraphicsScenePopupMenu::~GraphicsScenePopupMenu ()
{

}

void GraphicsScenePopupMenu::slotHandlingAction ( QAction* action )
{
    if (action)
    {
        QList<QVariant> listVariant = action->data().toList();
        if(listVariant.isEmpty()) return;

        ActionType actionType = static_cast <ActionType> ( listVariant.value(0).toInt() );

        switch ( actionType )
        {
            case DeletePoint:
            {
                int pointId = listVariant.value(1).toInt();

                emit sigDeletePoint(pointId);
            }
            break;

            case InsertPoint:
            {
                QPointF scenePos = listVariant.value(1).toPointF();

                emit sigInsertPoint(scenePos);
            }
            break;

            case Settings:
            {
                ManeuverSettingsWidget* maneuverSettingsWidget = new ManeuverSettingsWidget();
                maneuverSettingsWidget->show();
            }
            break;
        }

    }
}

void GraphicsScenePopupMenu::showMenu ( MenuType type, const QPoint& screenPos, const QVariant& variant )
{

    clear();

    switch(type)
    {
        case TrassPointMenu:
        {
            QAction* del_point = new QAction(tr("Удалить точку"), this);
            QList<QVariant> listVariant;

            listVariant.append(static_cast<int>(DeletePoint ));
            listVariant.append(variant);
            del_point->setData(QVariant(listVariant));
            addAction(del_point);

        }
        break;

        case TrassMenu:
        {
            QAction* add_point = new QAction(tr("Добавить точку") , this);
            QAction* settings = new QAction(tr("Настройки") , this);
            QList<QVariant> listVariant;

            add_point->setData(variant);
            listVariant.append (static_cast <int>(InsertPoint));
            listVariant.append(variant);
            add_point->setData(QVariant(listVariant));
            listVariant.clear();
            listVariant.append(static_cast <int>(Settings));
            settings->setData(listVariant);
            addAction(add_point);
            addAction(settings);

        }
        break;

    default:
        break;
    }

    exec ( screenPos );
}

