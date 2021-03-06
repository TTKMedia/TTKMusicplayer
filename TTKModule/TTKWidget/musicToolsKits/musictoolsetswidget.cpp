#include "musictoolsetswidget.h"
#include "ui_musictoolsetswidget.h"
#include "musictimerwidget.h"
#include "musiclocalsongsmanagerwidget.h"
#include "musictransformwidget.h"
#include "musicnetworkconnectiontestwidget.h"
#include "musicreplaygainwidget.h"
#include "musicsongdlnatransferwidget.h"
#include "musicsongringtonemakerwidget.h"
#include "musicapplication.h"
#include "musicrightareawidget.h"
#include "musicspectrumwidget.h"
#include "musicsinglemanager.h"

MusicToolSetsWidget::MusicToolSetsWidget(QWidget *parent)
    : MusicAbstractMoveWidget(parent),
      m_ui(new Ui::MusicToolSetsWidget)
{
    m_ui->setupUi(this);
    setFixedSize(size());

    setAttribute(Qt::WA_DeleteOnClose, true);
    setAttribute(Qt::WA_QuitOnClose, true);

    m_ui->topTitleCloseButton->setIcon(QIcon(":/functions/btn_close_hover"));
    m_ui->topTitleCloseButton->setStyleSheet(MusicUIObject::MQSSToolButtonStyle04);
    m_ui->topTitleCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->topTitleCloseButton->setToolTip(tr("Close"));
    connect(m_ui->topTitleCloseButton, SIGNAL(clicked()), SLOT(close()));

    m_ui->listItemWidget->setFrameShape(QFrame::NoFrame);
    m_ui->listItemWidget->verticalScrollBar()->setStyleSheet(MusicUIObject::MQSSScrollBarStyle01);

    m_ui->listItemWidget->setIconSize(QSize(60, 60));
    m_ui->listItemWidget->setViewMode(QListView::IconMode);
    m_ui->listItemWidget->setMovement(QListView::Static);

    m_ui->listItemWidget->setSpacing(11);
    addListWidgetItem();

    connect(m_ui->listItemWidget, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(itemHasClicked(QListWidgetItem*)));
}

MusicToolSetsWidget::~MusicToolSetsWidget()
{
    G_SINGLE_MANAGER_PTR->removeObject(getClassName());
    clearAllItems();
    delete m_ui;
}

void MusicToolSetsWidget::addListWidgetItem()
{
    typedef struct ToolItem
    {
        QString m_icon;
        QString m_name;

        ToolItem() { }
        ToolItem(const QString &icon, const QString &name)
        {
            m_icon = icon;
            m_name = name;
        }
    }ToolItem;
    TTK_DECLARE_LISTS(ToolItem);

    ToolItems pairs;
    pairs << ToolItem(":/tools/lb_localmanager", tr("localmanager"))
          << ToolItem(":/tools/lb_bell", tr("bell"))
          << ToolItem(":/tools/lb_timer", tr("timer"))
          << ToolItem(":/tools/lb_transform", tr("transform"))
          << ToolItem(":/tools/lb_spectrum", tr("spectrum"))
          << ToolItem(":/tools/lb_connections" ,tr("connections"))
          << ToolItem(":/tools/lb_gain", tr("gain"))
          << ToolItem(":/tools/lb_dlna", tr("dlna"))
          << ToolItem(":/tools/lb_detect", tr("detect"))
          << ToolItem(":/tools/lb_screen_saver", tr("saver"));

    for(const ToolItem &pair : qAsConst(pairs))
    {
        QListWidgetItem *item = new QListWidgetItem(QIcon(pair.m_icon), pair.m_name, m_ui->listItemWidget);
#if TTK_QT_VERSION_CHECK(5,13,0)
        item->setForeground(QColor(MusicUIObject::MQSSColor01));
#else
        item->setTextColor(QColor(MusicUIObject::MQSSColor01));
#endif
        item->setSizeHint(QSize(80, 90));
        m_ui->listItemWidget->addItem(item);
    }
}

void MusicToolSetsWidget::itemHasClicked(QListWidgetItem *item)
{
    hide();
    //
    switch(m_ui->listItemWidget->row(item))
    {
        case 0:
            {
                SINGLE_MANAGER_WIDGET_CLASS(MusicLocalSongsManagerWidget);
                break;
            }
        case 1:
            {
                MusicSongRingtoneMaker(this).exec();
                break;
            }
        case 2:
            {
                MusicTimerWidget timer(this);
                QStringList songlist;
                MusicApplication::instance()->getCurrentPlaylist(songlist);
                timer.setSongStringList(songlist);
                timer.exec();
                break;
            }
        case 3:
            {
                MusicTransformWidget(this).exec();
                break;
            }
        case 4:
            {
                SINGLE_MANAGER_WIDGET_CLASS(MusicSpectrumWidget);
                break;
            }
        case 5:
            {
                SINGLE_MANAGER_WIDGET_CLASS(MusicNetworkConnectionTestWidget);
                break;
            }
        case 6:
            {
                SINGLE_MANAGER_WIDGET_CLASS(MusicReplayGainWidget);
                break;
            }
        case 7:
            {
                SINGLE_MANAGER_WIDGET_CLASS(MusicSongDlnaTransferWidget);
                break;
            }
        case 8:
            {
                MusicRightAreaWidget::instance()->musicFunctionClicked(MusicRightAreaWidget::IndentifyWidget);
                break;
            }
        case 9:
            {
                MusicRightAreaWidget::instance()->musicFunctionClicked(MusicRightAreaWidget::ScreenSaverWidget);
                break;
            }
        default:
            break;
    }
}

void MusicToolSetsWidget::show()
{
    setBackgroundPixmap(m_ui->background, size());
    MusicAbstractMoveWidget::show();
}

void MusicToolSetsWidget::clearAllItems()
{
    m_ui->listItemWidget->clear();
}

void MusicToolSetsWidget::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
    QListWidgetItem *it = m_ui->listItemWidget->currentItem();
    if(it)
    {
        itemHasClicked(it);
    }
}
