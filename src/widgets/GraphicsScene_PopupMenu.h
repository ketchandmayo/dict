#pragma once

#include <QMenu>
#include <QPair>

class GraphicsScenePopupMenu : public QMenu
{
    Q_OBJECT

public:

    enum MenuType
    {
        UnknownMenu,
        TrassPointMenu,
        TrassMenu
    };

    static GraphicsScenePopupMenu* instance ( QWidget *parent = 0 );
    static void cleanup ();
    void showMenu (MenuType type, const QPoint& screenPos, const QVariant& variant = QVariant());

signals:
    void sigDeletePoint (int pointId = -1);
    void sigInsertPoint (const QPointF& point);

public slots:

private slots:
    void slotHandlingAction (QAction* action);

protected:
    explicit GraphicsScenePopupMenu (QWidget *parent = 0);
    virtual ~GraphicsScenePopupMenu ();

private:

    enum ActionType
    {
        DeletePoint,
        InsertPoint,
        Settings
    };

    static GraphicsScenePopupMenu* _instance;

//    QAction*    m_deletePointAction;
//    QAction*    m_insertPointAction;
};
