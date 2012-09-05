/*
    Copyright 2012 Sebastian Sauer <sebastian.sauer@kdab.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "uiview.h"

#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

using namespace KAccessibleClient;

struct RoleColor
{
    AtspiRole m_role;
    const char *m_color;
    RoleColor(AtspiRole role, const char *color) : m_role(role), m_color(color) {}
};

static RoleColor roleColors[] = {
    { ATSPI_ROLE_INVALID, "" },
//     { ATSPI_ROLE_ACCELERATOR_LABEL, "" },
    { ATSPI_ROLE_ALERT, "#ffacac" },
//     { ATSPI_ROLE_ANIMATION, "" },
//     { ATSPI_ROLE_ARROW, "" },
//     { ATSPI_ROLE_CALENDAR, "" },
//     { ATSPI_ROLE_CANVAS, "" },
    { ATSPI_ROLE_CHECK_BOX, "#6666ff" },
    { ATSPI_ROLE_CHECK_MENU_ITEM, "#ff6666" },
    { ATSPI_ROLE_COLOR_CHOOSER, "#6666ff" },
//     { ATSPI_ROLE_COLUMN_HEADER, "" },
    { ATSPI_ROLE_COMBO_BOX, "#6666ff" },
    { ATSPI_ROLE_DATE_EDITOR, "#6666ff" },
//     { ATSPI_ROLE_DESKTOP_ICON, "" },
    { ATSPI_ROLE_DESKTOP_FRAME, "#c0c0c0" },
    { ATSPI_ROLE_DIAL, "#6666ff" },
    { ATSPI_ROLE_DIALOG, "#c0c0c0" },
//     { ATSPI_ROLE_DIRECTORY_PANE, "" },
//     { ATSPI_ROLE_DRAWING_AREA, "" },
    { ATSPI_ROLE_FILE_CHOOSER, "#6666ff" },
//     { ATSPI_ROLE_FILLER, "" },
//     { ATSPI_ROLE_FOCUS_TRAVERSABLE, "" },
    { ATSPI_ROLE_FONT_CHOOSER, "#6666ff" },
    { ATSPI_ROLE_FRAME, "#c0c0c0" },
//     { ATSPI_ROLE_GLASS_PANE, "" },
//     { ATSPI_ROLE_HTML_CONTAINER, "" },
//     { ATSPI_ROLE_ICON, "" },
//     { ATSPI_ROLE_IMAGE, "" },
    { ATSPI_ROLE_INTERNAL_FRAME, "#c0c0c0" },
    { ATSPI_ROLE_LABEL, "#ffffaa" },
//     { ATSPI_ROLE_LAYERED_PANE, "" },
    { ATSPI_ROLE_LIST, "#acacff" },
    { ATSPI_ROLE_LIST_ITEM, "#6666ff" },
    { ATSPI_ROLE_MENU, "#acacff" },
    { ATSPI_ROLE_MENU_BAR, "#acacff" },
    { ATSPI_ROLE_MENU_ITEM, "#6666ff" },
//     { ATSPI_ROLE_OPTION_PANE, "" },
    { ATSPI_ROLE_PAGE_TAB, "#acacff" },
    { ATSPI_ROLE_PAGE_TAB_LIST, "#6666ff" },
    { ATSPI_ROLE_PANEL, "#c0c0c0" },
    { ATSPI_ROLE_PASSWORD_TEXT, "#ffffaa" },
    { ATSPI_ROLE_POPUP_MENU, "#acacff" },
//     { ATSPI_ROLE_PROGRESS_BAR, "" },
    { ATSPI_ROLE_PUSH_BUTTON, "#6666ff" },
    { ATSPI_ROLE_RADIO_BUTTON, "#6666ff" },
    { ATSPI_ROLE_RADIO_MENU_ITEM, "#6666ff" },
    { ATSPI_ROLE_ROOT_PANE, "#c0c0c0" },
//     { ATSPI_ROLE_ROW_HEADER, "" },
//     { ATSPI_ROLE_SCROLL_BAR, "" },
//     { ATSPI_ROLE_SCROLL_PANE, "" },
    { ATSPI_ROLE_SEPARATOR, "#acacff" },
    { ATSPI_ROLE_SLIDER, "#6666ff" },
    { ATSPI_ROLE_SPIN_BUTTON, "#6666ff" },
//     { ATSPI_ROLE_SPLIT_PANE, "" },
    { ATSPI_ROLE_STATUS_BAR, "#c0c0c0" },
    { ATSPI_ROLE_TABLE, "#acacff" },
    { ATSPI_ROLE_TABLE_CELL, "#6666ff" },
    { ATSPI_ROLE_TABLE_COLUMN_HEADER, "#3333ff" },
    { ATSPI_ROLE_TABLE_ROW_HEADER, "#3333ff" },
    { ATSPI_ROLE_TEAROFF_MENU_ITEM, "#6666ff" },
    { ATSPI_ROLE_TERMINAL, "#6666ff" },
    { ATSPI_ROLE_TEXT, "#ffffaa" },
    { ATSPI_ROLE_TOGGLE_BUTTON, "#6666ff" },
//     { ATSPI_ROLE_TOOL_BAR, "" },
    { ATSPI_ROLE_TOOL_TIP, "#ffffaa" },
    { ATSPI_ROLE_TREE, "#acacff" },
    { ATSPI_ROLE_TREE_TABLE, "#acacff" },
//     { ATSPI_ROLE_UNKNOWN, "" },
    { ATSPI_ROLE_VIEWPORT, "#c0c0c0" },
    { ATSPI_ROLE_WINDOW, "#c0c0c0" },
//     { ATSPI_ROLE_EXTENDED, "" },
//     { ATSPI_ROLE_HEADER, "" },
//     { ATSPI_ROLE_FOOTER, "" },
    { ATSPI_ROLE_PARAGRAPH, "#ffffaa" },
//     { ATSPI_ROLE_RULER, "" },
//     { ATSPI_ROLE_APPLICATION, "" },
//     { ATSPI_ROLE_AUTOCOMPLETE, "" },
    { ATSPI_ROLE_EDITBAR, "#6666ff" },
//     { ATSPI_ROLE_EMBEDDED, "" },
//     { ATSPI_ROLE_ENTRY, "" },
//     { ATSPI_ROLE_CHART, "" },
    { ATSPI_ROLE_CAPTION, "#ffffaa" },
//     { ATSPI_ROLE_DOCUMENT_FRAME, "" },
//     { ATSPI_ROLE_HEADING, "" },
//     { ATSPI_ROLE_PAGE, "" },
    { ATSPI_ROLE_SECTION, "#ffffaa" },
//     { ATSPI_ROLE_REDUNDANT_OBJECT, "" },
//     { ATSPI_ROLE_FORM, "" },
    { ATSPI_ROLE_LINK, "#6666ff" },
//     { ATSPI_ROLE_INPUT_METHOD_WINDOW, "" },
    { ATSPI_ROLE_TABLE_ROW, "#6666ff" },
    { ATSPI_ROLE_TREE_ITEM, "#6666ff" },
//     { ATSPI_ROLE_DOCUMENT_SPREADSHEET, "" },
//     { ATSPI_ROLE_DOCUMENT_PRESENTATION, "" },
    { ATSPI_ROLE_DOCUMENT_TEXT, "#ffffaa" },
    { ATSPI_ROLE_DOCUMENT_WEB, "#ffffaa" },
    { ATSPI_ROLE_DOCUMENT_EMAIL, "#ffffaa" },
    { ATSPI_ROLE_COMMENT, "#ffffaa" },
    { ATSPI_ROLE_LIST_BOX, "#6666ff" },
//     { ATSPI_ROLE_GROUPING, "" },
//     { ATSPI_ROLE_IMAGE_MAP, "" },
//     { ATSPI_ROLE_NOTIFICATION, "" },
    { ATSPI_ROLE_INFO_BAR, "#ffffaa" },
    { ATSPI_ROLE_LAST_DEFINED, "" }
};

#define ROLECOLORSCOUNT (sizeof(roleColors)/(sizeof(roleColors[0])))
#define ROLECOLOR "#aaffff"

UiWidget::UiWidget(UiView *view)
    : QWidget(view)
    , m_image(0)
{
    QPalette p = view->palette();
    p.setColor(QPalette::Window, Qt::white);
    view->setPalette(p);
    view->setAutoFillBackground(true);

    for(int i = 0; i < ROLECOLORSCOUNT; ++i) {
        RoleColor &rc = roleColors[i];
        m_roleColors[rc.m_role] = rc.m_color;
    }
}

void UiWidget::setAccessibleObject(const KAccessibleClient::AccessibleObject &acc)
{
    delete m_image; m_image = 0;
    m_object = acc;
    m_screen = QPixmap();
    m_bounds = bounds(acc);

    adjustSize();
    updateGeometry();
    update();
}

QSize UiWidget::sizeHint() const
{
    return m_bounds.size();
}

void UiWidget::paintEvent(QPaintEvent *event)
{
    if (!m_image) {
        if (m_bounds.isNull())
            return;
        m_image = new QImage(m_bounds.size(), QImage::Format_ARGB32_Premultiplied);
        QPainter painter(m_image);
        //painter.setClipRect(QRect(QPoint(0,0), QSize(m_bounds.size())));

        if (m_screen.isNull())
            m_screen = grabScreen();
        painter.setOpacity(0.6);
        painter.drawPixmap(0, 0, m_screen);
        painter.setOpacity(1.0);

        drawObject(&painter, m_object);
    }
    QPainter painter(this);
    painter.drawImage(0, 0, *m_image);
    painter.end();
}

QPixmap UiWidget::grabScreen() const
{
    if (m_bounds.isNull())
        return QPixmap();
    Q_ASSERT(m_bounds.left() < m_bounds.right() && m_bounds.top() < m_bounds.bottom());
    QPixmap pm = QPixmap::grabWindow(QApplication::desktop()->winId(), m_bounds.x(), m_bounds.y(), m_bounds.width(), m_bounds.height());
    return pm;
}

QRect UiWidget::bounds(const KAccessibleClient::AccessibleObject &acc) const
{
    if (!acc.isValid())
        return QRect();
    QRect rect;
    AccessibleObject::Interfaces ifaces = acc.supportedInterfaces();
    if( !(ifaces & AccessibleObject::Application) ) {
        KAccessibleClient::AccessibleObject parent = acc.parent();
        rect = bounds(parent);
    }
    if( ifaces & AccessibleObject::Component ) {
        QRect r = acc.boundingRect();
        if (!r.isNull())
            rect = rect.isNull() ? r : rect.united(r);
    }
    return rect;
}

void UiWidget::drawObject(QPainter *painter, const KAccessibleClient::AccessibleObject &acc, int depth)
{
    if (!acc.isValid())
        return;
    ++depth;
    AccessibleObject::Interfaces ifaces = acc.supportedInterfaces();
    if( !(ifaces & AccessibleObject::Application) ) {
        KAccessibleClient::AccessibleObject parent = acc.parent();
        drawObject(painter, parent, depth);
    }
    if( ifaces & AccessibleObject::Component ) {
        QRect r = acc.boundingRect();
        if (!r.isNull()) {
            r.moveTopLeft(r.topLeft() - m_bounds.topLeft());

            QColor color;
            QMap<AtspiRole, const char*>::ConstIterator colorIt = m_roleColors.constFind(acc.role());
            if (colorIt != m_roleColors.constEnd()) {
                color = QColor(colorIt.value());
            } else {
                color = QColor(ROLECOLOR);
            }
            color.setAlphaF(0.3);

            painter->fillRect(r, color);              
            if (depth == 1) {
                color = QColor(Qt::red);
            } else {
                color = color.darker();
            }
            painter->setPen(color);
            painter->drawRect(r);
        }
    }
}

UiView::UiView(QWidget *parent)
    : QScrollArea(parent)
{
    QWidget *widget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(widget);
    widget->setLayout(layout);

    m_uiWidget = new UiWidget(this);
    layout->addWidget(m_uiWidget);

    setWidget(widget);
}

UiView::~UiView()
{
}

void UiView::setAccessibleObject(const KAccessibleClient::AccessibleObject &acc)
{
    m_uiWidget->setAccessibleObject(acc);
    widget()->resize(m_uiWidget->size());
}
