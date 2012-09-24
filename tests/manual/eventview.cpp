/*
    Copyright 2012 Frederik Gladhorn <gladhorn@kde.org>

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

#include "eventview.h"

#include <qtextdocument.h>
#include <qtextcursor.h>
#include <QTextBlock>
#include <qscrollbar.h>

void EventsWidget::addLog(const QAccessibleClient::AccessibleObject &object, const QString &eventName, const QString &text)
{
    if (!object.isValid())
        return;
    if (object.name() == m_eventsEdit->accessibleName() && object.description() == m_eventsEdit->accessibleDescription())
        return;

    bool wasMax = m_eventsEdit->verticalScrollBar()->value() == m_eventsEdit->verticalScrollBar()->maximum();

    QTextDocument *doc = m_eventsEdit->document();
    doc->blockSignals(true); // to prevent infinte TextCaretMoved events
    QTextCursor cursor(doc->lastBlock());
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);

    QString s = QString("%1: %2").arg(eventName).arg(object.name());
    QUrl url = m_registry->url(object);
    cursor.insertText(s.trimmed() + QLatin1Char(' '));
    cursor.insertHtml(QString("(<a href=\"%1\">%2</a>) ").arg(url.toString()).arg(object.roleName()));
    if (!text.isEmpty())
        cursor.insertText(QLatin1Char(' ') + text);

    cursor.insertBlock();

    doc->blockSignals(false);

    if (wasMax) // scroll down if we where before scrolled down too
        m_eventsEdit->verticalScrollBar()->setValue(m_eventsEdit->verticalScrollBar()->maximum());
}